# NHL Hockey – data structures and simulation internals

Reverse engineered from `HOCKEY.EXE` (see README.md). Addresses are linear addresses of the LE image; names in
`code` are the ones used in `hockey.map`, the listing and the decompiled C. All positions are world
coordinates in **rink pixels**: x runs across the rink (-192..192, 0 at centre ice), y runs along the rink
(up/towards the top of the screen is positive, the goal lines are at y = ±240), z is height above the ice.
A world point maps to the 384x592 rink surface as `screen = (x + 192, 320 - y)` (`draw_sprite_world`).
Most values are 16.16 fixed point stored in 32-bit ints; "hi" means the integer part at offset +2.

## Entities (`entities`, 0xdf81c, 17 records of 0x80 bytes)

| Slot | What |
|---|---|
| 0-5 | home team players (one of them is the goalie, see `line_slot`) |
| 6-11 | away team players |
| 12, 13 | the two goal nets (collision bodies, `entities[12]`/`[13]`) |
| 14 | the **puck** (`puck`, 0xdff1c); the puck has its own AI states (`pnorm`, `pface`, ...) |
| 15 | puck shadow / spare |
| 16 | referee (`referee`, 0xe001c) |

Entity record (`struct Entity`, size 0x80):

| Offset | Type | Name | Meaning |
|---|---|---|---|
| 0x00 | int 16.16 | `x` | position across the rink |
| 0x04 | int 16.16 | `y` | position along the rink |
| 0x08 | int 16.16 | `z` | height |
| 0x0c | short | `vx` | velocity, added as `x += 16 * vx` per step |
| 0x0e | short | `vy` | |
| 0x10 | short | `vz` | gravity: `vz -= 6*16` per step while airborne, bounce `vz = -vz/2` |
| 0x12 | short | `frame` | current sprite frame id (index into `sprite_frames`, 0..0x46d) |
| 0x16 | short | `speed_prev` | |
| 0x18 | short | `speed` | skating effort, decays by 2 per step |
| 0x1a | short | `line_slot` | 0 = goalie, 1..5 = skater position on the ice, <0 = on the bench |
| 0x1c | short | `state_sp` | index of the current entry of the state stack |
| 0x1e | byte[8] | `state_stack` | AI state ids (see below), `state_stack[state_sp]` is the active state |
| 0x26 | short | `timer_a` | general purpose timers used by the state handlers |
| 0x27 | char | `react_timer` | reloaded from `reaction` when it expires (AI thinks every N steps) |
| 0x28 | byte | `want_dir` | wanted skating direction (0-7, 8 = none) |
| 0x2a | short | `target_x` | AI target position (also used as a countdown by some states) |
| 0x2c | short | `target_y` | AI target position (timer_b at 0x2e == -100 marks "arrived at the faceoff spot") |
| 0x2e | short | `timer_b` | |
| 0x30 | short | `push_x` | board normal `a` after a bounce this step (no acceleration into the boards) |
| 0x32 | short | `push_y` | board normal `b` |
| 0x34 | short | `heading` | movement direction index (0-7, see `dir8_vectors`) |
| 0x36 | short | `facing` | sprite facing direction 0-7 (0 = up, clockwise) |
| 0x38 | short | `anim` | animation sequence id (index into `anim_sequences`) |
| 0x3a | short | `anim_pos` | position within the sequence |
| 0x3c | short | `anim_hold` | frames left before advancing |
| 0x3e | short | `timer_c` | no-pickup time after releasing the puck |
| 0x40 | short | `timer_d` | hooked / slowed timer |
| 0x42 | byte | `next_line_slot` | line change: position to take (-1 none) |
| 0x43 | byte | `next_roster` | line change: replacement roster index |
| 0x44 | byte | `flags` | 0x01 committed (pass receiver / bench), 0x02 state just entered (handlers run their init part and clear it), 0x04 arrived at the bench door / puck out of play, 0x08 user controlled, 0x10 skating backwards, 0x20 busy (locked in an action animation), 0x40 away team (player 2 side), 0x80 shoots at the net at +y (the home team in the 1st period); every AI table is stored in the +y frame and negated when the bit is clear |
| 0x45 | byte | `flags2` | 0x01 knocked down, 0x02 turning / action started, 0x04 not selectable (penalty box/injured), 0x08 changing lines, 0x10 penalty recorded, 0x20 no collisions, 0x40 hooked (speed limit >> 3), 0x80 offside position |
| 0x46 | byte | `pass_target` | chosen pass receiver slot (AI) |
| 0x47 | byte | `roster_idx` | index into the team roster (0..24 skaters, 25,26 goalies) |
| 0x48 | byte | `flags3` | goalie: 0x02/0x04 may leave the crease |
| 0x4a | short | `timer_e` | goalie save cooldown / poke check direction |
| 0x4c | short | `timer_f` | shoot state cooldown |
| 0x4e | short | `puck_dist` | distance to the puck (`approx_distance`) |
| 0x50 | short | `puck_dist_sq` | (dx/4)² + (dy/4)² |
| 0x52 | byte | `puck_dir` | direction 0-7 towards the puck |
| 0x53 | byte | `pass_ok` | result of the pass lane check (`pass_lane_ok`) |
| 0x55 | byte | `flags4` | 0x08 left handed / sprite mirrored |
| 0x56 | byte | `weight` | used by `skating_accelerate` |
| 0x57 | byte | `speed_skill` | |
| 0x59 | byte | `reaction` | reload value for `react_timer` (CPU players) |
| 0x5a | byte | `reaction2` | |
| 0x5b | byte | `shot_skill` | shot power attribute |
| 0x5d | byte | `pass_skill` | pass power attribute |
| 0x62 | byte | `check_skill` | |
| 0x66 | short | `half_w` | collision half width |
| 0x68 | short | `half_h` | collision half height |
| 0x6a | short | `slot` | own index in `entities` |
| 0x6c | Team* | `team` | |
| 0x70 | Team* | `opponents` | |
| 0x74 | int | `prev_x` | position at the start of the step |
| 0x78 | int | `prev_y` | |
| 0x7c | int | `prev_z` | |

