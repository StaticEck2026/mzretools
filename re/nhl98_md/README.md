# NHL 98 (Mega Drive / Genesis) – disassembly

Byte-exact disassembly of the retail ROM of EA Sports' **NHL 98** for the Sega Mega Drive / Genesis,
written in SNASM68K / asm68k syntax. Assembling it reproduces the original 2 MB image.

| | |
|---|---|
| ROM | `NHL 98 (USA).bin`, 2097152 bytes |
| MD5 | `a2c92c09d420cf7c2d2e55e8777f3a31` |
| SHA-1 | `6771e9b660bde010cf28656cafb70f69249a3591` |
| Header | `GM T-172176-00`, `(C)T-5O 1997.SEP`, region `4` (USA), declared ROM end `$7FFFF` |
| Checksum | `$5B3A` in the header is the word sum of `$200-$7FFFF` only (the first 512 KB) |

The ROM itself is not part of the repository. Everything under `data/art` and `data/bin` was cut out of it.

## Building

With SNASM68K (or `asm68k.exe`, the same assembler):

```
build.bat path\to\original.bin
```

which runs `snasm68k.exe -e -o ae- nhl98.asm, nhl98.bin, nhl98.sym, nhl98.lst` and compares the result
with the original. On Linux/macOS the free [vasm](http://sun.hasenbraten.de/vasm/) assembler accepts the
same source with its Motorola syntax module:

```
./build.sh path/to/original.bin      # vasmm68k_mot -m68000 -no-opt -Fbin
```

Both produce a byte-exact `nhl98.bin`. The source never relies on assembler optimisations: branch sizes
(`.s`/`.w`), absolute address sizes (`.w`/`.l`), zero displacements (`0(a0)`) and the immediate forms
(`addi`/`cmpi` versus `add`/`cmp`) are always written out explicitly, so an optimising assembler must be
told not to optimise (`-no-opt`; SNASM68K does not optimise unless asked).

About 1800 instructions in the C-compiled parts of the game use the "general" encoding of
`cmp/add/sub/and/or #imm,Dn` (opcode `$B07C` etc.) instead of `cmpi`/`addi`/...; they are written as
`cmp.w #n,d0` and marked `; general form`. SNASM68K and vasm keep that encoding. Should an assembler fold
them into the `-i` forms, regenerate the source with `--imm-macros` to emit them through the macros in
`inc/macros.inc`, which produce the exact words.

## Layout

```
nhl98.asm            main file: includes the modules below in ROM order and adds the $FF padding
inc/genesis.inc      Mega Drive hardware addresses
inc/ram.inc          one equate per referenced work RAM address ($FFFFxxxx, sign extended)
inc/macros.inc       macros for the general form immediates (optional, see above)
src/boot.asm         $000000  vectors, ROM header, EntryPoint, region lockout screen, VBlank_Dispatch
data/rosters.asm     $00077E  RosterTable and the 33 roster records (players with ratings, team names, arenas)
src/season.asm       $00B8DE  season mode: menus, standings, stats, transactions, simulation (partly compiled C)
src/game.asm         $01B8B8  game engine: play, penalties, injuries, play-by-play text
src/system.asm       $01FF24  system library: VDP, DMA, palettes, text printing, joypads, random numbers,
                              exception handlers
src/game2.asm        $022A82  game engine, second part
data/game_tables.asm $0288B2  tables used by the game engine
src/sound.asm        $02993A  sound interface (Sound_FuncTable), SRAM access
data/sound_data.asm  $02B0B0  Z80_SoundDriver and SoundBank (incbin)
src/sound_glue.asm   $091F88  Sound_Call wrapper and sound effect helpers
data/art.asm         $0924C2  all graphics as structured tile sets (see below)
src/frontend.asm     $1CED80  front end: team select, playoffs, rosters/trades, options, shootout, stats,
                              awards, skills challenge
data/misc_data.asm   $1E6730  remaining data
data/art/*.bin       raw 8x8 4bpp tiles of every tile set
data/bin/*.bin       other binary blobs (sound driver, sound bank, sprite tables...)
nhl98.names          editable symbol names and comments (read back by the generator)
nhl98.sym            every label with its address and kind
segments.txt         module boundaries and titles
```

### Naming conventions

* `sub_XXXXXX` routines, `loc_XXXXXX` branch targets, `dat_XXXXXX` data, `ptrs_` / `ptrtbl_` pointer tables,
  `jmptbl_` word offset jump tables, `inl_XXXXXX` inline argument blocks, `ram_XXXX` work RAM variables.
  Everything else carries a descriptive name from `nhl98.names`.
* Routines whose arguments follow the call in the code stream (the text printers `Text_Print*`,
  `Draw_RunScript`) are recognised by the generator; the block after the `jsr` is emitted as data with a
  length expression, so it can be edited freely.
* Every routine header lists its callers.

### Data formats

**Tile sets** (`Art_*`, `Font_*`): EA's graphics container, 170 of them in `data/art.asm`:

```
Art_Rink:
    dc.l    Art_Rink_Pal-Art_Rink        ; offset of the palettes
    dc.l    Art_Rink_Map-Art_Rink        ; offset of the tile map
Art_Rink_Tiles:
    dc.w    453                          ; tile count
    incbin  "data/art/art_rink.bin"      ; 8x8 4bpp tiles
Art_Rink_Pal:
    dc.w    ...                          ; 4 palettes of 16 colours
Art_Rink_Map:
    dc.w    48,89                        ; width, height in tiles
    dc.w    ...                          ; name table entries (tile | flip | palette)
```

`Art_PlayerSprites` (23305 tiles, 745 KB) uses the map block for its sprite frame table instead.
Team graphics come in three kinds, indexed like `RosterTable`: `Art_TeamName_*` (banner text),
`Art_TeamLogo_*` and `Art_TeamIcon_*`; `TeamArtTable` holds them in two team orderings.

**Rosters**: `RosterTable` points at one record per team; a record starts with the team colours and
line-up data, then the players (word length, name, rating nibbles) and ends with the city, abbreviation,
nickname and arena strings (word length including itself, NUL padded to an even size).

**Sound**: `Sound_Call` with `d0` = function number dispatches through `Sound_FuncTable`
(0 = `Snd_LoadDriver`, 1 = `Snd_Update` from VBlank, 6 = `Snd_SetSoundBank`, 13/14 = pause/resume
around DMA...). Commands are queued in Z80 RAM for the driver in `Z80_SoundDriver`.

**Save data**: battery backup at the odd bytes of `$200000` (`SRAM_Read` / `SRAM_Write`), mirrored at
`SaveDataMirror` in work RAM and protected by `SRAM_UpdateChecksum`.

## Exporting the graphics

`tools/md68k/mdart.py` converts every tile set to PNG (pure Python, no dependencies):

```
python3 tools/md68k/mdart.py "NHL 98 (USA).bin" out/art --names re/nhl98_md/nhl98.names
```

For each set it writes `<name>.png` (the picture through its tile map and palettes), `<name>_tiles.png`
(the raw tiles) and `<name>_pal.png` (the four palettes). `Art_PlayerSprites` and the other sprite sets are
decoded through their frame tables: every frame goes to `<name>/frame_NNNN.png` and all frames are laid
out with their numbers on the character sheet `<name>_sheet.png` (oversized scenes on
`<name>_sheet_large.png`). `index.txt` lists what was exported. Use `--scale 2` for zoomed images and
`--no-frames` to skip the individual frames.

Sprite frames are lists of 8 byte pieces in the layout of the VDP sprite attribute table (y, size, tile
attribute, x); the otherwise unused upper nibble of the size word selects a 2048 tile bank inside the set.

## Regenerating

The source is produced by the generic Mega Drive tools in `tools/md68k` of this repository:

```
python3 tools/md68k/mddisasm.py "NHL 98 (USA).bin" re/nhl98_md --name nhl98 --ea \
        --segments re/nhl98_md/segments.txt --max-code 0x40000
```

The generator maps code by recursive descent from the vectors (following branches, jump and pointer
tables, inline argument conventions), then emits the tree. `nhl98.names` is read first and written back,
so names and comments added by hand survive a regeneration; `--map-cache file.pkl` keeps the analysis
between runs.
