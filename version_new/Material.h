#ifndef MATERIAL_H
#define MATERIAL_H

#include "IncludeStd.h"

class Object;
class Shader;

typedef pair<string, unsigned int> UniformMapItem;
typedef map<string, unsigned int> UniformMap;

class Material
{
public:
	Material();
	~Material();

	static Material* create();

	Shader* shader;
	//std::vector<GLuint> texture;
	GLuint texture;
	bool hasAlpha = false;

	function<void()> onBegin;
	function<void(Object*)> onDraw;
	function<void()> onEnd;
	function<void()> onExtraBegin;

	Material* setBegin(function<void()> onBegin);
	Material* setExtraBegin(function<void()> onExtraBegin);
	Material* setEnd(function<void()> onEnd);
	Material* setDraw(function<void(Object*)> onDraw);
	Material* setTexture(char* image);
	Material* setTexture(GLuint texture);
	Material* setShader(Shader* shader);
	Material* setHasAlpha(bool hasAlpha);
	void begin();
	void extraBegin();
	void draw(Object* object);
	void render(Object* object);
	void end();
};



#endif // !MATERIAL_H