For the puck (`entities[14]`) the byte at +0x42 is the **puck carrier** (`puck_carrier`, 0xdff5e): slot of the
player carrying the puck, -1 (0xff) when loose. The pointer block at 0xc907c (`p_puck_x`, `p_puck_vx`,
`p_puck_y`, `p_puck_vy`, `p_puck_z`, `p_puck_vz`, `p_puck_carrier`) points at the integer parts of the puck
fields and is what most of the code reads.

## Teams (`team_home` 0xdf614, `team_away` 0xdf714, 0x100 bytes each)

| Offset | Name | Meaning |
|---|---|---|
| 0x04 | `lead_changes` | incremented on each lead change (`update_lead_change`) |
| 0x10 | `goals` | score |
| 0x2a | `current_line` | |
| 0x30/0x32/0x34 | `carrier_hist` | last three puck carriers of the team (roster indices) |
| 0x36 | `skaters_on_ice` | recomputed when penalties are served (`penalty_box_update`) |
| 0x38/0x39 | `line_request` | pending line change request (low nibble = line) |
| 0x3e | `nearest_dist` | distance of the closest skater to the puck |
| 0x42 | `nearest_slot` | that skater's entity slot |
| 0x44 | `flags` | 0x01, 0x02 line change requested, 0x08, 0x10 offside pending |
| 0x46 | short[27] | `energy[roster]` | fatigue 0..0x1000, -0xcc per body check, +8 per step on the bench |
| 0x7e | short[27] | `entity_of[roster]` | entity slot of each roster player, -2 = on the bench |
| 0xea | ptr | `goalie_stats` | 6 bytes per goalie |
| 0xf6 | Entity* | `players` | first of the 6 entities of this team |
| 0xfa | short | `goalie_slot` | entity slot of the goalie |

## AI states (`ai_state_handlers`, 0xc9161, 47 entries; names `ai_state_names` at 0xcd8c4)

Each simulation step `sim_update_players` calls `ai_state_handlers[state_stack[state_sp]](entity)`. Handlers
run their initialisation when `flags & 2` is set (`set_state` sets it) and clear the bit.

