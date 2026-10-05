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

## What is ported

| Area | Status | Source routines |
|---|---|---|
| Static tables (`data/tables.json`, `data/Tables.gd`) | extracted from the EXE: animation sequences, direction vectors, frame offsets, skating tables, AI state names, team names | `tools/nhl/extract_tables.py` |
| Asset loaders (`loaders/`) | RefPack, SHPI shape banks (→ textures), VFN fonts, 8SVX/WAV samples, rink tiles | `unpack`, `loadshapes`, `setfont`, `loadsound`, `load_rink` |
| Entities (`sim/Entity.gd`) | the 17 x 0x80 byte records with the reverse engineered fields | STRUCTURES.md |
| Animation (`sim/Anim.gd`) | sequence stepping, looping, busy flag | `set_animation`, `advance_animation` |
| Physics (`sim/Sim.gd`) | friction, speed clamp, gravity/bounce, position update, boards with rounded corners | `sim_update_players`, `collide_boards`, `collide_corner`, `bounce_off_boards` |
| Controls (`sim/Controls.gd`, `Sim.control_player`) | control byte, 20 Hz sampling, skating/turning/stopping, switch player, pass, shot, body check (simplified) | `control_player`, `apply_skating`, `skating_turn`, `skating_accelerate`, `stop_skating`, `brake`, `switch_to_nearest`, `do_pass`, `start_shot`, `body_check` |
| Camera | follows the puck/carrier with the view clamps of the original | `update_camera`, `game_loop` |
| View (`view/Main.gd`) | 320x200 viewport, 384x592 rink surface, y-sorted sprites with hotspots, mirrored frames | `draw_sprites`, `draw_sprite_world`, `blit_sprite` |

## Not ported yet

- The 47 AI state handlers (`ai_*` in `hockey.map`): CPU players only glide. This is the bulk of the
  remaining work (about 60 KB of code in `decomp/decomp_04a343.c` .. `decomp_0526ed.c`).
- Puck/player interaction details (`puck_player_interaction`, deflections, stick handling), goal and
  net collision (`collide_net`, `score_goal`), rules (`check_offside`, `check_icing`, penalties,
  `setup_faceoff`), the game clock, line changes, HUD (`draw_clock`), sound (`play_sfx` ids are queued in
  `Sim.sfx_queue` but not played), speech, menus, season mode, databases, save games, replay.
- Team colours (`load_team_palettes`), jersey remap tables and the palette fades.

## Porting conventions

- Keep the fixed point scale of the original (positions 16.16, velocities 16 bit, `pos += 16 * v` per
  step, 60 steps per second) so that routines can be translated literally from `decomp/*.c`.
- World coordinates: x across the rink (±160 inside the boards), y along the rink (goal lines at ±232,
  boards at ±264), screen = (x + 192, 320 - y) on the rink surface, height z lifts a sprite by 3z/2.
- The `step()` order mirrors `sim_update_players`: animation, timers, physics, control/AI, collisions.
