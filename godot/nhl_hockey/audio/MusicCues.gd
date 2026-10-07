class_name MusicCues
extends RefCounted
## The organ songs of a match: load_music_banks (0x7dc8b) loads them when the match starts and
## play_speech (0x59a11) picks one for a cue of the simulation (Sim.music_queue):
##   0..5  the home team's songs (Tables.music_team_songs; none: one of the random songs)
##   6..8  three songs drawn from Tables.music_pool, none of the team's and no two alike
##   9     the "rock" stomp of the sound card (SBROCKU with digitised sound, MTROCKU for the MT-32,
##         ADROCKU for the others), with the clapping
##   10    the anthem of the home team's country (CANADA / USA)
##   11    ROCKDITI
## The simulation queues the cues; -1 stops the song (stop_crowd_loop at the faceoff).

const ROCKU := "SBROCKU"
const ROCKDITI := "ROCKDITI"

var team_songs: Array = ["", "", "", "", "", ""]
var random_songs: Array = ["", "", ""]
var anthem := ""
var rng := RandomNumberGenerator.new()
var exists: Callable              # name -> bool (the .KMS file is there)
var rocku := ROCKU

func _init(file_exists: Callable = Callable()) -> void:
	exists = file_exists
	rng.randomize()

## load_music_banks for the home team (database index) and the sound card (dword_c541f)
func setup(home: int, card: int = 2) -> void:
	rocku = "MTROCKU" if card == 8 else ("SBROCKU" if card == 2 or card == 0x20 else "ADROCKU")
	var row := home if home <= 0x19 else 0xd
	var ids: Array = Tables.music_team_songs[row] if row < Tables.music_team_songs.size() else [-1, -1, -1, -1, -1, -1]
	for k in 6:
		var i: int = ids[k]
		team_songs[k] = _song(i)
	var picked: Array = []
	for k in 3:
		var tries := 0
		while true:
			var cand: int = Tables.music_pool[rng.randi() % Tables.music_pool.size()]
			tries += 1
			if (not ids.has(cand) and not picked.has(cand)) or tries > 200:
				picked.append(cand)
				break
		random_songs[k] = _song(picked[k])
	var country: int = Tables.anthem_country[home] if home < Tables.anthem_country.size() else 0
	anthem = Tables.anthem_songs[clampi(country, 0, Tables.anthem_songs.size() - 1)]

func _song(i: int) -> String:
	if i < 0 or i >= Tables.music_songs.size():
		return ""
	var n: String = Tables.music_songs[i]
	if exists.is_valid() and not exists.call(n):
		return ""            # CGY2 is listed but not on the disks
	return n

## play_speech: the song of a cue ("" none)
func song_for(id: int) -> String:
	if id < 6:
		if id >= 0 and team_songs[id] != "":
			return team_songs[id]
		id = rng.randi() % 3 + 6
	if id < 9:
		return random_songs[id - 6]
	match id:
		9: return rocku
		10: return anthem
		11: return ROCKDITI
	return ""
