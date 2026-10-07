# NHL Hockey – Godot 4 port

A Godot 4.3 project rebuilding EA Sports NHL Hockey (DOS, 1994) from the disassembly in
[`re/nhl_hockey`](../../re/nhl_hockey). The simulation is a routine by routine translation of the decompiled
game; the graphics, team colours, rosters, HUD, speech, sound effects and music are read from the original game files, which
live in `re/nhl_hockey` of this repository (the project finds that directory on its own when it runs from a
checkout; another installation can be given with the `NHL_GAME_DIR` environment variable or `user://settings.cfg`,
key `files/game_dir`). Without the files it runs with coloured placeholders.

![Boston against Detroit](screenshots/bos_det_play.png) ![Edmonton faceoff](screenshots/edm_mtl_faceoff.png)
![Toronto at the net](screenshots/tor_mtl_net.png)

```
godot --path godot/nhl_hockey            # run: the intro, demo games until a key, then the EA SPORTS desk
NHL_NO_INTRO=1 godot --path godot/nhl_hockey                            # straight to the desk
NHL_HOME=0 NHL_AWAY=4 godot --path godot/nhl_hockey                     # a match without the front end (0..27)
godot --path godot/nhl_hockey --headless --import                       # first run: build the class cache
godot --path godot/nhl_hockey --headless --script tests/run_tests.gd    # self test (exit code 0 = pass)
NHL_HOME=5 NHL_AWAY=9 NHL_FAST_STEPS=600 NHL_SCREENSHOT=out.png godot --path godot/nhl_hockey   # screenshot and quit
NHL_UI_SCRIPT="wait:400;click:52,8;wait:60;shot:menu.png;quit" godot --path godot/nhl_hockey       # scripted front end
```

The front end works with the mouse like the original (the arrow keys and the joystick move the pointer too,
Enter / the first button clicks, Esc / the second button cancels). Leagues, play-off series, saved games
and edited databases are kept under `user://` (`leagues/NAME.LP`, `leagues/NAME.PO`, `saves/NAME.NHL`,
`databases/NAME`), `GAME.SET` holds the settings of the desk. The commands of `NHL_UI_SCRIPT` are listed in
`view/App.gd`.

Controls (player 1, home team): arrows skate, Alt = A (pass / switch player), Space = B (shoot / body
check), Ctrl = C (hook, poke check). Player 2 (`NHL_USER2`): I J K L skate, U = A, O = B, P = C. At the
faceoff hold a direction and press A when the puck drops. A or B skips the anthem.

Hotkeys of the original (`handle_hotkey`): Esc the pause screen (Back to Game, Exit, the goalie choice,
Go To Replay), R the instant replay, Tab the numbers of every player, S the sound effects and the crowd, M the
organ music, F1-F4 / F5-F8 the lines of player 1 / 2, F9 / F10 pull or return the goalie. In the replay the
mouse works the VCR panel (rewind, step back, pause, step forward, play, fast forward, the recorded
camera, exit) and a click on the ice follows that player; with the keyboard Left / Right select a button,
A holds it, Esc or R leaves.

Team indices (`NHL_HOME`, `NHL_AWAY`, or `match/home` and `match/away` in `user://settings.cfg`): 0 BOS, 1 BUF,
2 CGY, 3 CHI, 4 DET, 5 EDM, 6 HFD, 7 LA, 8 DAL, 9 MTL, 10 NJ, 11 NYI, 12 NYR, 13 OTT, 14 PHI, 15 PIT, 16 QUE,
17 STL, 18 SJ, 19 TB, 20 TOR, 21 VAN, 22 WSH, 23 WPG, 24 ANA, 25 FLA, 26/27 all stars.

## What is ported

The simulation is translated routine by routine from `re/nhl_hockey/decomp/*.c`; the source routine of
every function is given in its doc comment. The fixed point arithmetic of the original is kept so the
behaviour matches the DOS game (see "Porting conventions" below).

