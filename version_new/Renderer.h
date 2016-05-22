#ifndef RENDERER_H
#define RENDERER_H

#include "IncludeStd.h"
#include "Component.h"
#include "RenderManager.h"
#include "Shader.h"

class Material;
class Mesh;

class Renderer :
	public Component
{
public:
	Register_Info(Renderer)

	Material* defaultMaterial = nullptr;
	Material* material = nullptr;
	Mesh* mesh;

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	void setMaterial(Material* material)
	{
		if(material)
			RenderManager::getInstance()->unRegisterObject(object);
		this->defaultMaterial = this->material = material;
		RenderManager::getInstance()->registerObject(object);
	}

	void setMesh(Mesh* mesh)
	{
		this->mesh = mesh;
	}

	void resumeMaterial()
	{
		if (material != defaultMaterial)
		{
			RenderManager::getInstance()->unRegisterObject(object);
			delete material;
			material = defaultMaterial;
			RenderManager::getInstance()->registerObject(object);
		}
	}

	void cloneMaterial()
	{
		RenderManager::getInstance()->unRegisterObject(object);
		if (material != defaultMaterial)
		{
			delete material;
		}
		material = new Material();
		material->setShader(defaultMaterial->shader)
			->setBegin(defaultMaterial->onBegin)
			->setDraw(defaultMaterial->onDraw)
			->setEnd(defaultMaterial->onEnd)
			->setHasAlpha(defaultMaterial->hasAlpha)
			->setTexture(defaultMaterial->texture);

		RenderManager::getInstance()->registerObject(object);
	}

	void setValue(char* name, float value)
	{
		cloneMaterial();
		material->setExtraBegin([=]() {
			glUniform1f(material->shader->getUniform(name), value);
		});
	}
	void setValue(char* name, int value)
	{
		cloneMaterial();
		material->setExtraBegin([=]() {
			glUniform1i(material->shader->getUniform(name), value);
		});
	}
	void setValue(char* name, vec2 value)
	{
		cloneMaterial();
		material->setExtraBegin([=]() {
			glUniform2f(material->shader->getUniform(name), value.x, value.y);
		});
	}
	void setValue(char* name, vec3 value)
	{
		cloneMaterial();
		material->setExtraBegin([=]() {
			glUniform3f(material->shader->getUniform(name), value.x, value.y, value.z);
		});
	}
};



#endif // !RENDERER_H

