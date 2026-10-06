class_name ReplayFrame
## One unpacked replay frame (replay_seek_frames): what replay_draw_frame draws. The sprites carry
## the fields of Entity the view reads, so the view draws a replay like the live simulation.

class Sprite:
	var slot := 0
	var xi := 0
	var yi := 0
	var zi := 0
	var frame := -1
	var flags4 := 0
	var number := 0
	var line_slot := -1

	func on_ice() -> bool:
		return line_slot >= 0 or slot == Entity.Slot.REFEREE

var entities: Array = []
var user1_slot := -1
var user2_slot := -1
var puck_carrier := -1
var camera_x := 0
var camera_y := 0
var crowd := 0
var box_count := [0, 0]
var effect_frames: Array = []
var effect_ids: Array = []