| Id | Name | Handler | Id | Name | Handler |
|---|---|---|---|---|---|
| 0 | null | `ai_null` | 24 | pnorm | `ai_puck_normal` (puck physics, `puck_update`) |
| 1 | defo | `ai_defense_offense` | 25 | pshad | `ai_puck_shadow` |
| 2 | defd | `ai_defense_defense` | 26 | pnothing | `ai_puck_idle` |
| 3 | wingd | `ai_wing_defense` | 27 | pface | `ai_puck_faceoff` |
| 4 | wingo | `ai_wing_offense` | 28 | pface2 | `ai_puck_faceoff2` |
| 5 | centd | `ai_center_defense` | 29 | gamemiscon | `ai_game_misconduct` |
| 6 | cento | `ai_center_offense` | 30 | rfaceoff | `ai_ref_faceoff` |
| 7 | score | `ai_celebrate_goal` | 31 | rnorm | `ai_ref_normal` |
| 8 | stan | `ai_stanley_cup` | 32 | rcallpen | `ai_ref_call_penalty` |
| 9 | exben | `ai_exit_bench` | 33 | rpickup | `ai_ref_pickup_puck` |
| 10 | expen | `ai_exit_penalty_box` | 34 | rgotofo | `ai_ref_goto_faceoff` |
| 11 | bench | `ai_bench` | 35 | rpointgoal | `ai_ref_point_goal` |
| 12 | pen | `ai_penalty_box` | 36 | rgetnew | `ai_ref_get_new_puck` |
| 13 | dopen | `ai_door_open` | 37 | anth | `ai_anthem` |
| 14 | goalie | `ai_goalie` | 38 | ranth | `ai_ref_anthem` |
| 15 | goalieget | `ai_goalie_get_puck` | 39 | agotofo | `ai_all_goto_faceoff` |
| 16 | puckc | `ai_puck_carrier` | 40 | benwait | `ai_bench_wait` |
| 17 | nearest | `ai_nearest_to_puck` | 41 | initper | `ai_init_period` |
| 18 | shoot | `ai_shoot` | 42 | getcup | `ai_get_cup` |
| 19 | passrec | `ai_pass_receiver` | 43 | pgivecup | `ai_puck_give_cup` |
| 20 | 3star | `ai_three_stars` | 44 | rpenshot | `ai_ref_penalty_shot` |
| 21 | r3star | `ai_ref_three_stars` | 45 | apswait | `ai_all_penalty_shot_wait` |
| 22 | fowait | `ai_faceoff_wait` | 46 | abreak | `ai_breakaway` |
| 23 | faceoff | `ai_faceoff` | | | |

`position_default_state` (0xccc9e) maps `line_slot` to the default state: goalie -> goalie(14), 1,2 -> defd/defo,
3 -> wingd, 4 -> cento... (`set_default_state`).

## Controls

The 100 Hz timer callback (`timer_callback`) samples the controllers every 5 ticks into a ring buffer of 50
entries x 3 bytes (`control_ring`, 0xd8b80: player 1, player 2, hotkey). `run_sim_steps` consumes one entry per
3 simulation steps (`control_entry`, `control_steps_left`).

Control byte: bits 0-3 direction (0 up, 1 up-right, 2 right, 3 down-right, 4 down, 5 down-left, 6 left,
7 up-left, 8 none, 9 stop), 0x10 button A, 0x20 button B, 0x40 both buttons (button C).
`controller_type[2]` (0xc4d1c): 1 mouse, 2 joystick 1, 4 joystick 2, 8 keyboard. Keyboard: arrows/keypad for
direction (`arrow_to_dir8` 0xc4d1f), Alt or Ins = A, Space or Enter = B, Alt+Space / Ins+Enter = C.

`control_player` dispatches the newly pressed buttons:

| | puck carrier | not carrying |
|---|---|---|
| A (0x10) | `pass_request` → `pass_button` → `do_pass` when A is released, in the pushed direction; receiver chosen among team mates within ±1 direction (`pass_lead`), a CPU pass uses `pass_to_entity` | `switch_to_nearest` (control the team mate closest to the puck); with a pass on the way: one timer set up |
| B (0x20) | `start_shot` → `shot_control` every step of the wind up (power grows while held, A/C fake) → `do_shot`: power from `shot_skill` and energy, aim from `shot_targets[pending_dir]`, forehand/backhand (`shot_is_backhand`) | `body_check` (velocity burst, costs 0xcc energy, animation 0x621) |
| C (0x40) | `request_line_change` | `hook_button`: `try_block_shot`, `start_hook` (0x639/0x873) or `start_poke_check` |

Skating itself is `apply_skating(entity, dir)` (`skating_accelerate` adds `dir8_vectors[heading] * speed` scaled
by `speed_skill`/`weight`, `stop_skating` brakes, `goalie_move` for goalies).

## Game state globals (selection)

