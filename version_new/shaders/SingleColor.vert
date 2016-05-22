#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 _Model;
uniform mat4 _View;
uniform mat4 _Projection;


void main()
{
	gl_Position = _Projection * _View * _Model * vec4(position, 1.0);
}