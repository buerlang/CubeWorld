#include "IncludeClass.h"

Material::Material()
{
	RenderManager::getInstance()->registerMaterial(this);
}


Material::~Material()
{
	RenderManager::getInstance()->unRegisterMaterial(this);
}

Material* Material::create()
{
	return new Material();
}

Material* Material::setBegin(function<void()> onBegin)
{
	this->onBegin = onBegin;
	return this;
}
Material* Material::setExtraBegin(function<void()> onExtraBegin)
{
	this->onExtraBegin = onExtraBegin;
	return this;
}
Material* Material::setEnd(function<void()> onEnd)
{
	this->onEnd = onEnd;
	return this;
}
Material* Material::setDraw(function<void(Object*)> onDraw)
{
	this->onDraw = onDraw;
	return this;
}

Material* Material::setTexture(char* imagePath)
{
	// Generate Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture
	int w, h;
	unsigned char* image = SOIL_load_image(imagePath, &w, &h, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return this;
}
Material* Material::setTexture(GLuint texture)
{
	this->texture = texture;
	return this;
}

Material* Material::setShader(Shader* shader)
{
	this->shader = shader;
	return this;
}
Material* Material::setHasAlpha(bool hasAlpha)
{
	RenderManager::getInstance()->unRegisterMaterial(this);
	this->hasAlpha = hasAlpha;
	RenderManager::getInstance()->registerMaterial(this);
	return this;
}

void Material::begin()
{
	shader->Use();
	shader->begin();
	if(onBegin)
		onBegin();
}
void Material::extraBegin()
{
	if (onExtraBegin)
		onExtraBegin();
}
void Material::draw(Object* object)
{
	if (onDraw)
		onDraw(object);
}
void Material::render(Object* object)
{
	//cout << object->name << endl;
	Renderer* renderer = object->getComponent(Renderer);
	if (renderer)
	{
		draw(object);
		glBindVertexArray(renderer->mesh->VAO);
		glDrawElements(GL_TRIANGLES, renderer->mesh->indicesCount, GL_UNSIGNED_INT, 0);
		//std::cout << "Render!" << model[3].x << "," << model[3].y << "," << model[3].z << std::endl;
		//glBindVertexArray(0);
	}
	
}
void Material::end()
{
	shader->end();
	if(onEnd)
		onEnd();
	glUseProgram(0);
}