| Address | Name | Meaning |
|---|---|---|
| 0xc9098 | `camera` | current camera position (x low word, y high word), `camera_target` (0xc90ac/0xc90ae) |
| 0xc90bb | `game_flags` | 0x01 play stopped (whistle), 0x02 teams switched ends, 0x04 stoppage countdown running (`stoppage_timer`), 0x08 delayed penalty call pending, 0x10 practice / no statistics, 0x40 overtime, 0x80 game over (intermission camera) |
| 0xc90bc | `action_flags` | 0x04 pass pending, 0x08 shot pending, 0x10 replay buffer wrapped, 0x40 camera hold, 0x80 controls mirrored |
| 0xc90be | `stop_flags` | 0x01 faceoff set up (waiting for the drop), 0x04 whistle / announcement done, 0x10 a shot is in flight (`goalie_save` bookkeeping), 0x20 a team leads (0x40 = away), 0x80 goalie pulled |
| 0xc90b2 | `faceoff_spot` | dot of the next faceoff (x low word, y high word), chosen by `start_stoppage` |
| 0xc909c | `coll_half_w`/`coll_half_h` | half size of the entity being moved (`collide_boards`, `collide_net`) |
| 0xc90d4 | `ref_phase` | 0 referee called, 1 collecting the puck, -1 ready for the faceoff; `ref_infraction` 0xc90d6 |
| 0xcc0f4 | `one_timer_pending` | `breakaway_flag` 0xcc0f8, `defenders_ahead` 0xcc124, `controls_blocked` 0xccc9c |
| 0xcc128 | `penalty_shot_active` | `penalty_shot_phase` 0xcc118, `penalty_shot_slot` 0xcc0fc, `penalty_shot_team` 0xcc104 |
| 0xe9abe | `icing_state` | byte 2: 1 icing called, 2 direction, 4 shot from the own half; byte 3 shooter slot |
| 0xe9ac2 | `last_touch_slot` | last player to touch the puck; `last_touch_y` 0xe9ac4, `last_touch_x` 0xe9ac6 (faceoff spot after a frozen puck) |
| 0xdf812 | `goal_prediction` | 2 x (x, steps) where the puck will cross each goal line (`predict_puck_goal_line`, every 5 steps) |
| 0xc90a4 | `pending_dir` | direction of the pending pass/shot |
| 0xc90a6 | `shot_power` (lo) / `pass_target` (hi) | |
| 0xc90c2 | `user1_slot` | entity controlled by player 1 (-1 none), `user2_slot` 0xc90c4 |
| 0xc90c6 | `user1_team` | 1 home, 2 away, 0 CPU; `user2_team` 0xc90c8 (low word) |
| 0xc90ca | `home_team_id` | team index 0..27 (`team_abbrev[]`), `away_team_id` 0xc90cc |
| 0xc90da | `period_idx` | 0-based period (3 = overtime) |
| 0xc90dc | `clock_seconds` | time left in the period, `clock_sub` (0xc90de) counts 24 steps per second |
| 0xd8c84 | `period_num` | 1-based period shown on the scoreboard |
| 0xcc0dc | `crowd_noise` (hi word) | 0..2000, decays, boosted by goals/hits; lo word = pending replay sound event |
| 0xe9aa6 | `excitement` | |
| 0xcbc46 | `period_over` | `game_over` 0xcbc48 |
| 0xcbc3e | `show_names` | toggled with the hotkey, draws numbers of all players |
| 0xc4d0c | `input_enabled` | timer callback samples controllers while set |
| 0xc4e18 | `control_entry` | pointer to the current ring buffer entry |
| 0xe9a7a/0xe9a58/0xe9adb.. | `draw_order_*` | y-sorted list of entities for drawing and neighbour collision tests |
| 0xc9078 | `replay_buffer` | 0x9600 bytes of packed frames (`replay_record_frame`) |
| 0xd9a38 | `sprite_frames` | 1134 pointers to shapes, indexed by `frame` |
| 0xc921d | `anim_sequences` | animation table used by `advance_animation` |
| 0xc90e0 | `dir8_vectors` | (dx, dy) * 200 for the 8 directions |
| 0xcc148 | `frame_offsets` | per-frame x/y displacement used by movement animations |

## Animation sequences (`anim_sequences`, 0xc921d; `advance_animation`, `set_animation`)

