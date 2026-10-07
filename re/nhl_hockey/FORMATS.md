# NHL Hockey – file formats

Formats as read by the loaders in `HOCKEY.EXE`. Routine names refer to `hockey.map`; `tools/nhl/formats.py`
implements the readers and `tools/nhl/nhltool.py` exports to PNG/WAV/JSON; the Godot loaders in
`godot/nhl_hockey/loaders` mirror them. The formats were derived from the code and then verified against the
game files in this directory (every `.QFS`/`.PPV` bank, the fonts, the tiles, the databases and the sound bank
decode; the parts marked *unverified* could not be cross checked).

## Compression (`unpack` 0x97eb8)

Any file may be stored compressed. The buffer may start with a `Copyright...` C string (`skip_copyright`),
then the first two bytes identify the packer: byte 1 is `0xFB`, byte 0 (with bit 0 cleared) is the pack code.
`tools/nhl/formats.py` implements every code; `tools/nhl/test_pack.py` runs the game's own decoders in an
emulator (`tools/leemu.py`) on the same buffers and compares the results. The game files use only RefPack
(the `.QFS` banks), the byte pair code (the `.BGP` drivers) and the speech code of the VIV bank.

| Code | Decoder | Notes |
|---|---|---|
| `10`/`11` | `refpack_decode` (0x97ce0) | standard EA **RefPack**: 2 byte header, optional 3 byte compressed size when bit 0 of byte 0 is set, 3 byte big endian decompressed size, then the usual 2/3/4 byte copy commands, literal runs `E0..FB` ((n&0x1f)+1)*4 bytes, stop `FC..FF` with 0-3 trailing literals |
| `30`/`32`/`34` | `bitlz_decode` (0x97740) | EA's canonical **Huffman** code: the code (+3 bytes when bit 0 is set), then a bit stream read most significant bit first (`bitlz_getbits`): 24 bits the unpacked size, 8 bits the escape byte, per code length 1, 2, ... a gamma coded number of codes until the code space is full, the symbols in code order as gamma coded steps over the byte values not yet used; in the data the escape symbol is followed by a gamma coded run (the last byte repeated) or 0 and one bit, 0 = an 8 bit literal, 1 = the end. Gamma code (`bitlz_getgamma`): k zero bits, a one, k+2 bits r: r + 2^(k+2) - 4. `32` stores the result as a running sum, `34` as a running sum of a running sum |
| `46` | `bytepair_decode` (0x97a38) | byte pair substitution (see the speech bank below); the `.BGP` drivers |
| `60`/`62`/`66`/`72` | `delta_decode` (0x97bb8) | output byte = running sum of input bytes; after the code `62FB` has 3 more header bytes, `66FB` 4, then the 24 bit size |
| `6A`/`6E` | stored | 5 byte header followed by the raw data |
| `7A` | `pack7a_decode` (0x97c2c) | run length code of fixed size units: the code (+3 bytes for `7B`), 24 bit size, unit size, size of a count (1-4 bytes); signed big endian counts: n > 0 repeats the next unit n + 1 times, n < 0 copies -n units, 0 ends |

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

All `.PPV` frames use the run length code (`blit_rle_frame`): a count byte `c` followed by one colour byte when
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
colour (`settextpos(color, shadow)`). This decodes every font of the game (`HILIGHT`, `WITTLE06`, `TEENY05`,
`MINIFO05`, `EASN`, `LINEDIT`, the large menu fonts). `SCOR3B` and `SCOR2B`, the message box fonts, are plain
1 bpp rows as well: the two complementary checkerboard halves of one dithered font, drawn on top of each other in
the colours 0x25 and 0x27.

## Sound (`loadsound`, `playsample`)

