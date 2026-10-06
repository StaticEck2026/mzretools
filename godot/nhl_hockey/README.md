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
godot --path godot/nhl_hockey            # run (Boston against Detroit; NHL_HOME / NHL_AWAY pick other teams, 0..27)
godot --path godot/nhl_hockey --headless --import                       # first run: build the class cache
godot --path godot/nhl_hockey --headless --script tests/run_tests.gd    # self test (exit code 0 = pass)
NHL_HOME=5 NHL_AWAY=9 NHL_FAST_STEPS=600 NHL_SCREENSHOT=out.png godot --path godot/nhl_hockey   # screenshot and quit
```

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
| Sound | `loaders/Sounds.gd`, `loaders/FmBank.gd` | `snd_play_patch`, `loadpatches`: the patch bank PCFF001.PAT with the FM timbres of PCFF000.TIM and the digital ones of PCFF001.TIM, the 30 samples of PCFF001.DIG found by their ids, played at 11025 Hz shifted by the patch's transpose, loops and note lengths; 8SVX / WAV samples |
| Speech | `loaders/Viv.gd`, `sim/Speech.gd`, `view/Announcer.gd` | `speech_load_bank` (XBRUCE2.VIV, byte pair packed clips), the sentences of `say_goal`, `say_penalty`, `say_penalty_shot`, `say_star`, `say_time_remaining`, `say_game_intro`, played back to back like the timer routine `speech_timer` |
| Music | `loaders/Kms.gd`, `audio/KmsPlayer.gd`, `audio/FmDriver.gd`, `audio/Opl2.gd`, `audio/DacDriver.gd`, `audio/MusicCues.gd`, `audio/MusicPlayer.gd` | `music_load_kms` (KMS + CFG), the sequencer of the 100 Hz timer (`sound_timer_tick`, `kms_track_tick`, the note table, `snd_play_patch` for the FM effects), the FM driver YM30.BGP (voices, the timbres' envelopes, LFOs and step sequences, levels, frequencies), a model of the OPL2 chip, the digital voices of SB30.BGP, `load_music_banks` / `play_speech` (the home team's songs, three random ones, the anthem, the stomp) |
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
| Pause screen | `view/PauseMenu.gd` | `pause_menu`: the EA desk, the menu bar, Back to Game, Exit, the goalie choice, Go To Replay |

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

## Not ported yet, and known simplifications

- The front end: the menus, team selection, settings, line editor, statistics and standings screens, season and
  playoff mode, save games. The pause screen shows their entries but only Back to Game, Exit, the goalie
  choice and Go To Replay work. Teams are picked with `NHL_HOME` / `NHL_AWAY`.
- Sound: the port plays what the Sound Blaster plays (SBDAC.SCN: FM music and FM effects through the OPL2,
  digital effects, speech and the stomp through the DAC); the Adlib, MT-32 and speaker variants are not
  modelled. The OPL2 is a model, not a cycle exact emulation (envelope generator per 16 samples, 22050 Hz
  output). The ambient crowd is one looping sample whose volume follows `crowd_noise` (the original fades
  several channels in `update_ambient_audio`). The recorded menu loops (`*.IFF`, PAUSE.IFF on the pause screen)
  are not played: their bodies are not plain PCM and their coding is not identified (see FORMATS.md).
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
