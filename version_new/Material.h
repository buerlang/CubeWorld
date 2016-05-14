#ifndef MATERIAL_H
#define MATERIAL_H

#include "IncludeStd.h"

class Object;

typedef pair<string, unsigned int> UniformMapItem;
typedef map<string, unsigned int> UniformMap;

class Material
{
public:
	Material();
	~Material();

	GLuint shader;
	//std::vector<GLuint> texture;
	GLuint texture;
	UniformMap uniformMap;

	void(*onBegin)();
	void(*onEnd)();
	function<void()> onExtraBegin;

	void setBegin(void(*onBegin)());
	void setExtraBegin(function<void()> onExtraBegin);
	void setEnd(void(*onEnd)());
	void setTexture(char* image);
	void setShader(GLuint shaderID);
	void begin();
	void extraBegin();
	void render(Object* object);
	void end();
	unsigned int getUniform(char* name);
	void registerUniform(char* name);
};



#endif // !MATERIAL_H

