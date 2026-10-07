class_name SettingsScreens
extends RefCounted
## The settings screens of the front end (exhibition / league / play-off settings, the controllers,
## the sound)

var fe: FrontEnd
var scr: Screen8
var ui: Ui

func _init(f: FrontEnd) -> void:
	fe = f
	scr = f.scr
	ui = f.ui