An animation id (`Entity.anim`, e.g. 0x289 skate, 0x361 stop, 0x3f9 forehand shot, 0x491 backhand shot,
0x621 body check, 0x639/0x873 hook, 0x7a1/0x7dd/0xd05 faceoff, 0xa5b/0xb4b referee skate/glide, 0x1f1 goalie)
is a **word offset** into the table: `entry = (u16*)(anim_sequences + anim * 2)`.

```
entry[0..7]   per facing direction (0-7) word offset of the frame list, relative to entry + 8 words;
              bit 15 of entry[0] = the animation loops, otherwise anim is reset to 0 (idle) at the end
entry[8 + off + 2k]      frame id (index into sprite_frames)
entry[8 + off + 2k + 1]  duration in simulation steps; a negative duration marks the last frame
```

`advance_animation` holds each frame for its duration (`anim_hold`), steps `anim_pos` by 2, and when the duration
word of the previous frame is negative it rewinds; animations starting with the "busy" flag clear `flags & 0x20`
when they finish. Skating stride sounds (sfx 0xb3) are played on specific frame ids. Mirrored sprites
(`flags4 & 8`, left handed players) use `8 - dir` for the direction lookup. `frame_offsets` (0xcc148, pairs of
signed bytes indexed by frame id - see `frame_offsets_lookup`) give the per frame displacement that movement
animations apply to the position.

## Replay buffer (`replay_record_frame`, `replay_seek_frames`, `replay_draw_frame`)

`replay_buffer` (0xc9078, 0x9600 bytes) is a ring of frames recorded every second simulation step while
`game_flags & 0x10` is clear. One frame holds 17 packed u32 entity records (x & 0x3ff, y & 0x3ff << 10, frame &
0x7ff << 20, mirror bit), 12 bytes of per player data (+0x5e), 6 bytes of line slot/line info, the puck height,
the crowd/sound event, the controlled slots, the puck carrier, the camera position (u8 + u16 + u16) and the 20
effect slots (10 packed bytes + 20 frame bytes).

## Puck (`entities[14]`)