IFF **8SVX** (`FORM....8SVX`, `VHDR` with the sample rate at +12, signed 8 bit `BODY`) or RIFF WAV with a 0x2c
byte header, converted to signed by XOR 0x80. `loadsound` keeps a 16 byte header (rate, total length = one shot +
repeat, loop) before the body; `playsample(sample, driver, channel, volume)` hands the driver half of each length
(`drv_play_sample`) together with the **packed** flag: every sample `loadsound` loads is coded, two
samples per byte. These are the recordings of the front end (`MAINDESK.IFF` the main menu, `TONIGHTS.IFF`,
`GAMESUM.IFF`, `SCOUTING.IFF`, `PAUSE.IFF` on the pause screen when the music is on; the code also loads
`awards`, `awasong`, `leaguetm`, `jersey`, `coach`, `calendar`, `credits`, `title30`, `pioneer3`/`pioneer4`
`.iff` recordings that are not part of this installation); their VHDR declares 22050 Hz and
twice as many samples as the BODY holds bytes. The software mixer of the Sound Blaster driver (`mix_fill_buffer`,
and `gus_stream_fill` / `gus_dig_play` for the Gravis UltraSound) expands each byte through the table at
0xd7414 into two 8 bit steps, low nibble first, added to an accumulator that starts at 0 (signed samples):

```
nibble  0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
step  -34 -21 -13  -8  -5  -3  -2  -1  +1  +2  +3  +5  +8 +13 +21 +34
```

the Fibonacci delta code of 8SVX without the zero step, so silence is `0x78` (+1, -1). For a loop
(`MAINDESK.IFF` repeats from sample 24960, `TONIGHTS.IFF` from the start) `mix_play_sample` precomputes the
accumulator at the loop start. Decoded, the five files are 3 to 34 seconds of music without a single wrap of
the accumulator; `nhltool.py wav PAUSE.IFF OUT.wav` exports them (with the loop in a `smpl` chunk) and the
port plays `PAUSE.IFF` on its pause screen.

### Sound drivers and patch banks (`load_sound_config`, `loadpatches` 0x8ecc0)

The `.BGP` files are the sound card drivers, 16 bit MZ images packed with the byte pair code (`bytepair_decode`):
`YM30` the Adlib FM driver, `SB30` the Sound Blaster (FM through the OPL2 plus software mixed digital voices at
11025 Hz), `MT30` the Roland MT-32, `PC30` the speaker, `NL30` none. A `.SCN` file (`SBDAC`, `ADLIB`, `MT32`,
`MT32SBDA`, `PCBEEP`) names the patch file and the timbre files of the card: byte +1 the patch file number, +3 the
number of timbre files and their numbers at +0x14 (`%0.3sFF%03d.PAT/.TIM`): the Sound Blaster loads `PCFF001.PAT`
with `PCFF000.TIM` (FM) and `PCFF001.TIM` (digital), the Adlib `PCFF004.PAT` with `PCFF000.TIM` and `PCFF002.TIM`.

```
.PAT  +0 u16, +2 u8[256] sound / program id -> record index (0 = none: snd_patch_record), records of 0x14 bytes from
      +0x102: +0 type (0 FM timbre, 1 digital timbre), +1 timbre program, +2 u16 voice mask (0x1ff: any of the 9
      FM voices), +6 voices at most, +7 s8 transpose, +8 s8 fine tune (F-number units), +0xa pitch bend range in
      semitones, +0xc priority (<< 4), +0xe note length of a sound effect (x 6 ticks, 0 = 0xa0 ticks), +0xf driver
      class (bind_patch_timbres turns it into the index of the loaded driver), +0x10 the timbre pointer once loaded
.TIM  +0 u32 file size, +4 u16 n, n 4 byte keys (0x80, type, 0, program; the last one 0xffffffff), n u32 offsets
      relative to the data at 6 + 8 n (the same keyed layout as the .DIG)
      FM timbre (PCFF000.TIM, 144 of 80 bytes): +2..+0xe the OPL2 registers carrier 20/40/60/80/E0, modulator
      20/40/60/80/E0, C0, A0, B0; the driver's own modulation: +0x10 control of an envelope (+0x12 delay, +0x14
      start, +0x16/+0x18 attack step and peak, +0x1a/+0x1c decay step and floor, +0x1e sustain step, +0x20
      release step), +0x22 control of an LFO (+0x24 delay, +0x26 end, +0x28 depth, +0x2a clamp, +0x2c depth per
      modulation wheel, +0x2e rate: a 16 bit phase step a tick through a quarter sine), +0x32 control of a step
      sequence (+0x34 delay, +0x36 steps, +0x37 ticks a step, +0x38 length, +0x3a values), +0x4a ticks the voice
      stays after its note off. Controls (YM30 sub_1c6): 1 note offset, 2 F-number offset, 3 volume, 5 LFO depth,
      7 pitch bend, 8 LFO rate, 9 modulator level
      digital timbre (PCFF001.TIM, 30 of 32 bytes): +0 6, +2 the 4 byte id of the sample in the .DIG, +0x14 u32
      length, +0x18 / +0x1c u32 loop start / end (0 = none); load_timbre_file writes the sample pointer to +0xc and 11025
      to +0x12
.DIG  +0 u16 0x7ff1, +2 u16 4, +4 u16 n (30), n 4 byte sample ids (sorted), n u32 offsets relative to the data at
      6 + 8 n, signed 8 bit PCM
```

