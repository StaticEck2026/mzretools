class_name Controls
## Builds the original control byte from Godot input actions and reproduces the sampling of the
## timer callback: controllers are read every 5 ticks of a 100 Hz timer (20 Hz) and the
## simulation consumes one sample per 3 steps. Control byte: bits 0-3 direction (0 up,
## 1 up-right, 2 right, 3 down-right, 4 down, 5 down-left, 6 left, 7 up-left, 8 none),
## 0x10 button A, 0x20 button B, 0x40 both (button C).

const ARROW_TO_DIR8 := [8, 0, 4, 8, 2, 1, 3, 2, 6, 7, 5, 6, 8, 0, 4, 8]

var samples := [8, 8]       # current sample per player
var prev_buttons := [0, 0]
var step_in_sample := 0

static func read(prefix: String) -> int:
	var mask := 0
	if Input.is_action_pressed(prefix + "_up"):
		mask |= 1
	if Input.is_action_pressed(prefix + "_down"):
		mask |= 2
	if Input.is_action_pressed(prefix + "_right"):
		mask |= 4
	if Input.is_action_pressed(prefix + "_left"):
		mask |= 8
	var c: int = ARROW_TO_DIR8[mask]
	var a := Input.is_action_pressed(prefix + "_a")
	var b := Input.is_action_pressed(prefix + "_b")
	if (a and b) or Input.is_action_pressed(prefix + "_c"):
		c |= 0x40
	elif a:
		c |= 0x10
	elif b:
		c |= 0x20
	return c

## Call once per simulation step; returns [control_p1, control_p2, pressed_p1, pressed_p2]
func step() -> Array:
	if step_in_sample == 0:
		samples[0] = read("p1")
		samples[1] = read("p2") if InputMap.has_action("p2_up") else 8
	step_in_sample = (step_in_sample + 1) % 3
	var out := []
	for p in 2:
		var buttons: int = samples[p] & 0x70
		var pressed: int = buttons & ~prev_buttons[p]
		prev_buttons[p] = buttons
		out.append(samples[p])
		out.append(pressed)
	return [out[0], out[2], out[1], out[3]]
