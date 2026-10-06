# NHL Hockey (HOCKEY.EXE) – disassembly and analysis

This directory contains a complete disassembly and decompilation of `HOCKEY.EXE`, the DOS executable of
EA Sports' **NHL Hockey '95** (it carries the 1993-94 season: 26 teams including Anaheim, Florida, Quebec,
Hartford and Winnipeg). It was produced with the LE tools added to this repository
(`tools/le.py`, `tools/ledisasm.py`, `tools/ghidra/LEDecompile.java`, `tools/lede.sh`) and is meant as the
reference for rebuilding the game in a modern engine. See [GODOT_PORT.md](GODOT_PORT.md) for how to use it
for a Godot port.

| | |
|---|---|
| File | `HOCKEY.EXE`, 1179067 bytes |
| SHA-256 | `da6efc206b01181c3f4a01a1e02d5e4a1a14be937463224e2fccc1a3e099b1b6` |
| Compiler | WATCOM C/C++32 (run-time 1988-1994), 32-bit flat model |
| Extender | Rational Systems DOS/4G(W) (bound, `DOS/4G Copyright (C) Rational Systems, Inc. 1987 - 1993`) |
| Format | MZ stub + DOS/16M (`BW`) kernel + Watcom stub + **LE** linear executable |

The executable itself is *not* part of the repository. The outputs here are regenerated from it with:

```
pip install capstone
GHIDRA_HOME=/path/to/ghidra_11.2.1_PUBLIC tools/lede.sh HOCKEY.EXE re/nhl_hockey hockey
```

(without `GHIDRA_HOME` only the disassembly is produced). The map file `hockey.map` is read back on every
run, so names and comments added to it by hand are kept and propagated into all outputs.

## Contents

| File | What it is |
|---|---|
| `hockey.map` | Editable routine/variable map in the mzmap format (segment-relative offsets). **This is the file to edit** when naming things. `#@` comment lines above a routine are carried into the listing. |
| `asm/hockey_XXXXXX.asm` | Annotated assembly listing of the code object, split in ~32 KB chunks named after their start address; `asm/hockey_data2.asm` is the data object. Every routine has a header with its callers, referenced strings, interrupts and ports; relocated operands are replaced with symbol names. |
| `decomp/decomp_XXXXXX.c` | Ghidra pseudo-C for every routine (2615 functions, 1 failure), with the names from the map and the Watcom register calling convention applied. `decomp/prototypes.h` has the recovered signatures, `decomp/ghidra_types.h` the Ghidra base types. |
| `hockey.json` | Machine readable dump: routines (address, size, blocks, callers, callees, strings, variables, interrupts, ports, calling convention), variables and strings. |
| `hockey.sym` | Tab separated symbol list (address, func/data, name, size, convention) for importing into other tools. |
| `strings.txt` | All 2622 strings of the data object with the routines that reference them. |

`hockey.elf` (ignored by git) is the relocated program image as an ELF32 file with the full symbol table;
it can be opened directly in Ghidra, IDA, radare2 or `objdump -d`.

## Executable layout

```
file offset  0x00000  MZ   DOS/4G loader stub (16-bit, entry 1BD:2382)          -> mzhdr can show it
             0x0f474  BW   DOS/16M protected mode kernel
             0x26654  MZ   Watcom bound stub, e_lfanew -> LE header
             0x28fec  LE   linear executable header ('hockey'), all LE offsets are relative to 0x26654
             0x5f254       data pages (193 pages of 4 KB, the last one 0xb67 bytes)
```

| Object | Linear base | Size | Flags | Contents |
|---|---|---|---|---|
| 1 | `0x10000` | `0xa7886` | R X 32-bit | all code: game, EA libraries, Watcom runtime |
| 2 | `0xc0000` | `0x3ab90` | R W 32-bit | data, `0x19000` bytes initialized, the rest BSS; initial ESP `0xfab90` |

Entry point (`_cstart_`) is `0x8ffd4`. The LE image has 26790 internal fixups (1418 pointing into the code
object: callbacks, jump tables and function pointer tables, 25372 into the data object). No imports.
All addresses in the outputs are linear addresses as if the objects were loaded at their preferred base.

## Disassembly statistics

- 2593 routines (1777 found through calls, 456 through function pointers, 377 by scanning unreferenced
  areas, 30 tail-called), 200768 instructions covering 99.1% of the code object; the remaining ~2.6 KB are
  data (floating point constants, an `int N; ret` stub table, strings stored in code).
