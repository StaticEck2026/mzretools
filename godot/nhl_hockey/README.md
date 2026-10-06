# NHL Hockey – Godot 4 port (work in progress)

A Godot 4.3 project rebuilding EA Sports NHL Hockey (DOS, 1994) from the disassembly in
[`re/nhl_hockey`](../../re/nhl_hockey). The project contains no assets of the game; it reads the original
files from an installation directory (set the `NHL_GAME_DIR` environment variable or edit
`user://settings.cfg`, key `files/game_dir`). Without the files it runs with coloured placeholders.

```
godot --path godot/nhl_hockey            # run
godot --path godot/nhl_hockey --headless --import                       # first run: build the class cache
godot --path godot/nhl_hockey --headless --script tests/run_tests.gd    # self test (exit code 0 = pass)
```

Controls (player 1, home team): arrows skate, Alt = A (pass / switch player), Space = B (shoot / body
check), Ctrl = C (hook, poke check), Esc pauses. At the faceoff hold a direction and press A when the
puck drops.

## What is ported

The simulation is translated routine by routine from `re/nhl_hockey/decomp/*.c`; the source routine of
every function is given in its doc comment. The fixed point arithmetic of the original is kept so the
behaviour matches the DOS game (see "Porting conventions" below).

| Area | File | Source routines |
|---|---|---|
| Static tables | `data/tables.json`, `data/Tables.gd` | extracted by `tools/nhl/extract_tables.py`: animation sequences, direction vectors, frame and stick offsets, skating tables, faceoff spots and lineups, AI zones, shot targets, stoppage durations, entity init records |
| Asset loaders | `loaders/` | RefPack, SHPI shape banks (→ textures), VFN fonts, 8SVX/WAV samples, rink tiles (`unpack`, `loadshapes`, `setfont`, `loadsound`, `load_rink`) |
| Entities and teams | `sim/Entity.gd`, `sim/Team.gd` | the 17 x 0x80 byte entity records and the two team records (STRUCTURES.md) |
| Animation | `sim/Anim.gd` | `set_animation`, `advance_animation` |
| Step loop, physics | `sim/Sim.gd` | `sim_tick`, `sim_update_players` (update order, friction, speed clamp, gravity), `move_entity`, `collide_boards`, `collide_corner` (puck over the glass), `collide_net` (goals, posts), `sub_53ce5` (players against the net), `collide_neighbours`/`collide_pair` (body contact) |
| Controls | `sim/Sim.gd`, `sim/Controls.gd` | `control_player` (pass, shot, one timer, switch, hook, body check), `faceoff_control`, `apply_skating` with skating backwards, `skating_turn`, `skating_accelerate`, `stop_skating`, `brake`, `goalie_move`, `switch_to_nearest`, `find_switch_target` |
| Puck | `sim/PuckLogic.gd` | `puck_update`, `predict_puck_goal_line`, `update_carrier`, `puck_check_players`, `puck_player_interaction`, `goalie_save`, `puck_hits_player`, `attach_puck_to_stick`, `take_puck`, passes (`do_pass`, `pass_to_entity`, `pass_lead`, `pass_lane_ok`), shots (`start_shot`, `shot_control`, `do_shot`, `shot_setup`), checking (`body_check`, `hook_button`, `start_hook`, `start_poke_check`, `try_block_shot`, `resolve_body_check`, `knock_down`) |
| Rules | `sim/Rules.gd` | `sim_game_state`, `update_stoppage`, `process_infractions`, `start_stoppage` (faceoff spot selection), `queue_infraction`, `penalty_box_update` (serving penalties), `penalty_timers`, `goal_ends_penalty`, `game_clock_tick` (24 ticks per second), `score_goal`, `setup_faceoff` (period end), `check_offside`, `check_icing`, `update_offside_flags`, `two_line_pass_check`, `count_defenders_ahead`, the faceoff positioning of `ai_puck_faceoff2`, `faceoff_resolve`, `all_goto_positions` |
| AI | `sim/AI.gd` | the state dispatch and the handlers `defo defd wingd wingo centd cento score goalie goalieget puckc nearest shoot passrec fowait faceoff pnorm pshad pnothing pface pface2 rfaceoff rnorm rcallpen rpickup rgotofo rpointgoal rgetnew agotofo initper abreak` plus the helpers `ai_skate_towards`, `ai_chase_puck`, `ai_try_check`, `ai_near_carrier_check`, `ai_ref_positioning`, `ref_skate_to_point`, `ai_consider_shot`, `ai_offense_decision`, `ai_choose_pass_target`, `ai_desperation_shot`, the one timer logic (`sub_50b55`) |
| Camera | `sim/Sim.gd` | `update_camera` (follows the carrier, the referee during stoppages, the faceoff dot) |
| View | `view/Main.gd` | 320x200 viewport, 384x592 rink surface, y-sorted sprites with hotspots, mirrored frames, nets, scoreboard/clock/period HUD, queued sound effects |

The headless test (`tests/run_tests.gd`) checks the RefPack decoder, the tables, the animation stepping, a
complete game start (opening faceoff after about 4 seconds, CPU players moving, the clock running), the
skating controls, a shot into the empty net (goal, whistle, faceoff at centre ice), the end of a period
(teams switch ends), a hooking minor served in the box and a 6000 step game without script errors.

## Not ported yet, and known simplifications

- Penalties (hooking, charging, roughing, with the odds of the original) are served: the player skates to
  the box (`ai_penalty_box`, `ai_door_open`), his team plays short handed (faceoff lineups shrink), the
  penalty runs with the clock (`penalty_timers`) and ends with a power play goal (`goal_ends_penalty`) or
  by time (`ai_exit_penalty_box`). Not ported: the penalty shot (`ai_ref_penalty_shot`,
  `ai_all_penalty_shot_wait`), misconducts, injuries, the penalty announcements.
- Line changes and fatigue (`handle_line_change`, `apply_line_change`, `choose_line`, `ai_bench`,
  `ai_exit_bench`, `ai_bench_wait`, `cpu_line_change`) are not ported; the same six players stay on the
  ice with full energy, so `opt_line_changes` is off.
- `ai_choose_direction` (375 lines of net avoidance) is reduced to routing around the near post.
- The anthem, the three stars, the cup ceremony and the goal celebration cut scenes are not ported.
- Player ratings are placeholders (`Sim._default_skills`); `put_player_on_ice` reads them from the team
  database (`.db` files, see FORMATS.md) in the original.
- Team colours (`load_team_palettes`), jersey remap tables, the palette fades, the digit fonts of the
  HUD (`draw_clock`), menus, season mode, databases, save games, replay, speech.
- Which sample file holds which sound effect id is not recoverable from the executable; edit
  `Sounds.SFX_FILES` to match your installation.

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
- Decompiler artefacts to be aware of when reading `decomp/*.c`: `*(short *)(param_1 + 10)` with an
  `int` parameter is the puck height (+0xa), with an `int *` parameter it is the stuck timer (+0x28);
  JSON numbers load as floats in Godot, so `Tables.gd` converts every table to integers.
