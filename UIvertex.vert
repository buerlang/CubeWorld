#version 410 core
layout (location = 0) in vec2 localPos;
layout (location = 1) in vec2 texCoord;

uniform vec2 _Position;
uniform vec2 _Sink;
uniform vec2 _Scale;
uniform vec2 _ScrSize;


out vec2 TexCoord;

void main()
{
	float tx = _Position.x + _Sink.x;
	float ty = _Position.y + _Sink.y;
	mat4 model = mat4(	_Scale.x, 0.0f, 0.0f, 0.0f,
						0.0f, _Scale.y, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						tx, ty, 0.0f, 1.0f);

	vec4 p = model * vec4(localPos.x, localPos.y, 0, 1);

	gl_Position = vec4( (p.x / _ScrSize.x - 0.5f) * 2.0f,
						(p.y / _ScrSize.y - 0.5f) * 2.0f,
						0,
						1);
	TexCoord = texCoord;
}