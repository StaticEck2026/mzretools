class_name StatsScreens
extends RefCounted
## The statistics screens of the front end (standings, team and player tables, rosters, player cards)

var fe: FrontEnd
var scr: Screen8
var ui: Ui

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui
