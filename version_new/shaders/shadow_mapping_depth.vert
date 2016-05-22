#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texCoord;

uniform mat4 _LightSpaceProjection;
uniform mat4 _LightSpaceView;
uniform mat4 _Model;

void main()
{
    gl_Position = _LightSpaceProjection * _LightSpaceView * _Model * vec4(position, 1.0f);
}