The puck uses the same record as the players. `p_puck_x` .. `p_puck_vz` point at its integer parts; `puck_carrier`
(+0x42 of the puck, 0xdff5e) is the slot of the carrier or -1. While carried, `update_carrier` moves the puck to
the stick position (`frame_offsets` of the carrier's frame). `puck_update` (state `pnorm`) applies friction,
bounces off the boards (`bounce_off_boards`, sfx 0xb1) and the nets (`collide_net` → `score_goal` when it crosses
the goal line between the posts), lets players pick it up (`puck_check_players` → `puck_player_interaction`), and
checks icing (`check_icing`) and offside (`check_offside`, blue lines at y = ±74).

Physics constants found so far: friction `v -= v >> 6` per step on the ice (`>> 9` with flag 0x01 set, which
the puck has: it glides much further than a player), max skater speed 16000 (16.16 px/step * 16), gravity 96 per
step, boards at x = ±160, y = ±264 minus the entity half size with 64 px rounded corners (`collide_boards`), nets
at y = ±236 (half size 20 x 6, `entity_init`), goal line y = ±232 (0xe8), blue lines y = ±78 (0x4e), shot aiming
table `shot_targets` (0xccc60, (x, z) pairs per `pending_dir`). A puck higher than 0x1d (or 0x12 away from the end
boards) at the boards is out of play (`collide_corner`); higher than 0xd it flies over the net (`collide_net`);
higher than 0x10 nobody can play it (`puck_check_players`). The decompiler shows the puck height as
`*(short *)(param_1 + 10)` when `param_1` is an `int` (offset 0xa) - with an `int *` the same expression is the
stuck timer at 0x28.

## Stoppages and infractions (`queue_infraction`, `process_infractions`, `start_stoppage`, `penalty_box_update`)

`infraction_queue` (0xe9a16, 32 x (type byte, slot byte)) collects rule events. Types: 1 period start, 2 period
end, 3 puck frozen / held / out of play, 4 goalie holding the puck, 5 penalty shot end, 6 icing, 7 goal, 8 offside,
9..21 two minute minors (9 hooking, 13 charging, 14 high sticking, 19 elbowing, ...), 22 misconduct, 23..25
majors (`infraction_is_penalty` 0xc9123: 0, 2, 5, -1), 27 goal disallowed, 29 two line pass, 30 player pinned at
the net. Per type `stoppage_duration` (0xc9104, << 5 steps) and `announce_delay` (0xc9142, * 0x20 steps) time
the stoppage, `infraction_priority` (0xcd39c) picks the announcement.

Flow: the first non penalty event stops the play (`start_stoppage`: `game_flags |= 1 | 4`, whistle sfx 0xa4,
faceoff spot from the event - centre after a goal, the last touch position after a frozen puck or a two line pass,
otherwise the puck position snapped to the nearest dot: end zone dots (±96, ±184), neutral zone dots (±100, ±61),
the blue line for offsides, the offending team's end for icing). A penalty against the team without the puck is
delayed (`game_flags |= 8`) until it touches the puck. The referee announces the call (`ref_announce`: state
`rpointgoal` after a goal, `rcallpen` otherwise, with `ref_signal_dir`/`ref_signal_anim` per type), sends
everybody to the faceoff (`all_goto_positions` → state `agotofo`, `faceoff_spots`/`faceoff_lineup` give the
position per line slot relative to the dot), collects the puck (`rpickup` → `rgotofo`, the puck is carried at
height -100) and when `ref_phase` is -1 `penalty_box_update` serves the penalties and puts the puck into state
`pface` → `pface2`: everybody is snapped into place, a countdown of 0xb4 + random(0x78) steps runs
(`faceoff_timer`, the referee's drop animation 0xc43 at 0x11) and `faceoff_resolve` gives the puck to the centre
with the better readiness (`faceoff_ready_*` 1..6 from `ai_faceoff`, `faceoff_bonus`) and skill; the users can
steer the won draw with the direction held at the drop (`faceoff_dir_*`).

## AI tables used by the handlers

| Address | Name | Used by |
|---|---|---|
| 0xccca1 | `position_default_state` | `set_default_state`: state per line slot (goalie 14, D 2, LW/RW 3, C 5) |
| 0xcbe8c / 0xcbea8 | `faceoff_spots` / `faceoff_lineup` | faceoff positions (7 spots, lineup rows for 6/5/4 skaters) |
| 0xcca6e | `carrier_targets` | `ai_puck_carrier`: 10 skating targets, index = lane + 6 (or line slot - 1 with the goalie pulled) |
| 0xcca18 / 0xcca38 | `wing_zones` / `center_zones` | `ai_wing_offense` / `ai_center_offense`: [x, dx, y, dy] per zone phase |
| 0xcc7a4 | `stick_offsets` | stick blade position per frame (puck pick up reach) |
| 0xccbba | `onetimer_offsets` | one timer blade position per facing |
| 0xccc30 | `poke_vectors` | `start_poke_check` velocities |
| 0xccb18 | `breakaway_waypoints` | `ai_breakaway` lanes (x, y, trigger y) |
| 0xcca5a | `goalie_save_anims` | `ai_goalie` save animation per direction class |
| 0xcbd5a | `entity_init` | initial entity records (positions on the bench, nets at ±236, puck 5x5, referee) |

## Rendering (`game_loop`, `draw_rink`, `draw_sprites`, `draw_clock`)

The screen is 320x200 (`set_video_mode(0x140, 200)`): the ice view on top (320x168, a window onto the 384x592
rink surface, scrolled by the camera clamped to 0..0x40 / 0..0x1a8) and the scoreboard `hud_window` (320x32 at
y 0xa8). `draw_sprite_world(frame, x, y, mirror, team)` draws `sprite_frames[frame]` at (x + 0xc0, 0x140 - y)
of the surface through the remap table of the team (`blit_sprite` -> `setremaptable(remap_home / remap_away)`,
`blit_rle_frame*` for the run length coded frames). `draw_sprites` first draws the markers under the controlled
players and the puck carrier (`marker_frames`: 0x185, 0x186, 0x187; `arrow_frames` when the player is off
screen), the nets and effects (`draw_nets_and_effects`: `effect_frames` records at 0xdee94, 12 bytes each, 18
ice marks and the two nets), the puck when it lies on the ice, then the entities in `draw_order_list` order
(sorted by y) with `draw_player_number` (NUMSHP digits 13 pixels below the skates, the position letter for the
controlled players and the carrier), the puck again when it is in the air, the penalty box overlay and the
message box. `load_rink` composes the surface once per home team (`rink_logo_table`). Sound effects go through
`play_sfx` -> `snd_play_sfx` -> `snd_play_patch` (see FORMATS.md).
