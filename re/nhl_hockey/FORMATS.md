# NHL Hockey – file formats

Formats as read by the loaders in `HOCKEY.EXE`. Routine names refer to `hockey.map`; `tools/nhl/formats.py`
implements the readers and `tools/nhl/nhltool.py` exports to PNG/WAV/JSON. Everything below was derived from
the code only (the data files were not available), so the readers are untested against real files; the parts
marked *unverified* were read from code paths that could not be cross checked.

## Compression (`unpack` 0x97eb8)

Any file may be stored compressed. The first two bytes identify the packer: byte 1 is `0xFB`, byte 0 (with bit 0
cleared) is the pack code:

| Code | Decoder | Notes |
|---|---|---|
| `10`/`11` | `refpack_decode` (0x97ce0) | standard EA **RefPack**: 2 byte header, optional 3 byte compressed size when bit 0 of byte 0 is set, 3 byte big endian decompressed size, then the usual 2/3/4 byte copy commands, literal runs `E0..FB` ((n&0x1f)+1)*4 bytes, stop `FC..FF` with 0-3 trailing literals |
| `30`/`32`/`34` | `bitlz_decode` (0x97740) | bit coded LZ variant, not implemented in the tools |
| `46` | `bytepair_decode` (0x97a38) | byte pair substitution, not implemented |
| `60`/`62`/`66` | `delta_decode` (0x97bb8) | output byte = running sum of input bytes; `62` has a 5 byte header, `66` 6 bytes |
| `6A`/`6E` | stored | 5 byte header followed by the raw data |
| `7A` | `pack7a_decode` (0x97c2c) | not implemented |

`loadfile_packed` reads a file, unpacks it when needed and returns the result; `loadfile_auto` additionally tries
the `.fsh/.vsh/.qfs/.qvs` variants of a name and rebuilds the directory of a `q*` bank (`shpi_from_compressed`).

## SHPI shape banks (`loadshapes`, `locateshape`, `getshape`, `shapecount`, `drawshape`)

Used for everything graphical: `.fsh/.qfs` banks, the `.PPV` sprite banks, `.iff` screens, `.KMS` and the
portrait sets.

```
+0    'SHPI'
+4    u32  file size
+8    u32  entry count                      (shapecount)
+0xc  4 chars directory id ('GIMX', 'G354'...)
+0x10 entries: 4 char tag + u32 offset       (getshape(bank, i) = bank + entry[i].offset)
```

Entry (EA "FSH" image):

```
+0    u8   code: 0x7b = 8 bit indexed image, 0x2d/0x24 = 24 bit palette, 0x2a = 32 bit palette, 0x29 = 16 bit
+1    u24  block size (0 = up to the end of the file)
+4    u16  width,  +6 u16 height
+8    u16  hotspot x, +0xa u16 hotspot y    (used by drawshape_remap_centered and the sprite renderer)
+0xc  u16  x position, +0xe u16 y position  (drawshape_home draws the entry at this position)
+0x10 pixel data, one byte per pixel, colour 0 is transparent in the sprite blitters
```

The game copies 0x300 bytes from +0x10 of palette entries (`!pal`, `embpal`, `Pal`, `apal`...) straight to the
VGA DAC, so palettes are 256 x 3 bytes with **6 bit** components. Jersey colours come from `HOMEPALS.BIN` /
`AWAYPALS.BIN` (0x1c0 bytes per team: 0xc0 bytes copied into the palette at +0x180/+0x240, 0x100 bytes remap
table, `load_team_palettes`) and are applied through the colour remap tables of `blit_sprite`.

### Sprite frames

`Entity.frame` (0..1133) indexes `sprite_frames`, which `load_sprite_banks` fills from 23 banks named after the
frames they hold: `000_049.PPV`, `050_099.PPV`, `100_149.PPV` ... `1100_1149.PPV`
(`"%d00_%d49"` / `"%d50_%d99"` with the bank index / 2). Inside a bank the entries are tagged `"%04d"` with the frame
number. `F000149.PPV` holds 105 effect frames (nets, ice marks, crowd), `numshp.PPV` the HUD digits (`0000`..`0009`)
and the position letters (`000G 000D 000D 000L 000C 000R 000X`), `trinknd.PPV` the rink ends, `HILIGHT.VFN` the
HUD font. Animations are described by `anim_sequences` (see STRUCTURES.md).

