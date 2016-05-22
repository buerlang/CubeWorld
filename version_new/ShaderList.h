#ifndef SHADER_LIST_H
#define SHADER_LIST_H

class Shader;

class ShaderList
{
private:
	ShaderList();
public:
	static Shader* UI;
	static Shader* SingleColor;
	static Shader* Gradient;
	static Shader* Diffuse;
	static Shader* DepthMap;
	static Shader* Diffuse_Lighted_Shadow;
	static void Initialize();
};



#endif // !SHADER_LIST_H
