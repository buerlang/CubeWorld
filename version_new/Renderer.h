#ifndef RENDERER_H
#define RENDERER_H

#include "IncludeStd.h"
#include "Component.h"
#include "RenderManager.h"

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

	void setFloat(char* name, float value)
	{
		RenderManager::getInstance()->unRegisterObject(object);
		material = new Material();
		material->shader = defaultMaterial->shader;
		material->texture = defaultMaterial->texture;
		for (UniformMap::iterator it = defaultMaterial->uniformMap.begin(); it != defaultMaterial->uniformMap.end(); it++)
		{
			material->uniformMap.insert(UniformMapItem(it->first, it->second));
		}
		material->onBegin = defaultMaterial->onBegin;
		material->onEnd = defaultMaterial->onEnd;
		material->setExtraBegin([=]() {
			glUniform1f(material->getUniform(name), value);
		});
		RenderManager::getInstance()->registerObject(object);
	}
};



#endif // !RENDERER_H

