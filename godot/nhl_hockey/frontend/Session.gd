class_name Session
## The globals of the front end (apply_settings / save_settings, 0x327a1 / 0x3271b): the settings
## block of 0x75 bytes that GAME.SET stores (settings_exhibition 0xc5298 is the default) and the
## state the menus share. Field names follow the block:
##   +0x00 mode (dword_c53fb: 0 exhibition, 1 league, 2 play-offs)
##   +0x04 league directory (13 chars), +0x11 / +0x31 the two league names (32 chars each)
##   +0x51 home team, +0x55 visiting team (team indices 0..27)
##   +0x59 option_flags
##   +0x5d / +0x61 the team player 1 / player 2 controls (dword_c5403 / dword_c5407; -1 / -2 none)
##   +0x65 / +0x69 the controller of player 1 / player 2 (dword_c540b / dword_c540f: 1 mouse,
##         2 joystick 1, 4 joystick 2, 8 keyboard, 0x10 none)
##   +0x6d / +0x71 the side of player 1 / player 2 (dword_c5413 / dword_c5417: 0 home, 1 away)
##
## option_flags (the exhibition settings, game_settings_menu / settings_toggles):
##   0x01 penalties, 0x02 offsides, 0x04 line changes, 0x08 two line pass, 0x10 injuries,
##   0x20 fighting (unused by the match), 0x40 music, 0x80 sound effects,
##   0x100 speech, 0x200 regular season game (a 5 minute overtime, clear: play-off rules),
##   0x400 / 0x800 period length (period_seconds), 0x1000 .. bits of the league setup

const SETTINGS_SIZE := 0x75
const DEFAULT_SETTINGS := 0xc5298

static var mode := 0
static var league_dir := ""
static var league_name := ""
static var league_name2 := ""
static var home_team := 12
static var away_team := 21
static var option_flags := 0x7bff
static var p1_team := -1
static var p2_team := -2
static var p1_device := 0x10
static var p2_device := 0x10
static var p1_side := 0
static var p2_side := 1

static var input_devices := 8 | 1       # input_devices: 1 mouse, 2 joystick 1, 4 joystick 2, 8 keyboard
static var sound_enabled := true        # a sound card is installed (sound_enabled)
static var sound_device := 2            # dword_c541f: the card (1 PC speaker, 2 Sound Blaster, 4 AdLib,
                                        # 8 MT-32, 0x10 none, 0x20 UltraSound: the table at 0xd243a)
static var sound_cards := 0x3f          # dword_c541b: the cards that can be chosen (the port models them all)
static var cd_drive := "D"              # NHL.CFG line 2
static var installed: PackedStringArray = []   # NHL.CFG: the files on the hard disk
static var stats_league := false        # dword_c695a: the statistics of the league (else '93 - '94)
static var stats_playoffs := false      # dword_c6956: the play-offs (else the regular season)
static var stats_dir := ""              # unk_c65d4: the directory of the league's files
static var game_number := 0             # dword_dc234: the league game being played (>= 0x444 play-offs)
static var saved_game := -1             # the saved game to continue (play_game param, -1 a new game)

## apply_settings: the block (GAME.SET or settings_exhibition) into the globals
static func apply_block(b: PackedByteArray) -> void:
	if b.size() < SETTINGS_SIZE:
		return
	mode = b.decode_s32(0)
	league_dir = _str(b, 4, 13)
	league_name = _str(b, 0x11, 32)
	league_name2 = _str(b, 0x31, 32)
	home_team = b.decode_s32(0x51)
	away_team = b.decode_s32(0x55)
	option_flags = b.decode_u32(0x59)
	p1_team = b.decode_s32(0x5d)
	p2_team = b.decode_s32(0x61)
	p1_device = b.decode_s32(0x65)
	p2_device = b.decode_s32(0x69)
	p1_side = b.decode_s32(0x6d)
	p2_side = b.decode_s32(0x71)
	_check_devices()

## save_settings: the globals into a block
static func save_block() -> PackedByteArray:
	var b := PackedByteArray()
	b.resize(SETTINGS_SIZE)
	b.encode_s32(0, mode)
	_put_str(b, 4, 13, league_dir)
	_put_str(b, 0x11, 32, league_name)
	_put_str(b, 0x31, 32, league_name2)
	b.encode_s32(0x51, home_team)
	b.encode_s32(0x55, away_team)
	b.encode_u32(0x59, option_flags)
	b.encode_s32(0x5d, p1_team)
	b.encode_s32(0x61, p2_team)
	b.encode_s32(0x65, p1_device)
	b.encode_s32(0x69, p2_device)
	b.encode_s32(0x6d, p1_side)
	b.encode_s32(0x71, p2_side)
	return b

## the default block of the executable (settings_exhibition)
static func default_block() -> PackedByteArray:
	return Exe.bytes(DEFAULT_SETTINGS, SETTINGS_SIZE)

## apply_settings: a controller that is not there becomes none; a player without a controller
## gets the first free one (joystick 1, joystick 2, keyboard, mouse)
static func _check_devices() -> void:
	p1_device = _device_ok(p1_device)
	p2_device = _device_ok(p2_device)
	if p1_device == 0:
		p1_device = _free_device(p2_device)
	if p2_device == 0:
		p2_device = _free_device(p1_device)
	if (p1_device == 0x10) != (p2_device == 0x10):
		# one player without a controller: the other plays alone
		var second := p1_device != 0x10        # the player without a controller is player 2
		var other_side := p1_side if second else p2_side
		if second:
			p2_side = 1 if other_side == 0 else 0
			p2_team = (1 if other_side != 0 else 0) - 2
		else:
			p1_side = 1 if other_side == 0 else 0
			p1_team = (1 if other_side != 0 else 0) - 2

static func _device_ok(d: int) -> int:
	match d:
		1:
			return 1 if input_devices & 1 else 0
		2:
			return 2 if input_devices & 2 else 0
		4:
			return 4 if input_devices & 4 else 0
	return d

static func _free_device(other: int) -> int:
	if input_devices & 2 and other != 2:
		return 2
	if input_devices & 4 and other != 4:
		return 4
	if input_devices & 8 and other != 8:
		return 8
	if input_devices & 1 and other != 1:
		return 1
	return 0x10

## the users of a match: 0 none, 1 home, 2 away (Sim.user1_team / user2_team)
static func user_side(player: int) -> int:
	var team := p1_team if player == 0 else p2_team
	var dev := p1_device if player == 0 else p2_device
	if dev == 0x10 or team < 0:
		return 0
	if team == home_team:
		return 1
	if team == away_team:
		return 2
	return 0

## period_length (0x5b9d1): word_cbc4a[option_flags bits 10-11] = 300, 600, 1200, 1200 seconds; the
## overtime of a regular season game (0x200, period 4 on) is the first entry
static func period_seconds(period_num: int = 1) -> int:
	var table := [300, 600, 1200, 1200]
	if (option_flags & 0x200) != 0 and period_num > 3:
		return table[0]
	return table[(option_flags >> 10) & 3]

static func _str(b: PackedByteArray, at: int, n: int) -> String:
	var e := at
	while e < at + n and b[e] != 0:
		e += 1
	return b.slice(at, e).get_string_from_ascii()

static func _put_str(b: PackedByteArray, at: int, n: int, s: String) -> void:
	var a := s.to_ascii_buffer()
	for i in n:
		b[at + i] = a[i] if i < a.size() and i < n - 1 else 0