The FM driver (YM30, and the FM half of SB30) receives MIDI messages. A note gets the patch's transpose; channel 9
plays the drum patch note + 0x5c at note 60. The frequency is block = note / 12 with the F-number table
86, 91, 96, 102, 108, 114, 121, 128, 136, 144, 153, 162 (171, ... for the bends) of DS:0x117 (note 60: F-number 86
in block 5, 130.4 Hz before the operators' multipliers) plus the fine tune. The velocity (table DS:0x15f, 0.63..1)
times the channel volume (controller 7, table DS:0x19f) scales the carrier's attenuation as 63 - (63 - TL) * gain,
the modulator's too with additive synthesis. Controllers 1 (modulation, LFO depth), 7, 10 (pan), 0x40 (sustain),
0x7b (all off); the pitch bend spans the patch's range. Every 100 Hz timer tick the driver runs the timbre's
envelope, LFO and sequence and writes the registers. The digital half of SB30 mixes its voices at 11025 Hz (DSP
time constant for 0x2b11, command 0x14) and steps through a sample by the note: the table at DS:0x1f6 holds
2^((note - 60) / 12) in 4.12 fixed point, so a sample plays at 11025 * 2^(transpose / 12) Hz whatever its
recording rate (the post, 0xac, is a 22050 Hz recording).

### Sound effects of the match (`play_sfx`, `snd_play_sfx`, `snd_play_patch`)

`play_sfx(id)` (0x59884) passes the id to `snd_play_patch` unless the announcer is speaking (the goal horn 0x9c
always plays); 0x7d only raises the crowd noise, 0x90 plays 0x91. The driver plays it as a MIDI event: ids
>= 0x80 are drum notes on channel 9 (note id - 0x74, + 24 on the way to the driver: the driver's drum patch is the
id), ids < 0x80 program changes on the channels 12..15 at note 0x24; the note ends after the record's length.
The digital records hold 33 effects, `nhltool.py dig GAMEDIR OUT` exports them as `sfx_<id>.wav`. Ids used by the
game code: 0x7d/0x7e crowd loops (`update_ambient_audio`, volume from `crowd_noise`), 0x91 period horn, 0x97 one
minute warning, 0x98/0x99 pass, 0x9a slap shot, 0x9b pick up, 0x9c goal horn (the 7 second sample), 0x9d/0xa3 puck
hits a body / stick, 0xa0/0xa1 body check, 0xa2 stung, 0xa4 whistle, 0xa6 crowd, 0xaa wrist shot, 0xac post,
0xad boards, 0xae glass, 0xb0/0xb2 skates, 0xb1 body into the boards; the FM records are 0xab (the puck drop),
0x94, 0x96 and the drum kit 0x7f..0x92 of the songs.

### Songs (`music_load_kms` 0x8f13b, the sequencer `kms_track_tick`, `load_music_banks`, `play_speech`)

```
.KMS  +1 u8 tempo, +6 u8 track count, +8 u16 file offsets of the tracks (each preceded by a size byte and "TRAK").
      A track is a list of events: a delta time in steps (7 bit groups, the high bit continues) and an event byte
        < 0xd9  a note (low 7 bits, the driver gets + 24), a velocity byte (below 0x80 the running velocity is used
                instead), the length in steps (7 bit groups)
        0xd9/0xda end (return from a call), 0xdb back to the start, 0xdc program, 0xdd tempo, 0xdf controller
        number and value, 0xe2/0xe3 loop start (count)/end, 0xe4 running velocity, 0xe5 u16 pitch bend (the high
        byte is sent), 0xe6 call, 0xe7 text (length byte; the track name), 0xe8 system exclusive (MT-32 only),
        0xea marker; any other code carries one byte
.CFG  per track 16 bytes from +8: u16 mask of the MIDI channels it may use (the first is taken), +6 volume
      (controller 7, scaled by the song's volume), +7 pan
```

The timer routine `sound_timer_tick` runs at 100 Hz (the PIT is set to 11932): a track adds 128 a tick and takes a step
for every 32000 / tempo, i.e. 0.4 x tempo steps a second (24 a beat). A note stays in a table of 32 sounding notes
until its length has run out. The songs of the match are organ tunes (two to three tracks: 'left', 'right' and
the pedal), the anthems `CANADA` and `USA`, `ROCKDITI`, the stomps `SBROCKU` (the digital sample of program 0x7c),
`ADROCKU` / `MTROCKU`, and the front end pieces (`TITLE`, `ADTITLE`, `ADSUM`, `ADAWARDS`, `ADAFAN`; `MT*` for
the MT-32). `nhltool.py kms FILE.KMS --events` lists a song.

`load_music_banks` (0x7dc8b) loads the songs of a match: six per home team from the byte table at 0xd1be3
(6 bytes a team, indices into the 54 names at `off_d1b0b`, -1 none; teams above 25 use row 13), three random
ones from the 18 indices at 0xd1c8b (none of the team's, all different), the stomp of the sound card, the anthem
of the home team's country (byte at 0xcc9b0 + team: 0 Canada, 1 USA; names at 0xd1cde) and `ROCKDITI`.
`play_speech(cue)` (0x59a11) stops the running song and starts the cue's: 0..5 the team's (none: one of the
random ones), 6..8 the random ones, 9 the stomp, 10 the anthem, 11 `ROCKDITI`. The cues: 0 the intermission
(`game_loop`), 3 a home goal without the announcer (`score_goal`), 1 / 4 a power play of the home / away team
(`ref_check_announcements` with the announcer on), 2 halfway through a period, 5 late in the third, 6..8 and 11
at random stoppages, 9 with the clapping crowd clip, 10 before the game. `stop_crowd_loop` ends the song at the
puck drop (`faceoff_resolve`) and before a penalty shot.

## Announcer speech (`speech_load_bank`, `speech_queue_clip`, `speech_release_clip`)

The clips referenced in the code (`pause.cor`, `goalnum.cor`, `scor1per.bar`, `nhl.int`, `roughing.pen`, ...) are
entries of the speech bank `XBRUCE2.VIV`, an EA `0xC0FB` archive: u16 BE `0xC0FB`, u16 BE size of the index,
u16 BE entry count (344), then per entry a 24 bit BE offset, a 24 bit BE size (`read_be32` reads three bytes)
and a zero terminated name (eight `.int` names appear twice). An entry is either coded with the 4 bit Fibonacci
delta code of the menu recordings (two samples a byte, see Sound; `speech_timer` plays these with
`playsample_raw_loop`, which sets the mixer's packed flag, at 11025 Hz, so a byte lasts 1 / 5512 s:
`speech_load_bank` counts size * 100 / 5512 ticks) or packed with pack code `0x47 0xFB`
(`unpack` -> `bytepair_decode`, 0x97a38): 3 bytes, the unpacked size (24 bit BE), the escape byte, the number
of byte pairs and the pairs (code, left, right); in the data a pair code expands recursively (`bytepair_expand`),
the escape byte is followed by a literal, an escape followed by 0 ends it. The unpacked data skips a 5 byte
header and is a running sum (`speech_delta_decode`) of signed 8 bit samples at 11025 Hz. Clip types: `.num` numbers
(`0`..`99`, `01`..`09` for the seconds), `.tea` / `.frm` / `.hom` / `.awa` team names (by `team_abbrev`),
`.rnk` arenas, `.pen` penalties, `.cor` / `.bar` / `.int` phrases.

`speech_queue_clip` only loads a clip (once per sentence); `speech_release_clip` appends it to the playback
list, so the release order is what is said: `say_goal` "bos.tea goalnum.cor 12.num [pause.cor asstnum.cor
77.num [pause.cor andnum.cor 8.num]]", `say_penalty` "det.tea pennum.cor (pensnum.cor when more are queued,
andnum.cor for the next one of the same team) 19.num pause.cor 2min.cor|5min.cor|gamemisc.cor hooking.pen
pause.cor [at.cor pause.cor 12.num 05.num]", `say_penalty_shot`, `say_star` "3rdstar.cor bos.frm pause.cor
number.cor 77.num", `say_one_minute_left` "oneleft.cor" (one minute left, from `game_clock_tick`; without speech the
tone 0x97). The timer routine `speech_timer` (100 Hz) starts each clip 0x1a ticks before the previous one ends
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

