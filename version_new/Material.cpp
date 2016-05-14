#include "IncludeClass.h"

Material::Material()
{
	RenderManager::getInstance()->registerMaterial(this);
}


Material::~Material()
{
	RenderManager::getInstance()->unRegisterMaterial(this);
}

void Material::setBegin(void(*onBegin)())
{
	this->onBegin = onBegin;
}
void Material::setExtraBegin(function<void()> onExtraBegin)
{
	this->onExtraBegin = onExtraBegin;
}
void Material::setEnd(void(*onEnd)())
{
	this->onEnd = onEnd;
}

void Material::setTexture(char* imagePath)
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
}

void Material::setShader(GLuint shaderID)
{
	this->shader = shaderID;
}
void Material::begin()
{
	glUseProgram(shader);
	if(onBegin)
		onBegin();
}
void Material::extraBegin()
{
	if (onExtraBegin)
		onExtraBegin();
}
void Material::render(Object* object)
{
	//cout << object->name << endl;
	Renderer* renderer = object->getComponent(Renderer);
	UIRenderer* uiRenderer = object->getComponent(UIRenderer);
	if (renderer)
	{
		Transform* transform = object->getComponent(Transform);
		glUniformMatrix4fv(getUniform("_Model"), 1, GL_FALSE, value_ptr(transform->getModelMatrix()));
		glBindVertexArray(renderer->mesh->VAO);
		glDrawElements(GL_TRIANGLES, renderer->mesh->indicesCount, GL_UNSIGNED_INT, 0);
		//std::cout << "Render!" << model[3].x << "," << model[3].y << "," << model[3].z << std::endl;
		//glBindVertexArray(0);
	}
	else if (uiRenderer)
	{
		UITransform* uiTransform =object->getComponent(UITransform);
		vec2 position = uiTransform->getGlobalPosition();	
		glUniform2f(getUniform("_Position"), position.x, position.y);
		glBindVertexArray(uiRenderer->mesh->VAO);
		glDrawElements(GL_TRIANGLES, uiRenderer->mesh->indicesCount, GL_UNSIGNED_INT, 0);
		//std::cout << "Render!" << position.x << position.y << std::endl;
		//glBindVertexArray(0);
	}
}
void Material::end()
{
	if(onEnd)
		onEnd();
	glUseProgram(0);
}

unsigned int Material::getUniform(char* name)
{
	if(uniformMap.find(name) != uniformMap.end())
		return uniformMap.find(name)->second;
	else return 0;
}
void Material::registerUniform(char* name)
{
	uniformMap.insert(pair<string, unsigned int>(name, glGetUniformLocation(shader, name)));
}