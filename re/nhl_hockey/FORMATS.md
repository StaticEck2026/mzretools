# NHL Hockey – file formats

Formats as read by the loaders in `HOCKEY.EXE`. Routine names refer to `hockey.map`; `tools/nhl/formats.py`
implements the readers and `tools/nhl/nhltool.py` exports to PNG/WAV/JSON; the Godot loaders in
`godot/nhl_hockey/loaders` mirror them. The formats were derived from the code and then verified against the
game files in this directory (every `.QFS`/`.PPV` bank, the fonts, the tiles, the databases and the sound bank
decode; the parts marked *unverified* could not be cross checked).

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
A few banks (`EADESK0.QFS`, the `JER*.QFS` jerseys, `EDBPAL.QFS`...) carry one to three padding bytes behind the
stop code; `unpack` only ever writes the number of bytes given in the header, so decoders must truncate.

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
+0    u8   code: 0x7b = 8 bit indexed image; 0x22/0x2d/0x24 = 24 bit palette, 0x2a = 32 bit, 0x29 = 16 bit;
           bit 7 set (0xfb, 0x80, 0x81) = run length coded sprite frame (below)
+1    u24  block size (0 = up to the end of the file; meaningless for the run length frames)
+4    u16  width,  +6 u16 height
+8    s16  hotspot x, +0xa s16 hotspot y    (blit_sprite draws a frame at x - hotspot, y - hotspot)
+0xc  u16  x position, +0xe u16 y position  (drawshape_home / blit_rle_frame_home draw the entry there)
+0x10 pixel data
```

Plain images (`0x7b`) store one byte per pixel; colour 0 is transparent in `drawshape`. Palette entries (`!pal`
768x1 in the `.PPV` banks, `embpal`, `Pal`, `apal`...) hold 256 x 3 bytes with **6 bit** components; the game
copies 0x300 bytes from +0x10 straight to the VGA DAC.

### Sprite frames (`blit_sprite`, `blit_rle_frame`)

All `.PPV` frames use the run length code (`sub_b4cd8`): a count byte `c` followed by one colour byte when
`1 <= c <= 0x7f` (the colour repeated `c` times; colour `0xff` is a run of `c` transparent pixels which the
blitter skips), `0x100 - c` literal colour bytes when `c >= 0x80`, and `c == 0` ends the frame. Rows are not
aligned, the stream is simply `width * height` pixels long.

`Entity.frame` (0..1133) indexes `sprite_frames`, which `load_sprite_banks` fills from 23 banks named after the
frames they hold: `000_049.PPV`, `050_099.PPV` ... `950_999.PPV`, then without the underscore because of the
8.3 limit: `10001049.PPV`, `10501099.PPV`, `11001149.PPV` (`"%d00_%d49"` / `"%d50_%d99"` with the bank index / 2).
Inside a bank the entries are tagged `"%04d"` with the frame number. Frames 404/405 are the two nets (entity slots
12/13), 0x185/0x186/0x187 the markers drawn under the controlled players and the puck carrier, 0x17f..0x184 and
0x160..0x163 the off screen arrows. `F000149.PPV` holds 105 effect frames (ice marks, net variants, crowd),
`numshp.PPV` the 8x7 digits (`0000`..`0009`, drawn 13 pixels below the skates by `draw_player_number`) and the
position letters (`000G 000D 000D 000L 000C 000R 000X`, indexed by line slot), `trinknd.PPV` the end boards
overlay, `scrbrd1.PPV` the scoreboard (below). Animations are described by `anim_sequences` (see STRUCTURES.md).

### Match palette and jersey colours (`load_team_palettes`, `blit_sprite`)

`RINKPAL.QFS` (`!pal`) provides the palette entries 0..0x7f and 0xfb..0xff. `HOMEPALS.BIN` and `AWAYPALS.BIN`
hold 0x1c0 bytes per team (28 teams): 0xc0 palette bytes (64 jersey colours, placed at entries 0x80..0xbf for the
home team and 0xc0..0xff for the away team) followed by a 256 byte colour **remap table**. Every pixel of a
sprite is pushed through the remap table of its team (`setremaptable`); the away table gets 0x40 added to its
entries 0x90..0xff so that it points into the away block. Frames use the indices 0x85..0xc4, 0xd0..0xd4, 0xe0..0xe4
and 0xf0..0xf4 for the jerseys. While a mirrored frame is drawn the entries 0xc0 + 16k + {0, 1, 3, 4} of the table
are swapped ([0] with [4], [1] with [3]) so the shaded side of the jersey follows the facing. `blit_sprite`
mirrors a frame around `width - 1 - hotspot_x`.

### Scoreboard (`draw_clock`, `draw_score_digits`, `draw_clock_full`, `draw_line_box`, `draw_penalty_clocks`)

The screen is 320x200: the ice view (a 320x168 window onto the 384x592 rink surface, world x + 0xc0,
0x140 - world y) on top and a 320x32 scoreboard window (`hud_window`, `subwindowdefadr(..., 0, 0xa8, 0x140, 0x20)`)
below. `scrbrd1.PPV` holds its shapes: `hlin`/`vlin` 72x32 panels at (64, 0) / (184, 0) with the line energy bars
(`hpp`/`hpk`/`vpp`/`vpk` while a unit is on the ice, `homp`/`visp` while penalties run), the 16x13 score digits
`0000`..`0009` (`000 ` blank) at x 0x2e/0x38 (home) and 0xff/0x109 (away), y 4, the 16x11 clock digits
`1000`..`1009` (`100 ` blank) at x 0x8c, 0x95, 0xa1, 0xaa, y 3 (`mm:ss`, or `ss.hh` with a blank last digit
during the final minute), the 8x4 penalty clock digits `2000`..`2009` (number, minutes, seconds at x + 10, 0x10,
0x1b, 0x21, 0x2a, 0x30 from 0x48 / 0xbf, y 9 + 5n) and the `lin1`..`PK2` labels of the pause screen. The line
bars are `fillrect`s: 20 pixels = full energy, at (0x4a + 0x15 - w, 8 + 6n) and (0x4a + 0x20, ...) for the home
team (0xc1 for the away team), colour 0x21 for the current line, 0x67 otherwise; `draw_energy_bar` draws the
energy of the players on the ice as two 8 pixel bars at y 0x1a next to the score. Stoppage messages
(`draw_message_box`: `FACE-OFF`, `OFFSIDE`, `ICING`, `2 LINE PASS`, `PENALTY`...) appear in a box at (12, 149)
of the view, fill colour 0x10, border 9, text in `SCOR3B.VFN` (colour 0x25) with `SCOR2B.VFN` on top (0x27).

## VFN fonts (`setfont`, `printstr`, `textwidth`)

```
+0    4 char tag; tag[3] is an ASCII digit with the bits per pixel ('1'), 'MTNF' = glyphs are shapes
+4    u8 first char, +5 u8 last char, +6 u8 default glyph width, +7 u8 glyph height, +8 u8 extra advance
+0x12 u16 offset of a per character width table (0 = all glyphs use the default width)
+0x14 u16 per character height table, +0x16 u16 advance table, +0x18 u16 x offset table, +0x1a u16 y offset table
+0x1c 4 char tag ('FNTX' or 'FNED') in every font of the game
+0x20 u32[last-first+1] absolute file offsets of the glyph bitmaps (0 = no glyph)
```

1 bpp glyphs are rows of `ceil(width/8)` bytes, most significant bit first; set bits are drawn in the current text
colour (`settextpos(color, shadow)`). This decodes `HILIGHT`, `WITTLE06`, `TEENY05`, `MINIFO05`, `EASN`,
`LINEDIT`, the large menu fonts and the glyph metrics of every font; the 9 byte glyphs of `SCOR2B`/`SCOR3B`
(the message box fonts) are not plain 1 bpp rows and are not decoded yet.

## Sound (`loadsound`, `playsample`)

IFF **8SVX** (`FORM....8SVX`, `VHDR` with the sample rate at +12, signed 8 bit `BODY`) or RIFF WAV with a 0x2c
byte header, converted to signed by XOR 0x80. `playsample(sample, rate, channel, volume)`. The `.IFF` files of
the installation (`MAINDESK.IFF`, `PAUSE.IFF`, `TONIGHTS.IFF`...) are such 22050 Hz samples: the music loops of
the menu screens.

### Sound effects of the match (`play_sfx`, `snd_play_sfx`, `snd_play_patch`)

`play_sfx(id)` hands a sound id to the EA sound driver, which plays it as a MIDI event: ids >= 0x80 are
percussion notes on channel 9 (note = id - 0x74), ids < 0x80 program changes on the channels 12..15 with note
0x24. The driver resolves the id through the bank of the sound card (`PCFF001.PAT/.TIM/.DIG` for the digital
drivers, `%0.3sFF%03d.PAT/.TIM` per driver name):

```
PCFF001.PAT  +0 u16, +2 u8[256] sound id -> record index, +0x102 records of 0x14 bytes:
             +0 1 = digital sample / 0 = FM instrument, +1 program number (1 based timbre index), +7 s8 transpose
             in semitones, the rest envelope/driver data
