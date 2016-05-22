#version 410
in vec2 v2f_texCoord;

out vec4 out_color;

uniform vec3 _Color;

void main()
{
	out_color = vec4(_Color, (1 - v2f_texCoord.x) * (1 - v2f_texCoord.x));
}