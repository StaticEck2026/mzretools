# Porting NHL Hockey to Godot

This guide describes how to use the disassembly in this directory to rebuild the game in Godot 4. The goal of
the disassembly is to make the *behaviour* of the original recoverable (simulation rules, AI, timing, menus and
data formats); the DOS specific layer (DOS/4GW, VGA, PIT timer, port I/O, EA's memory manager) is replaced by the
engine and does not need to be ported.

The port itself lives in [godot/nhl_hockey](../../godot/nhl_hockey) (Godot 4.3 project): asset loaders, the
static tables extracted from the EXE, entity and team records, animation, physics and collisions, controls, the
puck handling (passes, shots, saves, deflections), the rules (stoppages, faceoffs, goals, offside, icing, the
clock) and the AI state machine are translated from the decompiled routines; penalties, line changes and the
ceremonies are the main parts still missing (see its README for the exact list). [STRUCTURES.md](STRUCTURES.md) documents the data structures the port mirrors and
[FORMATS.md](FORMATS.md) the file formats its loaders (and `tools/nhl`) read.

## 1. What to port and what to replace

| Original layer | Address range | In Godot |
|---|---|---|
| Watcom runtime, DOS/DPMI, memory manager, file I/O | `0x8ffd4+`, `0x8c1b7-0x8ffd3` | GDScript/C# standard library, `FileAccess`, resources |
| Timer interrupt (100 Hz) + frame pacing | `inittimer`, `addtimer`, `sub_10dcd`, `get_frame_ticks` | `_physics_process` with `physics_ticks_per_second = 60` |
| Keyboard, joystick (port 201h), mouse (int 33h) | `sub_10a86`, `sub_10ac6`, `joy_read`, `readmouse` | `Input` actions, polled at the same rate the original samples them (20 Hz for the simulation's control buffer) |
| VGA/VESA, palettes, blitters, fonts | `initgraphics`, `setpalette`, `drawshape*`, `printstr*` | `SubViewport` 320x200 (game) / 640x480 (menus), `Sprite2D`/`AnimatedSprite2D`, palette shader, `FontFile` |
| Sound (8SVX samples, channels, patches) | `loadsound`, `playsample`, `sound_*`, `loadpatches` | `AudioStreamWAV`, `AudioStreamPlayer` pool, buses for crowd/speech/sfx |
| **Game code** | `0x10000-0x8c1b7` | **port**: simulation, AI, rules, camera, menus flow, stats, databases, save games |

Only the ~1175 routines of the game range need porting, and many of those are menu screens that can be
redesigned rather than translated.

## 2. Suggested Godot project structure

```
res://
  autoload/
    Game.gd            global state that lives in the data object today (settings, teams, schedule, stats)
    Assets.gd          loaders for the converted assets
  sim/
    Simulation.gd      sim_tick: fixed step (60 Hz), deterministic, no rendering
    Players.gd         sim_update_players, AI roles (defo/defd/wingo/wingd/cento/centd/goalie)
    Puck.gd
    Rules.gd           sim_game_state: whistles, offside, icing, penalties, faceoffs
    Clock.gd           game_clock_tick (24 steps per clock second)
  view/
    Rink.tscn          384x592 rink texture + Camera2D (limits as in game_loop)
    PlayerSprite.tscn  AnimatedSprite2D with the animation names from the original (skate, shotf, hipchkl ...)
    Hud.tscn           clock/score bar (draw_clock), 320x32 at the bottom
  menus/               front end screens (frontend_main_menu, pause_menu, boxscore_screen ...)
  audio/               crowd, organ, announcer (.cor/.bar/.int), penalty calls (.pen)
tools/                 asset converters (Python, run once outside Godot)
```

Keep the simulation independent from the scene tree (plain objects stepped from `_physics_process`), exactly
like the original separates `run_sim_steps`/`sim_tick` from the drawing done once per frame in `game_loop`. This
makes it possible to compare the port against the original step by step.

## 3. Timing and coordinates

Values taken from the code (see README.md for the addresses):

- Simulation: **60 steps per second** (`run_sim_steps` gets `ticks * 6 / 10` steps from a 100 Hz timer).
  Set `Engine.physics_ticks_per_second = 60` and call the ported `sim_tick()` once per physics frame.
- Controls are sampled every 5 timer ticks (20 Hz) into a ring buffer and consumed every 3 simulation steps; to
  reproduce the original feel, latch the input state every third physics step.
- Game clock: 24 simulation steps per displayed second.
- Screen: in game 320x200, the play field is the top 320x168, the status bar the bottom 32 lines. Use a 320x200
  `SubViewport` with nearest filtering and integer scaling (`display/window/stretch/mode = viewport`).
- Rink: a 384x592 bitmap (`rink` shape), camera origin x in `0..64`, y in `0..424`, computed from the tracked
  object as `x + 32` and `236 - y` (`game_loop`). Note the inverted y axis of the original coordinates.

## 4. Assets

Write offline converters (Python is fine) that turn the original files into Godot friendly formats; the
disassembly tells exactly how they are read:

1. **Shape banks** (`.fsh`, `.qfs`, and screens/graphics loaded through `loadshapes`): parse the `SHPI`
   directory (`shapecount`/`getshape`/`locateshape`), decompress `q*` files first (`unpack` at `0x97eb8`,
   RefPack-style header `xx FB`). Export every entry as a PNG plus a JSON sidecar with its tag, hotspot
   (+8/+0xa) and position (+0xc/+0xe); export `!pal`/`embpal` entries as palettes. Import sprite sheets into
   `SpriteFrames` using the animation names found in the data object.
2. **Palettes**: the game changes palettes at runtime (fades in `fade_palette`/`fade_palette_to`, remap tables
   via `setremaptable`, team colors). Either bake RGB textures per palette, or keep 8-bit index textures and do
   the lookup in a `CanvasItem` shader with a 256x1 palette texture; the latter reproduces fades and color
   remapping (`drawshape_remap`) exactly.
3. **Sound**: IFF 8SVX (`VHDR`/`BODY` chunks, signed 8-bit PCM) converts directly to WAV. Announcer clips
   (`.cor`, `.bar`, `.int`, `.pen`) are concatenated at runtime by the speech routines around `0x84306-0x8579e`;
   port their sequencing logic, not the audio code.
4. **Databases and saves** (`teams.db`, `schedule.db`, `career.db`, `game.set`, `game.sav` ...): the readers use
   plain `open/read` wrappers (`file_open_read`, `file_read`, `savegame_io`); follow the callers of these to get
   the record layouts and convert to JSON or Godot `Resource`s.
5. **Fonts** (`.vfn`): bitmap fonts selected with `setfont`; convert to image fonts.

## 5. Porting the game logic

Work top down from the flow documented in README.md and port routine by routine:

1. Use `decomp/decomp_*.c` as the readable starting point and the listing in `asm/` to resolve anything the
   decompiler got wrong (register-passed arguments show up as `param_N`/`unaff_EDX` etc., with Watcom
   `__watcall` meaning `eax, edx, ebx, ecx`).
2. Global variables (`dword_c9098`, `word_cbc48` ...) are the game state: collect the ones a routine touches from
   `hockey.json` (`vars` field of each routine) and move them into typed fields of the port's state objects.
   Rename them in `hockey.map` as their meaning becomes clear so all outputs stay in sync.
3. Fixed point: most positions/velocities are 16.16 values stored in 32-bit ints (`>> 0x10` all over the
   decompiled code) or plain 16-bit values. Keep the port in integers first (GDScript `int` is 64-bit) so the
   behaviour matches exactly; switch to floats only after the logic is verified.
4. Random numbers: the game uses EA's `randomrange` (0x8c230, 16-bit LCG) and Watcom `rand` (0x8eb27,
   `seed * 0x41c64e6d + 0x3039`). Port them bit-exactly to be able to replay identical matches.
5. Verification: run the original in DOSBox, record the key presses per simulation step, feed the same input
   into the port and compare the positions of players and puck; a mismatch points at the routine to fix. This is
   the same instruction level approach mzdiff uses for 16-bit code, applied to behaviour.

Recommended order: data loading (teams/rosters) -> rink and camera -> player movement and puck physics
(`sim_update_players`, `sub_65d01`, `sub_675d6`) -> rules and clock (`sim_game_state`, `game_clock_tick`) ->
AI roles -> HUD and pause menu -> front end menus -> season/playoff mode, statistics and saves -> audio and
announcer.

## 6. Legal note

The disassembly and decompiled code are derived from a commercial product (EA Sports, NHL/NHLPA licenses). Use
them as a reference for your own reimplementation; the port should not ship original code, graphics, sounds or
the licensed team and player data without permission. Assets extracted from a legally owned copy can be
loaded at runtime from the user's installation instead of being redistributed.