## VFN fonts (`setfont`, `printstr`, `textwidth`)

```
+0    4 char tag; tag[3] is an ASCII digit with the bits per pixel ('1'), 'MTNF' = glyphs are shapes
+4    u8 first char, +5 u8 last char, +6 u8 default glyph width, +7 u8 glyph height, +8 u8 extra advance
+0x12 u16 offset of a per character width table (0 = all glyphs use the default width)
+0x14 u16 per character height table, +0x16 u16 advance table, +0x18 u16 x offset table, +0x1a u16 y offset table
+0x1c u32 offset of the glyph bitmaps
+0x20 u32[last-first+1] glyph offsets relative to the bitmap base
```

1 bpp glyphs are rows of `ceil(width/8)` bytes, most significant bit first; set bits are drawn in the current text
colour (`settextpos(color, shadow)`). The reader only handles 1 bpp fonts.

## Sound (`loadsound`, `playsample`)

IFF **8SVX** (`FORM....8SVX`, `VHDR` with the sample rate at +12, signed 8 bit `BODY`) or RIFF WAV with a 0x2c
byte header, converted to signed by XOR 0x80. `playsample(sample, rate, channel, volume)`.

## Announcer speech (`speech_load_bank`, `speech_queue_clip`)

The clips referenced in the code (`pause.cor`, `goalnum.cor`, `scor1per.bar`, `nhl.int`, `roughing.pen`, ...) are
not separate files: they are entries of a speech bank, `XBRUCE2.VIV`. *Unverified* index layout:
three big endian u16 values (unknown, entry count, unknown) followed by, per entry, u32 BE offset, u32 BE size and
a zero terminated name. Entries whose data starts with `'G'` carry a 6 byte header before the sample
(`speech_load_bank` subtracts 5 from the size); the others are raw. A sentence is built by queueing clips
(`speech_queue_clip`) and played with `speech_play_sentence` (`say_goal`, `say_penalty`, `say_time_remaining`...).

## Rink (`load_rink`, `load_rink_tiles`)

`rink.til`: 8x8 tiles, 64 bytes each, 0xff = transparent. `rink.map`: u16 width, u16 height, u16 reserved, then
`width*height` u16 cells: bits 0-9 tile index, 0x2000 flip horizontally, 0x4000 flip vertically. The map is
rendered once into the 384x592 off-screen rink surface; the `rink` shape of the rink bank provides the backdrop.

## Databases and saves

| File | Layout |
|---|---|
| `teams.db`, `career.db`, `season.db`, `carteams.db` | 26 records of 0x2e8 bytes (`db_read_record`); team name (13 bytes) at +0x1a, short name (21 bytes) at +5 |
| `schedule.db`, `LSSCHED.DB` | 6 byte game records starting at offset 2 (`db_read_record2`): home team, away team, scores/flags |
| `gsummary.db` | per game summary records written by `season_record_result` |
| `PINFO.DB`, `PLAYER.ID`, `GAME` | league player information; `PLAYER.ID`: team byte, 11 byte name at +1, 13 byte league directory at +0xc, 4 bytes at +0x19 |
| `game.set`, `game.sav` | settings block (see `apply_settings`) and the saved game: u32, 17 x 0x66 byte entity snapshots, 2 x 0xd4 byte team snapshots, 2 x 0x30 byte line tables, ... (`read_saved_game`) |
| `*.nhl`, `*.po`, `*.lp` | league directories (exhibition, playoff, league) |
| `nhl.cfg`, `ALLFILES.TXT` | installation directory and the list of files that were copied to the hard disk (`file_on_disk[]`) |
| `*.HI` | saved instant replay highlights (`replay_save_highlight`) |
| `*.cmv` | coach "clip" movies played between periods (`coach_clip_player`), IFF chunked (`iff_parse`) |

Settings block (`apply_settings`): +0 u32 flags, +4 league directory (13 chars), +0x11 and +0x31 strings, +0x51 home
team id, +0x55 away team id, +0x59 option flags, +0x5d, +0x61, +0x65 controller of player 1 (0 none, 1 mouse,
2 joystick 1, 4 joystick 2, 8 keyboard), +0x69 controller of player 2, +0x6d period length, +0x71.
