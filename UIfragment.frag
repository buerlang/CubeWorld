#version 410 core
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D _Image;
uniform float _UVFactor;
uniform vec3 _Emission;
uniform float _Opaque = 1.0f;


void main()
{
	float uvAff = clamp(-11 * (TexCoord.y - 0.2f) * (TexCoord.y - 0.8f), 0, 1);
	vec4 tex = texture(_Image, TexCoord);
	color = vec4(tex.xyz, tex.w * _Opaque) + vec4(_Emission, 0.0f) + vec4(uvAff, uvAff, uvAff, 0.0f) * _UVFactor;
}