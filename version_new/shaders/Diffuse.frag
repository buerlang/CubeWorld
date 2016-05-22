#version 410

in vec2 v2f_tex;

out vec4 out_color;

uniform sampler2D _Image;

void main()
{
	out_color = texture(_Image, v2f_tex);
}