- 54 switch jump tables resolved, 11 routines found to never return.
- 5985 variables, 2622 strings.
- Calling conventions: 2228 routines use the Watcom register convention (`__watcall`: arguments in
  `eax, edx, ebx, ecx`, then the stack, callee cleans up; all registers except `eax` preserved), 364 take
  their arguments on the stack with caller cleanup (`__cdecl` - EA's library layer and hand-written assembly).

## Code map

| Range | Routines | What |
|---|---|---|
| `0x10000 - 0x8c1b7` | 1175 (~500 KB) | **Game code** (Watcom C, register convention, every function starts with `push framesize; call __CHK`) |
| `0x8c1b7 - 0x8ffd3` | | EA library: VGA helpers, random numbers, memory manager (`reservemem`, `initmemman`), timer (`addtimer`), graphics init (`initgraphics`, EAVESA), fonts, shapes, sound, file loading |
| `0x8ffd4 - 0xa7fff` | | Watcom C runtime (`_cstart_`, `__CMain`, stdio, string functions, DOS/DPMI wrappers) mixed with EA library modules (unpacking, windows, text) |
| `0xa8000 - 0xb7886` | | Low level drivers: PIC/timer interrupt handlers, keyboard, mouse (`int 33h`), joystick (port `201h`), VGA/VESA bank switching, shape blitters, fatal error handling |

The library layer is what a port replaces with engine functionality; the list of the 217 library routines
called directly by game code is easy to obtain from `hockey.json` (routines below `0x8c1b7` and their callees
above it). The ones identified so far are named in the map, see the tables below.

## Program flow

```
_cstart_ (0x8ffd4)                  Watcom startup, DOS/4GW environment
 └ __CMain (0x99c32)
    └ main (0x10094)                disk space / memory checks, DPMI, initmem, initgraphics(640,480),
       │                            inittimer + addtimer(sub_10dcd), initmouse, fonts (.VFN), pointer shape,
       │                            load_cfg_palette (NHL.CFG), load_nhl_cfg (nhl.cfg, ALLFILES.TXT),
       │                            joystick detection/calibration, game.set
       ├ frontend_main_menu (0x31ab5)   EA SPORTS "desk" menus (maindesk/easndesk .iff screens,
       │   │                            "Sports Central", "League Calendar", "Playoff Tree", "Broadcast Booth");
       │   │                            menu handlers are called through the table at 0xc65c0
       │   └ ... match setup flows calling play_game (sub_32da9, sub_36b93, sub_89268)
       │       └ play_game (0x11d09)    loads game.sav and the .PPV team graphics, sets up the match
       │           └ game_loop (0x1167b)
       │               ├ get_frame_ticks      100 Hz timer ticks since the last frame
       │               ├ run_sim_steps(n)     n = ticks * 6 / 10  ->  fixed 60 Hz simulation
       │               │   ├ get_key_event / handle_hotkey   ESC pause, R replay, S sound, M music, F1-F10
       │               │   ├ game_clock_tick  24 steps per game-clock second, period horn (sfx 0x97)
       │               │   └ sim_tick (0x5c1c4)
       │               │       ├ sim_game_state (0x5c302)     stoppages, whistles, faceoffs
       │               │       ├ sim_update_players (0x5c40f) 12 players (6 per team)
       │               │       ├ sub_65d01
       │               │       └ sub_675d6 (tail call)
       │               ├ camera: from the tracked object at 0xc9098 (x + 32 clamped 0..64, 236 - y clamped 0..424)
       │               ├ draw_rink (0x33dd3) -> draw_sprites (0x5ce12) -> draw_clock (0x14cf1) -> present_frame (0x6ada7)
       │               ├ pause_menu (0x1935d), instant_replay (0x7e0fa), show_scoreboard (0x150c6)
       │               └ end_of_period (0x5dea6)
       └ shutdown: fade_palette, sound off, settextmode, exit handler
```

Key facts for a reimplementation:

- **Timing**: `inittimer` programs PIT channel 0 with divisor `0x2e9c` = **100 Hz**. The timer callback
  (`sub_10dcd`) counts ticks for the frame loop and every 5 ticks (20 Hz) samples both controllers and the
  keyboard into a 50 entry ring buffer (3 bytes per entry) which the simulation consumes every 3 steps.
  The simulation runs at a fixed **60 steps per second**, rendering happens once per loop iteration.
- **Video**: menus run at **640x480x256** (`initgraphics(0x280, 0x1e0)`, VESA through `EAVESA.COM`), the
  match at **320x200x256** (`set_video_mode(0x140, 200)`). In game the play field is a 320x168 window
  with a 32 pixel status/clock bar below (`subwindowdefadr(..., 0, 0xa8, 0x140, 0x20)`).
- **Rink**: the `rink` shape is rendered once into a 384x592 off-screen window (`sub_3377c`) and the camera
  scrolls over it vertically (the rink is viewed from above, goals at the top and bottom).
- **Game clock**: `game_clock_tick` counts 24 simulation steps per clock second, i.e. the clock runs 2.5x
  faster than real time.
- **Input**: keyboard events (scancodes), up to two joysticks read directly from port `201h`
  (`joy_detect`, `joy_read`, calibration prompts "Configure Left/Right Joystick"), mouse via `int 33h`
  in the menus.

## Data and asset formats

The game loads everything through a small set of loaders, so assets can be converted with standalone tools.
The complete game directory is committed next to this file (`*.PPV`, `*.QFS`, `*.TIL/.MAP`, `*.VFN`, `*.DB`,
`*.BIN`, the sound driver banks, `XBRUCE2.VIV`, ...), and every reader in `tools/nhl/formats.py` has been verified
against it; [FORMATS.md](FORMATS.md) has the exact layouts. `tools/nhl/nhltool.py` exports shapes and sprite
frames in team colours (`shapes`, `sprites`), the rink with a team's logo (`rinkfull`), fonts (`font`), the
sound effects (`dig`) and the speech bank (`viv`).

| Format | Loader(s) | Notes |
|---|---|---|
| `.fsh` / `.qfs` / `.vsh` / `.qvs` shape banks and the `.PPV` sprite and HUD banks (the `.iff` files of the installation are 8SVX music loops, `.KMS` music sequences) | `loadshapes`, `loadfile_auto`, `locateshape`, `getshape`, `shapecount`, `blit_sprite`, `blit_rle_frame` | EA **SHPI** bank: `"SHPI"`, size, entry count (+8), directory id, then 8-byte directory entries (4 character tag, offset) from +0x10. Each entry: type byte + 24-bit block size, width (+4), height (+6), hotspot x/y (+8/+0xa), position x/y (+0xc/+0xe), pixels from +0x10: plain 8-bit for type 0x7b, run length coded for the sprite frames (type bit 7). Palettes are entries named `!pal`, `embpal` etc. `q*` variants are compressed. |
| compressed files | `unpack` (0x97eb8), `unpackfile` | EA packers, header byte 1 = `0xFB` (RefPack `10FB` family), type byte selects the variant |
| `.vfn` fonts | `loadfile`, `setfont` | bitmap fonts (EASN.vfn, scor2b, scor3b, kaufm020 ...) |
| `.iff` sound (`VHDR`) | `loadsound`, `playsample` | IFF **8SVX** samples (the menu screens' music loops) |
| `PCFF001.PAT` / `.TIM` / `.DIG` | `snd_play_patch`, `snd_patch_record` | the sound effect bank of the digital driver: id -> patch record -> timbre -> signed 8 bit sample (30 samples, 11025 Hz) |
| `HOMEPALS.BIN`, `AWAYPALS.BIN`, `RINKPAL.QFS` | `load_team_palettes`, `setremaptable` | match palette and the per team colour remap tables of the sprites |
| `.cor` / `.bar` / `.int` | `sub_84ddd`, `sub_847ce`, `sub_59c1d` ... | announcer speech clips: `.cor` words and numbers ("1minute", "goalnum", "pennum"), `.bar` phrases ("scor1per", "eastfind", "stanleyd"), `.int` intros ("nhl", "lineups", "goodnite") |
| `.PAT` / `.TIM`, `.KMS` + `.CFG`, `.BGP` | `loadpatches`, `music_load_kms`, `load_music_banks` | instrument patches per sound driver (`%0.3sFF%03d.PAT/.TIM`), the organ songs and jingles, the sound card drivers |
| `.pen` | | penalty announcements (roughing, charging, slashing, hooking, tripping ...) |
| `.db`, `.dbx`, `.org`, `.HI`, `.SET`, `.sav` | `db_open_files`, `db_load_team_roster`, `db_read_player`, `savegame_io` ... | databases and saves: `teams.db` (28 teams, rosters as offsets into `key.db`, line tables), `key.db` (player names, numbers, positions), `att.db` (ratings), `career.db`, `season.db`, `carteams.db`, `schedule.db`, `gsummary.db`, `game.set`, `game.sav`, league directories `*.nhl`, `*.po`, `*.lp` |
| `RINK.QFS`, `TEAM.til` / `.map` | `load_rink`, `load_rink_tiles` | the 384x592 rink surface and the 8x8 tile maps of the 26 centre ice logos |
| `nhl.cfg`, `ALLFILES.TXT` | `load_nhl_cfg`, `load_cfg_palette` | installation path configuration and file list |

Sprite animation sequences are referenced by name (table around `0xc1e00`): skater `skate`, `glide`,
`turnl/turnr`, `stop`, `passf/passb`, `shotf/shotb`, `onetimef/b`, `fakeshotf/b`, `sweepchk`,
`shoulderchkl/r`, `hipchkl/r`, `crosscheck`, `hook`, `burst`, `fallfwd/fallback`, `stumble`, `injury1`,
`celebrate`, `pump`, `faceoff`, board checks, blocks; goalie `gstickl/r`, `gstackl/r`, `gdive`, `gswing`,
`goaliepoke`, `goalieknee`, `gofall*`; referee `ref*` (skating, pointing to the goal, penalty signals for
every infraction, `refpenshot`, anthem); cup ceremony `getcup`, `stansk`. AI roles and states use names
like `defo defd wingo wingd cento centd goalie puckc nearest shoot passrec`.

## Named routines

761 routines and 182 variables are named so far (the rest keep `sub_<address>` / `dword_<address>` names).
Library names in lower case without prefix (`reservemem`, `locateshape`, `initgraphics`, `addtimer`,
`unpack`, ...) are EA's own names recovered from their error messages; C runtime functions carry their
standard names; game routines use `snake_case` names describing what was understood of them, with the 47 AI
state handlers prefixed `ai_` and named after the original state names found in the data. The reverse
engineered data structures (entities, teams, AI dispatch, controls, globals) are described in
[STRUCTURES.md](STRUCTURES.md) and the file formats in [FORMATS.md](FORMATS.md). The most important routines:

| Address | Name | |
|---|---|---|
| `0x10094` | `main` | startup and shutdown |
| `0x31ab5` | `frontend_main_menu` | EA SPORTS desk menu |
| `0x11d09` | `play_game` | match setup |
| `0x1167b` | `game_loop` | per frame loop |
| `0x1149a` | `run_sim_steps` | fixed 60 Hz stepping |
| `0x5c1c4` | `sim_tick` | one simulation step |
| `0x5c40f` | `sim_update_players` | per entity update: animation, physics, control/AI dispatch |
| `0x5e16d` | `apply_skating` | skating/turning from a control byte |
| `0x5edad` | `skating_accelerate` | acceleration and speed limit from the skills |
| `0x5f53c` | `collide_boards` | boards with rounded corners |
| `0x11ff4` | `set_state` | push an AI state |
| `0x4a343+` | `ai_*` | the 47 AI state handlers |
| `0x1118f` | `handle_hotkey` | in-game hotkeys |
| `0x5dc10` | `game_clock_tick` | period clock |
| `0x33dd3` | `draw_rink` | background |
| `0x5ce12` | `draw_sprites` | players/puck |
| `0x14cf1` | `draw_clock` | clock/score overlay |
| `0x6ada7` | `present_frame` | copy to screen |
| `0x1935d` | `pause_menu` | in-game menu |
| `0x7e0fa` | `instant_replay` | replay |
| `0x60612` | `savegame_io` | load/save game |
| `0x8e080` | `initgraphics` | video mode setup |
| `0x903f0` | `drawshape` | transparent sprite blit |
| `0xb30b4` | `locateshape` | find shape by tag |
| `0x8e83c` | `loadshapes` | load FSH/QFS bank |
| `0x8f98f` | `loadsound` | load 8SVX sample |
| `0x8fb8e` | `playsample` | start a sample |
| `0xb4b88` | `setpalette` | VGA DAC upload |
| `0x8e5ac` | `inittimer` | 100 Hz timer |
| `0xb3464` | `joy_read` | joystick |

The full list with descriptions is in `hockey.map` (lines starting with `#@`).

## Continuing the work

The recommended loop is the one used throughout mzretools: study a routine in the listing and the pseudo-C,
rename it (and important variables) in `hockey.map`, add a `#@` comment, rerun `tools/lede.sh` and all outputs
(listing, JSON, ELF symbols, Ghidra output) pick up the new names. The simulation core, the AI dispatch, the
controls, the asset loaders and most screens are named; what remains unnamed is mostly menu/screen helpers in
`0x1b000-0x45000`, the HUD drawing helpers under `draw_clock`, the season/statistics screens and small sim
helpers. The Godot reimplementation that uses this material lives in
[godot/nhl_hockey](../../godot/nhl_hockey); the asset tools in [tools/nhl](../../tools/nhl).