PCFF001.TIM  +0 u32 file size, +4 u16 timbre count, then count x (u16 0x180, u16 program), ".dig", u32 offsets;
             32 byte timbres from +0x106: +0xa u16 sample rate (11025, one at 22050), +0xc u32 sample length,
             +0x10/+0x14 u32 loop start/end (0 = no loop), +0x19 5 byte sample id
PCFF001.DIG  +0 u16 0x7ff1, +2 u16 4, +4 u16 sample count (30), +6 the 4 byte sample ids sorted ascending,
             +0x82 u32 start offsets of the samples 1..n-1 (relative to the data), +0xf6 signed 8 bit PCM
```

Timbres are matched to the samples by their length (three pairs share a length; the first match is taken).
`nhltool.py dig GAMEDIR OUT` exports the 33 digital effects as `sfx_<id>.wav`. Ids used by the game code:
0x7d/0x7e crowd loops (`update_ambient_audio`, volume from `crowd_noise`), 0x90 period horn (FM only),
0x97 one minute warning, 0x98/0x99 pass, 0x9a slap shot, 0x9b pick up, 0x9c goal horn (the 7 second sample),
0x9d/0xa3 puck hits a body / stick, 0xa0/0xa1 body check, 0xa2 stung, 0xa4 whistle, 0xa6 crowd, 0xaa wrist shot,
0xab puck drop (FM only), 0xac post, 0xad boards, 0xae glass, 0xb0/0xb2 skates, 0xb1 body into the boards.
The `.KMS` files are the organ songs and jingles for the music driver (`music_load_kms`, `load_music_banks`), with
a `.CFG` each; `.BGP` are the sound card drivers and `.SCN`/`.PAT`/`.TIM` their patch sets.

## Announcer speech (`speech_load_bank`, `speech_queue_clip`, `speech_release_clip`)

The clips referenced in the code (`pause.cor`, `goalnum.cor`, `scor1per.bar`, `nhl.int`, `roughing.pen`, ...) are
entries of the speech bank `XBRUCE2.VIV`, an EA `0xC0FB` archive: u16 BE `0xC0FB`, u16 BE size of the index,
u16 BE entry count (344), then per entry a 24 bit BE offset, a 24 bit BE size (`read_be32` reads three bytes)
and a zero terminated name (eight `.int` names appear twice). An entry is either raw unsigned 8 bit PCM played
at 5512 Hz (`speech_load_bank`: duration = size * 100 / 5512 ticks) or packed with pack code `0x47 0xFB`
(`unpack` -> `bytepair_decode`, 0x97a38): 3 bytes, the unpacked size (24 bit BE), the escape byte, the number
of byte pairs and the pairs (code, left, right); in the data a pair code expands recursively (`sub_979f8`),
the escape byte is followed by a literal, an escape followed by 0 ends it. The unpacked data skips a 5 byte
header and is a running sum (`sub_83bf3`) of signed 8 bit samples at 11025 Hz. Clip types: `.num` numbers
(`0`..`99`, `01`..`09` for the seconds), `.tea` / `.frm` / `.hom` / `.awa` team names (by `team_abbrev`),
`.rnk` arenas, `.pen` penalties, `.cor` / `.bar` / `.int` phrases.

`speech_queue_clip` only loads a clip (once per sentence); `speech_release_clip` appends it to the playback
list, so the release order is what is said: `say_goal` "bos.tea goalnum.cor 12.num [pause.cor asstnum.cor
77.num [pause.cor andnum.cor 8.num]]", `say_penalty` "det.tea pennum.cor (pensnum.cor when more are queued,
andnum.cor for the next one of the same team) 19.num pause.cor 2min.cor|5min.cor|gamemisc.cor hooking.pen
pause.cor [at.cor pause.cor 12.num 05.num]", `say_penalty_shot`, `say_star` "3rdstar.cor bos.frm pause.cor
number.cor 77.num", `sub_854ac` "oneleft.cor" (one minute left, from `game_clock_tick`; without speech the
tone 0x97). The timer routine `sub_832bc` (100 Hz) starts each clip 0x1a ticks before the previous one ends
and keeps `speech_busy` set 0x1a ticks after the last. `nhltool.py viv XBRUCE2.VIV OUT` exports the clips as WAV.

## Rink (`load_rink`, `load_rink_tiles`)

`RINK.QFS` holds the 384x592 `rink` shape (plain 0x7b image, the ice with the crowd): the rink surface. Centre
ice is at (192, 320) of the surface (`draw_sprite_world`: screen = (x + 0xc0, 0x140 - y)), the boards at world
y = +-264. The centre ice logo of the home team comes from `TEAM.TIL` / `TEAM.MAP` (BOS, BUF, CGY, CHI, DET, EDM,
HFD, LA, MIN, MTL, NJ, NYI, NYR, OTT, PHI, PIT, QUE, STL, SJ, TB, TOR, VAN, WSH, WPG, ANH, FLO): `.TIL` = 8x8
tiles of 64 bytes, 0xff transparent; `.MAP` = u16 width, u16 height, u16 reserved, then `width*height` u16
cells: bits 0-9 tile index, 0x2000 flip horizontally, 0x4000 flip vertically. `rink_logo_table` (0xc7298, 12
bytes per team: name, tile column, tile row, column/row of a second copy or -1) places the map on the surface;
EDM, LA, NJ and PIT store half of a symmetric logo and draw the second copy mirrored (flag 0x6000: right to
left, bottom to top, every tile flipped). `nhltool.py rinkfull GAMEDIR OUT.png --home N` renders the result.

## Databases and saves

| File | Layout |
|---|---|
| `teams.db`, `carteams.db` | 28 records of 0x2e8 bytes (26 teams + the two all star teams): +0 abbreviation (5), +5 city and nickname (21), +0x1a short name (13), +0x4c 25 x i32 offsets of the skaters in `key.db` (-1 = empty), +0xb0 3 x i32 goalie offsets, +0xbc the line table (`db_load_team_roster`, `line_energy`): 4 forward lines x 3 (LW C RW), 3 defence pairs x 2, 2 power play units x 5, 2 penalty killing units x 4, 2 goalies, 6 extra slots, all as roster indices 0..27 (0x64 = unset) |
| `key.db` | player records of 0x34 bytes (`db_read_player`): +1 jersey number, +2 position letter (C L R D G), +3 first name (16), +0x13 last name (16), +0x24 i32 offset into `att.db`, +0x28 into `career.db`, +0x2c into `season.db`, +0x30 portrait id ("0001") |
| `att.db` | ratings 0..15 (`put_player_on_ice`): skaters 0x14 bytes: hand (1 = left, right handed players are drawn mirrored), agility, speed, weight class, shot power, aggressiveness, defensive awareness, shot accuracy, (unused), passing, offensive awareness, awareness, checking, stick handling, +0xe..+0x13 further ratings (faceoffs, ...); goalies 0x10 bytes: hand, +1..+5 (checking, passing, offensive awareness, stick handling, shooting), agility, speed, weight, +0xa/+0xb reaction / awareness |
| `season.db`, `career.db` | per player statistics records pointed to by `key.db` (0x2f / 0x36 bytes per skater / goalie in `season.db`, 0x28 in `career.db`): goals and assists as u16 pairs, the injury date at +0x26 |
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
