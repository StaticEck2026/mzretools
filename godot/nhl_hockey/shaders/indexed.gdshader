shader_type canvas_item;
// An 8 bit indexed picture (R8 texture of colour indices) shown through a 256 x 1 palette texture,
// like the VGA DAC shows the frame buffer of the EA library. `transparent` (>= 0) is a colour
// index left out (the 0xff of drawshape_remap / copy_skip_ff).

uniform sampler2D palette : filter_nearest;
uniform int transparent = -1;

void fragment() {
	float i = texture(TEXTURE, UV).r * 255.0;
	if (transparent >= 0 && abs(i - float(transparent)) < 0.5) {
		discard;
	}
	COLOR = vec4(texture(palette, vec2((floor(i + 0.5) + 0.5) / 256.0, 0.5)).rgb, 1.0);
}
