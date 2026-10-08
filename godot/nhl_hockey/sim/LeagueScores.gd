class_name LeagueScores
## The scores around the league the intermissions and the end of a game show (league_scores_init
## 0x2f2b1, league_scores_advance 0x2f3d7; simulate_pending_games 0x18f8d is in Highlight.gd): six
## other games of the night, their teams and scores (frontend/BoxScore.gd draws them).

const TEAM_RATING := 0xc8922       # unk_c8922: a strength per team (the order of the games' finish)

static var games: Array = []       # calendar_games (unk_dd774 / dd775), unk_dd730, unk_dd788 / dd789: 6 x [a, b, status, score a, score b]
static var shown: Array = [0, 0, 0, 0, 0, 0]   # league_status_shown: the status last shown
static var done_mask := 0          # league_done_mask: the games already simulated to the end

## league_scores_init: six other games of the night, between teams not stronger than the home team
## (the C library's rand(), League.rand)
static func init(home: int, away: int) -> void:
	games.clear()
	done_mask = 0
	var limit := Exe.u8(TEAM_RATING + home)
	var used := [home, away]
	for g in 6:
		var a := 0
		while true:
			a = League.rand() % 0x1a
			if a == home or a == away or Exe.u8(TEAM_RATING + a) > limit or a in used:
				continue
			break
		used.append(a)
		var b := 0
		while true:
			b = League.rand() % 0x1a
			if b == a or b == home or b == away or b in used:
				continue
			break
		used.append(b)
		games.append([a, b, 0, 0, 0])
	for g in 6:
		shown[g] = 0

## league_scores_advance: each game moves on as far as the game on the ice (shifted by the
## difference of the teams' strengths): 0..2 goals for each side per period, a tie after the
## third goes to overtime (status 4) where 71 of 100 games end in a tie, else one side wins (5);
## 6 the game is over after regulation
static func advance(period: int, home: int) -> void:
	for g in games.size():
		var game: Array = games[g]
		var target := Exe.u8(TEAM_RATING + home) - Exe.u8(TEAM_RATING + game[0]) + period
		var st: int = game[2]
		while st <= target:
			if st == 4:
				if game[3] == game[4]:
					game[2] = 4
					if League.rand() % 100 < 0x47:
						if League.rand() % 100 > 0x46:
							game[2] = 5
							game[4] += 1
					else:
						game[2] = 5
						game[3] += 1
				else:
					game[2] = 6
			elif st == 5 and game[2] == 4:
				game[2] = 5
			elif game[2] < 3 and st != game[2]:
				game[2] = st
				game[3] += League.rand() % 3
				game[4] += League.rand() % 3
			st += 1