## Movies (`ea_sports_intro`, `cmv_play`, `cmv_load_palette`, `cmv_next_frame`, `cmv_decode_frame`)

Two kinds of movie, read from the CD unless the installation copied them (`NHL.CFG` lists none and none is in
the game directory): `TITLE.CMV`, the intro after the EA SPORTS screen (`ea_sports_intro`: `EASCRN.QFS` with
its 200x200 mask `msk1`, the title music `TITLE30.IFF` with digital sound, else the `MTTITLE` / `ADTITLE`
song), and `CLIPnnnn.CMV`, a coach clip picked at random from `clip0001` .. `clip0050` (`coach_clip_player`,
after the intermission box score, not in the all star game: backdrop `COACHCUT.QFS`, the sound `COACH.IFF`
started on the first frame, the announcer's "coachclp" introduction). `cmv_play` shows a clip at (353, 84) of
the 640x480 screen (a 228x176 area is cleared first). Both stream the file through the CD buffer of
`cdstream_open` (300000 bytes, read in 0x2000 byte blocks, 1.5 s prefetched) and `iff_parse`. `mvi_*`
(0x86690 ..) is a second implementation of the same block codec with its own file reader; `mvi_open` is never
called. The layout below is from the code: `tools/nhl/test_pack.py` runs the game's `cmv_next_frame` on
synthetic movies and compares the frames with `formats.CmvPlayer` (`nhltool.py cmv FILE [OUTDIR]` exports
them as PNG).

A movie is a sequence of chunks: a 4 character tag and a u32 *little endian* size including the 8 byte
header (not IFF's big endian). `iff_parse` passes a chunk whose tag starts with a digit 1 .. 8 to that
secondary buffer; the players only see the others and stop at an unknown tag:

| Tag | Content |
|---|---|
| `MVIh` | header, starts a segment (`cmv_load_palette`, fresh frame buffers): +10 u16 frames, +12 width, +14 height, +16 block size (4; `mvi_print_info`'s "Block Size", not read by `cmv_*`), +18 frame rate (frames per second: a frame lasts 100 / rate ticks of the 100 Hz timer), +20 first colour, +22 number of colours, +24 the colours (3 bytes, 8 bit RGB, shifted right by 2 for the DAC) from the first colour on |
| `MVIf` | a frame: +8 u16 0 = width x height raw pixels from +10; otherwise (width / 4) x (height / 4) op bytes from +10, one per 4x4 block row by row, then the data stream of the 0xff ops |
| `MVIe` | end of a segment: the intro stops after the second, a coach clip after the third |

Frame ops (`cmv_decode_frame`; offsets of the table `cmv_load_palette` builds at +0x2c of the cmv object):
an op other than 0xff copies the block of the previous frame displaced by dx = (op & 15) - 7, dy = (op >> 4) - 7;
0xff takes the next data byte b: b != 0xff copies from the frame before the previous one with the same
displacement, b = 0xff is followed by the 16 pixels of the block (4 rows of 4). The displacement is the linear
offset dx + dy * width, so a block at the left edge copies from the end of the row above. Three frame windows
rotate (`cmv_next_frame`): the new frame is written into the oldest. Frames are always decoded but only drawn
when the player is not behind its schedule; `cmv_play` decodes a segment's frames while the frame count of its
`MVIh` is above 1 (it counts down per frame), the intro decodes every frame.

## Databases and saves

| File | Layout |
|---|---|
| `teams.db`, `carteams.db` | 28 records of 0x2e8 bytes (26 teams + the two all star teams): +0 abbreviation (5), +5 city and nickname (21), +0x1a short name (13), +0x28 the season and +0x3a the play-off block of the team (u8 GP, W, L, T, then u16 goals for, goals against, power play goals, advantages, power play goals against, times short-handed, penalty minutes; `season_record_result`), +0x4c 25 x i32 offsets of the skaters in `key.db` (-1 = empty), +0xb0 3 x i32 goalie offsets, +0xbc the line table (`db_load_team_roster`, `line_energy`): 4 forward lines x 3 (LW C RW), 3 defence pairs x 2, 2 power play units x 5, 2 penalty killing units x 4, 2 goalies (+0x24 / +0x25), 2 extra attackers, then 8 scratches (+0x28..+0x2f), all as roster indices 0..27 (0x64 = unset), +0x11c 84 x i32 the team's regular season games as offsets into `schedule.db` (2 + game x 6), +0x26c 28 x i32 its play-off games (kept for the teams humans play), +0x2dc the nine ratings of the scouting report |
| `key.db` | player records of 0x34 bytes (`db_read_player`): +0 team (0xff a free agent of the Central Registry), +1 jersey number, +2 position letter (C L R D G), +3 first name (16), +0x13 last name (16), +0x24 i32 offset into `att.db`, +0x28 into `career.db`, +0x2c into `season.db`, +0x30 portrait id ("0001") |
| `att.db` | ratings 0..15 (`put_player_on_ice`): skaters 0x14 bytes: hand (1 = left, right handed players are drawn mirrored), agility, speed, weight class, shot power, aggressiveness, defensive awareness, shot accuracy, (unused), passing, offensive awareness, awareness, checking, stick handling, +0xe..+0x13 further ratings (faceoffs, ...); goalies 0x10 bytes: hand, +1..+5 (checking, passing, offensive awareness, stick handling, shooting), agility, speed, weight, +0xa/+0xb reaction / awareness |
| `season.db`, `career.db` | per player statistics records pointed to by `key.db`. `season.db` skaters 0x2f bytes: the season at +0 and the play-offs at +0x12, each u16 GP, G, A, PTS, PPG, SHG, PIM, SOG, +/-; +0x26 / +0x27 month and day an injured player returns (`db_load_team_roster` marks him injured before that date; only the multi-player merge `merge_delta_words` writes it); +0x28 the three stars. Goalies 0x36 bytes: blocks of 0x16 at +0 / +0x16, u16 GP, W, L, T, SO, -, minutes, GA, GAA x 100, SA, save percentage x 1000; the stars at +0x30. `career.db` 0x28 bytes, scaled to 84 games by the league's game simulator |
| `schedule.db`, `LSSCHED.DB` | u16 the number of games played (`league_calendar_flow`), then 1197 game records of 6 bytes (`db_read_record2`, `schedule_write_record`): month, day, home team, away team, home goals, away goals (0xff = not played). Records 0..1091 are the season (26 teams x 84 games / 2, October 5 to April 14), from offset 0x199a the play-offs: 15 series x 7 game slots (all 0xff for the games a series did not need): series 0..3 the first round of the West (the conference of `unk_c55e9`), 4..7 of the East, 8..9 / 10..11 the second rounds, 12 / 13 the conference finals, 14 the Stanley Cup final. The games played count marks the stages: 0x444 the season is over, 0x47c the second round, 0x498 the conference finals, 0x4a6 the final, 0x4ad the play-offs are over. Series are 2-2-1-1-1 or 2-3-2 (`playoff_set_series`), of 1, 3, 5 or 7 games (option flags >> 12). `LSSCHED.DB` holds the 90 games of the 1994 play-offs with their results (Detroit - San Jose 4-5, 4-0, 3-2 ... the Rangers' 3-2 in game 7 of the final), the "'93 - '94 Play-Offs" of the statistics screens; `nhltool.py schedule FILE` lists them |
| `gsummary.db` | the events of the game being played, for the box score (`begin_game_session`, `gsummary_append_record`, `gsummary_write_final`): an 11 byte header (+1 month, +2 day of a league game, +3 home team, +4 away team, +5 u16 the number of records written), 11 byte events, and an 11 byte trailer that is written again behind every new event (+1 home goals, +2 home shots, +3 away goals, +4 away shots). Events: `1` goal (`announce_goal`): team, scorer, assists 1 and 2 (0xff none), flags (2 short-handed, 4 power play), period, minutes, seconds, the goalies in both nets; `2` penalty (`record_penalty`): team, player, infraction (the penalty type - 9), minutes (0xff a misconduct), period, minutes, seconds; `3` injury (`announce_injury`): team, player, 1 out for the game, period, minutes, seconds; `4` the trailer of a period (home goals, home shots, away goals, away shots), rewritten behind every new event and closed at the intermission, so that a finished game holds one per period. Players are roster indices (0..27), times elapsed in the period. The installation's file is an empty summary (NYR - VAN); `nhltool.py gsummary FILE` |
| `PINFO.DB`, `PLAYER.ID` | league information (`pinfo_db_create`, `league_save_db`): `PINFO.DB` +0 u16 the team of the league's owner, +2 u16, +4 u16 (0xffff once the league is saved), +6 13 bytes status text ("saved"), +0x13 u16, +0x15 11 bytes the master password (checked by `master_password_prompt`; `password_scramble` XORs passwords with "NHLHockey"), +0x20 26 team entries of 0x1e bytes (+0 the coach's name (11), +0xb the password scrambled with "NHLHockey" (11), +0x16 1, +0x17 1 = played by a human, +0x18 2). New leagues of the port write +0 the number of human teams and +2 the first of them (`new_league_dialog`). `PLAYER.ID`: +0 team byte, +1 11 byte name, +0xc 13 byte league directory, +0x19 4 bytes. *From the code; no league exists in this installation* |
| `GAME.SET`, `GAME.SAV` | `GAME.SET` the settings block of a league (see `apply_settings`, copied by `import_game_set`). `GAME.SAV` the saved game (`savegame_io`, `read_saved_game`): in a league first the league state of `league_save_db` (u32 x 3, three 4 byte counters including the games played, two 13 byte league directories, the 6 byte record of the current game), then u32, 17 x 0x66 byte entity snapshots, 2 x 0xd4 byte team snapshots, 2 x 0x30 byte line tables, ... *From the code* |
| `*.nhl`, `*.po`, `*.lp` | a saved exhibition, the directory of a play-off series, of a league (the seven databases, `PINFO.DB`, `GAME.SET`, `GAME.SAV`) |
| `NHL.CFG`, `ALLFILES.TXT` | `NHL.CFG` (`load_nhl_cfg`, `load_cfg_palette`, `load_sound_config`): line 1 the sound card as `%04x`, an index into the table at 0xd243a (0 none, 1 PC speaker, 2 AdLib, 3 Sound Blaster, 4 MT-32, 5 Gravis UltraSound; rewritten when the card changes), line 2 the CD drive letter (`ALLFILES.TXT` is read from its root), then the files copied to the hard disk; every other file of `ALLFILES.TXT` is read from the CD (`file_on_disk[]`). The installation's file: Sound Blaster, drive D, 441 files (`nhltool.py cfg NHL.CFG`). `SND.CFG` (one byte, 2) is not read by `HOCKEY.EXE` |
| `*.HI` | saved instant replay highlights (`replay_save_highlight`) |
| `TITLE.CMV`, `CLIPnnnn.CMV` | the intro and the coach clip movies (on the CD), see Movies |

Settings block (`apply_settings`): +0 u32 flags, +4 league directory (13 chars), +0x11 and +0x31 strings, +0x51 home
team id, +0x55 away team id, +0x59 option flags, +0x5d, +0x61, +0x65 controller of player 1 (0 none, 1 mouse,
2 joystick 1, 4 joystick 2, 8 keyboard), +0x69 controller of player 2, +0x6d period length, +0x71.
