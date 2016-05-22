#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 _Projection;
uniform mat4 _View;
uniform mat4 _Model;
uniform mat4 _LightSpaceMatrix;

void main()
{
    gl_Position = _Projection * _View * _Model * vec4(position, 1.0f);
    vs_out.FragPos = vec3(_Model * vec4(position, 1.0));
    vs_out.Normal = transpose(inverse(mat3(_Model))) * normal; //规矩阵，去掉了平移属性
    vs_out.TexCoords = texCoords;
    vs_out.FragPosLightSpace = _LightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
}