| Area | File | Source routines / files |
|---|---|---|
| Static tables | `data/tables.json`, `data/Tables.gd` | extracted by `tools/nhl/extract_tables.py`: animation sequences, direction vectors, frame and stick offsets, skating tables, faceoff spots and lineups, AI zones, shot targets, stoppage durations, entity init records, rink logo placement, marker frames |
| Game files | `autoload/GameFiles.gd` | case insensitive access to the installation directory, `loadfile` / `loadfile_auto`, the 23 sprite bank names of `load_sprite_banks` |
| Shape banks | `loaders/Shpi.gd`, `loaders/RefPack.gd` | RefPack, SHPI directories, plain and run length coded frames (`blit_rle_frame`), hotspots, palettes |
| Team colours | `loaders/GamePalette.gd` | `load_team_palettes`: RINKPAL.QFS + HOMEPALS.BIN / AWAYPALS.BIN, the colour remap tables of `blit_sprite` and their mirrored variant |
| Rink | `loaders/RinkTiles.gd` | `load_rink` / `load_rink_tiles`: the RINK.QFS surface with the centre ice logo of the home team (TEAM.TIL / .MAP, mirrored second half for EDM, LA, NJ, PIT) |
| Rosters | `loaders/Database.gd` | `db_open_files` / `db_load_team_roster` / `db_read_player`: TEAMS.DB, KEY.DB, ATT.DB (names, numbers, positions, ratings, the line table) |
| Sound cards | `audio/MusicPlayer.gd`, `loaders/FmBank.gd`, `loaders/Sounds.gd` | `load_sound_config`: the card chosen in the settings (NHL.CFG; `NHL_SOUND` for a match without the front end) and its SCN file, patch file and timbre files (`loadpatches`); the drivers compiled into HOCKEY.EXE: Sound Blaster (FM + `sbdac_*`), AdLib (`adlib_drv_*`, the effects as FM timbres of PCFF002.TIM), PC speaker (`pcspk_*`), MT-32 (`mpu_drv_*`), none; `snd_play_patch` for the effects, `update_ambient_audio` / `sound_pause_all` for the crowd |
| Digital driver | `audio/DacDriver.gd` | `sbdac_*` and the software mixer `mix_*`: four voices at 11025 Hz with their 8 bit volume tables and clipping, the voice masks and priorities of the patch records, voice stealing, pitch bend; the effects, the crowd's roar (0x7d, voice 2) and murmur (0x7e, voice 3), the speech (voices 0 / 1), the stomp and the front end's recordings (voice 3) |
| PC speaker | `audio/PcSpeaker.gd` | `pcspk_*`: one voice (as in the original), the timbre's envelope, LFO and note sequence moving the PIT divisor of the note, `pcspk_hw_update` |
| MT-32 | `audio/Mt32.gd` | `mpu_drv_send_midi`: the MPU-401 byte stream (MT32HOCK.KMS's set-up, the MT* songs, the effects on the rhythm part), heard through a small stand-in synthesiser (see below) |
| Speech | `loaders/Viv.gd`, `sim/Speech.gd`, `view/Announcer.gd` | `speech_load_bank` (XBRUCE2.VIV: byte pair packed clips and 4 bit Fibonacci delta coded ones), the sentences of `say_goal`, `say_penalty`, `say_penalty_shot`, `say_star`, `say_time_remaining`, `say_game_intro`, played back to back like the timer routine `speech_timer` |
| Music | `loaders/Kms.gd`, `audio/KmsPlayer.gd`, `audio/FmDriver.gd`, `audio/Opl2.gd`, `audio/DacDriver.gd`, `audio/MusicCues.gd`, `audio/MusicPlayer.gd` | `music_load_kms` (KMS + CFG), the sequencer of the 100 Hz timer (`sound_timer_tick`, `kms_track_tick`, the note table, `snd_play_patch` for the FM effects), the FM driver (`adlib_drv_*`, also YM30.BGP: voices, the timbres' envelopes, LFOs and step sequences, levels, frequencies), the YM3812 computed sample by sample at 49716 Hz (ROM tables, envelope generator, feedback, the YM3014 DAC; natively in `native/opl2` where the library is built, else in GDScript), each track sent to the driver of its program's record class (`kms_track_tick`), `load_music_banks` / `play_speech` (the home team's songs, three random ones, the anthem, the card's stomp) |
| Fonts | `loaders/Vfn.gd` | `setfont` / `printstr`: 1 bpp VFN fonts (HILIGHT, WITTLE06, TEENY05...) |
| Entities and teams | `sim/Entity.gd`, `sim/Team.gd` | the 17 x 0x80 byte entity records and the two team records (STRUCTURES.md) |
| Animation | `sim/Anim.gd` | `set_animation`, `advance_animation` |
| Step loop, physics | `sim/Sim.gd` | `sim_tick`, `sim_update_players` (update order, friction, speed clamp, gravity), `move_entity`, `collide_boards`, `collide_corner` (puck over the glass), `collide_net` (goals, posts), `collide_player_net` (players against the net), `collide_neighbours`/`collide_pair` (body contact), `put_player_on_ice` (ratings of the database into the entity, right handed players mirrored) |
| Controls | `sim/Sim.gd`, `sim/Controls.gd` | `control_player` (pass, shot, one timer, switch, hook, body check), `faceoff_control`, `apply_skating` with skating backwards, `skating_turn`, `skating_accelerate`, `stop_skating`, `brake`, `goalie_move`, `switch_to_nearest`, `find_switch_target` |
| Puck | `sim/PuckLogic.gd` | `puck_update`, `predict_puck_goal_line`, `update_carrier`, `puck_check_players`, `puck_player_interaction`, `goalie_save`, `puck_hits_player`, `attach_puck_to_stick`, `take_puck`, passes (`do_pass`, `pass_to_entity`, `pass_lead`, `pass_lane_ok`), shots (`start_shot`, `shot_control`, `do_shot`, `shot_setup`), checking (`body_check`, `hook_button`, `start_hook`, `start_poke_check`, `try_block_shot`, `resolve_body_check`, `knock_down`) |
| Rules | `sim/Rules.gd` | `sim_game_state`, `update_stoppage`, `process_infractions`, `start_stoppage` (faceoff spot selection), `queue_infraction`, `penalty_box_update` (serving penalties), `penalty_timers`, `goal_ends_penalty`, `game_clock_tick` (24 ticks per second), `score_goal`, `setup_faceoff` (period end), `check_offside`, `check_icing`, `update_offside_flags`, `two_line_pass_check`, `count_defenders_ahead`, the faceoff positioning of `ai_puck_faceoff2`, `faceoff_resolve`, `all_goto_positions` |
| AI | `sim/AI.gd` | the state dispatch and the handlers `defo defd wingd wingo centd cento score goalie goalieget puckc nearest shoot passrec fowait faceoff pnorm pshad pnothing pface pface2 rfaceoff rnorm rcallpen rpickup rgotofo rpointgoal rgetnew agotofo initper abreak` plus the helpers `ai_skate_towards`, `ai_chase_puck`, `ai_try_check`, `ai_near_carrier_check`, `ai_ref_positioning`, `ref_skate_to_point`, `ai_consider_shot`, `ai_offense_decision`, `ai_choose_pass_target`, `ai_desperation_shot`, the one timer logic (`one_timer_step`) |
| Camera | `sim/Sim.gd` | `update_camera` (follows the carrier, the referee during stoppages, the faceoff dot) |
| View | `view/Main.gd` | `game_loop` / `draw_sprites`: 320x168 window onto the 384x592 rink surface, y-sorted sprites through the team's remap table, mirrored frames, nets (frames 404/405), puck, the markers under the controlled players and the carrier (`draw_sprites`), jersey numbers and position letters under the skates (`draw_player_number`), queued sound effects and the crowd loop (`play_sfx`, `update_ambient_audio`) |
| Scoreboard | `view/Hud.gd` | `draw_clock`, `draw_score_digits`, `draw_clock_full`, `draw_line_box`, `draw_energy_bar`, `draw_penalty_clocks`, `draw_message_box`: the 320x32 scoreboard window with the SCRBRD1.PPV panels and digits |
| Lines | `sim/Lines.gd` | `assign_line_positions`, `apply_line_change`, `handle_line_change`, `choose_line`, `cpu_line_change`, fatigue (`regenerate_energy`), goalie pulling (`maybe_pull_goalie`, `late_game_pull_goalie`), `choose_goalie` |
| Ceremonies | `sim/Ceremonies.gd` | the anthem (`match_sequence`, `ai_anthem`), the end of a period and of the game, the goal celebration, the three stars (`three_stars_sequence`, `compute_three_stars`), the Stanley Cup presentation |
| Info panel | `sim/InfoPanel.gd`, `view/PanelView.gd` | the panel of the stoppages (`info_panel_open`, `load_cutscene_clip`, `show_penalty`, `announce_goal`, `ref_check_announcements`), the music cues (`play_speech`) |
| Replay | `sim/Replay.gd`, `sim/ReplayFrame.gd`, `view/VcrView.gd` | `replay_record_frame`, `replay_seek_frames`, `instant_replay` / `replay_control_loop` with the VCR panel of GADGET5.PPV |
| Crowd | `sim/Crowd.gd` | the fans, photographers and benches (`start_crowd_figure`, `bench_cheer`, `update_effects`) |
| Pause screen | `view/PauseMenu.gd`, `frontend/FrontEnd.gd` | `pause_menu` (0, 1 the intermission, 2 after the game): the EA desk, the menu bar, Back to Game, the goalie choice, Go To Replay, the settings, the line editor, the statistics, Save Game, the Sports Desk, Exit (`PauseMenu.gd` is the screen of a match started without the front end) |
| Front end | `frontend/FrontEnd.gd`, `ui/Screen8.gd`, `ui/Ui.gd`, `ui/Menus.gd` | `main`, `loading_screen`, `frontend_main_menu` (the EA SPORTS desk), `run_menu` / the menu bar (the 32 byte menu records of the executable, every callback a method of the same name), `message_dialog`, the buttons, text entry, `play_game`, `end_match_from_period` / `end_match_from_loop`: a 640x480 256 colour frame buffer with the original coordinates, colour indices and palette fades |
| Intro, credits | `frontend/IntroScreens.gd` | `intro_sequence`, `ea_sports_intro`, `demo_game` (computer against computer, 60 second periods, until a key), `credits_screen` (the 0x1d pages of the executable's credits) |
| Exhibition | `frontend/GameScreens.gd`, `frontend/BoxScore.gd` | the locker room (`locker_room_screen`: teams and controllers), `exhibition_mode`, the scouting report (`scouting_report_screen`), tonight's line-ups (`lineups_screen`), the box score and summaries (`boxscore_screen`), the scores around the league (`league_scores_init` / `advance`), Game Statistics (`game_statistics_screen`), the scratches, Save Game (`broadcast_booth_screen`, `sim/SaveGame.gd`) |
| Settings | `frontend/SettingsScreens.gd`, `frontend/Session.gd` | `apply_settings` / `save_settings` (the 0x75 byte block of GAME.SET), the exhibition / game / league / play-off settings dialogs, the controllers of the two players, the sound settings |
| Line editor | `frontend/LineEditor.gd` | `edit_lines_screen_b`, `draw_lines_screen`, `edit_lines_keys`: the 40 places of the line table, before and during the game |
| Statistics | `frontend/StatsScreens.gd` | `standings_table`, `team_stats_screen`, `stats_table` (leaders), `player_stats_screen`, `player_card_screen`, `goalie_card_screen`, the statistics hubs; '93 - '94, a league's season or play-offs |
| Leagues | `sim/League.gd`, `frontend/LeagueScreens.gd` | New League (`new_league_mode`, `new_league_dialog`, the team grid `team_info_screen`, passwords), Open (`league_select_screen`), Next League Game (`league_calendar_screen`, `league_calendar_flow`, `calendar_screen`), the schedule (SCHEDULE.DB), the statistical game of the teams nobody plays (`league_sim_game`), `league_play_day`, `season_record_result` (TEAMS / SEASON / KEY / CAREER written back), the play-offs (`playoff_make_round1..final`, `playoff_set_series`, the bracket `stanley_cup_tree_screen`), New Play-Off Series, the League Manager entries, the awards |
| Central Registry | `frontend/Registry.gd` | `menu_central_registry` / `database_screen`: trades, free agents, new players, a team's lines, databases saved and loaded by name |

The headless test (`tests/run_tests.gd`) checks the RefPack decoder, the tables, the animation stepping, a
complete game start (opening faceoff after about 4 seconds, CPU players moving, the clock running), the
skating controls, a shot into the empty net (goal, whistle, faceoff at centre ice), the end of a period
(teams switch ends), a hooking minor served in the box, a 6000 step game without script errors, and against
the game files: the 1134 sprite frames, the palette and remap tables, the rink with the Boston logo, the
scoreboard shapes and fonts, the databases (Ray Bourque #77 D, Jon Casey, the Boston lines), a Boston against
Detroit game dressed from the databases, the sound bank (30 samples by id, goal horn, crowd loop, the post's
rate), the speech bank and its sentences, line changes, the match rules, the ceremonies, the replay, the crowd,
and the music: the 144 FM timbres, every song of the match tables, the sequencer's first notes and their
frequencies, the FM kick drum's sweep, the puck drop effect, the digital stomp, the cues of a Boston and a
Montreal home game and the power play flags.

## Verified against the original

`tools/nhl/golden.py` runs routines of HOCKEY.EXE itself in an emulator (`tools/leemu.py`: the LE image
mapped at its linear addresses, port I/O caught, a few routines such as `play_sfx` or `score_goal`
replaced by recorders) on fixed and random inputs, and writes what they produce to `tests/golden/*.json`
(the large ones gzipped);
the headless test feeds the same inputs to the port and compares, field by field:

| Golden data | The original's routines | Cases | Compared |
|---|---|---|---|
| `rng.json` | `randomrange`, `rand` / `srand` | 7 seeds x 64 | every value and the final seed |
| `fm_driver.json` | the AdLib driver (`adlib_drv_init` / `send_midi` / `tick` and the `opl_*` layer) | 4 MIDI sequences (an organ note with bend and modulation, the drum kit, the match's FM effects, 60 notes over 4 channels with stealing, sustain and all notes off) | the OPL2 registers after every 100 Hz tick |
| `pc_speaker.json` | the PC speaker driver (`pcspk_*`) | 8 effects | the gate and the PIT divisor every tick |
| `physics.json.gz` | `approx_distance`, `direction8` | 200 vectors | the results |
| | `collide_boards`, `collide_corner`, `bounce_off_boards`, `puck_spin` | 300 puck and skater states at the boards and corners | the entity record, the sounds, the seed |
| | `apply_skating`, `skating_turn`, `skating_accelerate`, `stop_skating`, `brake`, `goalie_move` | 400 skater, goalie and referee states (100 on seeds that hit the fatigue step) | velocity, heading, animation, flags, the team's energy word, the seed |
| | `collide_net`, `collide_player_net`, `net_push_off` | 400 states at the nets: goals, posts, the roof, the frame, nets knocked off | the record, the goal, the infractions, the net's velocity, the seed |
| | `move_entity`, `collide_neighbours`, `collide_pair`, the draw order | 300 clusters of team mates | every record of the cluster, the draw order, the seed |
| | `advance_animation` | 500 animation states of 81 animations (frames, durations, the ends, the board pins) | the record, the stride sounds |
| | `puck_check_players`, `puck_player_interaction`, `goalie_save`, `puck_hits_player`, `attach_puck_to_stick`, `take_puck`, `update_carrier`, `shot_landed`, `two_line_pass_check` | 800 situations of the puck among players, goalies and the referee (loose, carried, shots in flight, first touches, icing) | every record, the carrier, the sounds, infractions, knock downs and user switches in order, the touch, pass and icing state, the team records (the last carriers, shots, faceoffs, passes), the players' and goalies' shots, the seed |
| | `collide_pair` (opponents), `goalie_collision`, `resolve_body_check`, `resolve_hook_hold`, `resolve_dive_hit`, `penalty_odds`, `breakaway_foul`, `facing_boards`, `knock_down`, `knockdown_position`, `crowd_reaction_sfx` | 1800 body contacts among both teams, goalies, the referee and the puck, in open ice, along the boards, in the corners and at the nets: `move_entity`, and `resolve_body_check` and `knock_down` called directly | every record (the state stack too), the carrier, the sounds, penalties, injuries, bench cheers and stoppages in order, the penalty shot, the referee's hits, the crowd, the teams' hits, the seed |
| | `puck_update`, `predict_puck_goal_line`, `check_icing`, `check_offside`, `note_breakaway`, `count_defenders_ahead`, `update_offside_flags`, `end_penalty_shot` | 800 states of all 17 entities with the puck crossing the blue and red lines, carried, standing still, on a penalty shot | every record, the carrier, the calls in order, the prediction, the frozen puck and penalty shot timers, offside and icing state, the touch, the teams' flags and breakaways, the seed |
| | `do_pass`, `pass_to_entity`, `pass_lead`, `pass_lane_ok`, `isqrt32`, `start_shot`, `shot_control`, `do_shot`, `shot_setup` | 1100 passes (aimed, blind, direct, led, the goalie's clearance), lanes, wind ups and releases with every aim and power, with and without a carrier, on penalty shots | every record (the pass flags, the receivers' timers), the shot power and aim, the touch and shot state, the users, the teams' passes, the sounds, the seed |
| `ai.json.gz` | `ai_state_handlers` through `AI.dispatch`: the positional states (`ai_defense_offense`, `ai_defense_defense`, `ai_wing_defense`, `ai_wing_offense`, `ai_center_defense`, `ai_center_offense` with `ai_skate_towards`, `ai_choose_direction`, `ai_near_carrier_check`, `ai_try_check`); the puck states (`ai_nearest_to_puck`, `ai_puck_carrier` with `ai_consider_shot`, `ai_offense_decision`, `ai_choose_pass_target`, `carrier_scan_opponents`; `ai_shoot`, `ai_pass_receiver` with `one_timer_step`, `ai_breakaway` with its lane) | 600 + 500 random moments of play (both teams, the puck loose or carried, the referee, the team records, fifty globals, the scratch words the original reads as an earlier routine left them, the stack below the call filled with garbage) | all 17 records, the globals, the team records, the calls, the seed |

All of them match. The comparisons found and fixed, among others: the distance (the original's is
|dx| / cos of the vector's angle from its arctangent and sine tables, not an octagonal estimate), the
corner, glass and post rules, the puck's jump and spin off the boards, the goalie turning the other way,
a stride counter the port had invented, the draw order deciding which players collide, the net knocked
off its pegs, the frame shown at most every 5 steps with the skate stride sound, who gets to a loose puck
(a goalie's reach with the stick, the skaters' 14 around their frame, the stick blade, the body), the
steal odds and the hold speed, deflections off a goalie, icing called only when the other team touches
the puck, the two line pass against the right goal line, the referee's hits counted for the home team,
the injury that stops the play at once, a skater turning on the spot by the direction of his whole
velocity, the blue line crossing noting a breakaway, the goal line prediction counting down every step
and wrapping like the original's 16 bit words, the flat puck only on the ice, the pass lead solved with
the original's approximate square root and the shared shot power, the puck's pickup timer during a led
pass, a weak shot's sound, the scatter of a shot and its lift, a blind pass without a direction reading
the random seed past the end of the direction table, and every FM register of the AdLib driver
(`audio/FmDriver.gd` is a literal port). Running
whole games beside them showed one more departure: the centre lost the puck chasing role to a line
change during play (the original changes lines there only while the play is stopped).

The workflow `.github/workflows/nhl.yml` runs, on every change of the tools, the port or the game files:
the decoders of `tools/nhl/formats.py` against the game's own (`tools/nhl/test_pack.py`), `golden.py`
again (its output must equal the committed data, `tools/nhl/golden_check.py`), the Godot tests on the committed OPL2 library, and the
library built from source with the tests again.

## Not ported yet, and known simplifications

- The files that are on the CD only are replaced: the intro logos and the title video (the loading screen
  with the title song stands in), the credits' background and photographs (the NHL emblem), the calendar's
  pictures (drawn cells), the play-off tree's logos (SRLOGO at half size), the mouse pointer (an arrow), the
  front end recordings that the floppy files lack, and the .INT clips of the announcer (goodnight, the
  line-ups).
- The multi-player league of the original (every human team plays from its own copy of the league files,
  `league_merge_files` puts them together) is folded into one set of files: the games of the computer
  teams are simulated after each human game, so there is nothing to merge.
- Injuries do not carry over from one league game to the next; neither do they in the original, whose
  roster loader reads a return date (SEASON.DB +0x26 / +0x27) that nothing but the multi-player merge writes.
- Sound: the MT-32's sound is its own (LA synthesis and the PCM samples of its ROMs, neither part of the
  game): the port sends it exactly what the game sends but plays the messages on a small stand-in
  synthesiser (a waveform and an envelope per program family, noise for the rhythm part). The Gravis
  UltraSound plays like the Sound Blaster (its drivers need the GUS's own patch files). The OPL2's rhythm
  mode is not modelled (the drivers never set it). The chip runs natively through the GDExtension in
  `native/` (built for Linux x86_64 in `native/bin`; `native/opl2/CMakeLists.txt` builds it for other
  platforms); without the library the same arithmetic runs in GDScript, which costs about half a
  CPU core for six sounding channels.
- The period label under the clock is an addition (the original shows the period on the pause screen).

## Porting conventions

- Keep the fixed point scale of the original (positions 16.16, velocities 16 bit, `pos += 16 * v` per
  step, 60 steps per second) so that routines can be translated literally from `decomp/*.c`.
- World coordinates: x across the rink (±160 at the boards), y along the rink (goal lines at ±232, blue
  lines at ±78, boards at ±264), screen = (x + 192, 320 - y) on the rink surface, height z lifts a sprite
  by 3z/2. Entity flag 0x80 (`F_ATTACK_UP`) marks the team that shoots at the +y net; all AI tables are
  stored in that frame and negated for the other team, exactly like the original does.
- The `step()` order mirrors `sim_update_players`: for each entity animation, timers, physics, user
  control, AI state handler, goalie crease clamp, movement and collisions; then the puck clamps and the
  camera. Entities are updated in slot order, so the puck (slot 14) always sees the players' new
  positions.
- Ratings are the 0..15 values of ATT.DB mapped like `put_player_on_ice` (see `Sim.dress_player`); line
  slots are 0 goalie, 1 LD, 2 RD, 3 LW, 4 C, 5 RW, which is the order of the position letters in NUMSHP.PPV
  and of the line table in TEAMS.DB.
- Decompiler artefacts to be aware of when reading `decomp/*.c`: `*(short *)(param_1 + 10)` with an
  `int` parameter is the puck height (+0xa), with an `int *` parameter it is the stuck timer (+0x28);
  JSON numbers load as floats in Godot, so `Tables.gd` converts every table to integers.
