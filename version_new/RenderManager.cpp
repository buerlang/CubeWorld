#include "IncludeClass.h"

RenderManager* RenderManager::instance;

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

RenderManager* RenderManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new RenderManager();
	}
	return instance;
}
void RenderManager::unRegisterMaterial(Material* material)
{
	RenderMap::iterator it;
	if (material->hasAlpha)
	{
		it = renderMapAlpha.find(material);
		if (it != renderMapAlpha.end())
		{
			renderMapAlpha.erase(it);
		}
	}
	else
	{
		it = renderMap.find(material);
		if (it != renderMap.end())
		{
			renderMap.erase(it);
		}
	}
}
void RenderManager::registerMaterial(Material* material)
{
	RenderMap::iterator it;
	if (material->hasAlpha)
	{
		it = renderMapAlpha.find(material);
		if (it == renderMapAlpha.end())
		{
			renderMapAlpha.insert(RenderMapItem(material, ObjectListInfo()));
		}
	}
	else
	{
		it = renderMap.find(material);
		if (it == renderMap.end())
		{
			renderMap.insert(RenderMapItem(material, ObjectListInfo()));
		}
	}
}
void RenderManager::registerObject(Object* object)
{
	Renderer* renderer = object->getComponent(Renderer);
	if (!renderer)
	{
		return;
	}
	Material* mat = renderer->material;
	RenderMap::iterator it;
	RenderMap* map;
	if (mat->hasAlpha)
	{
		map = &renderMapAlpha;
	}
	else
	{
		map = &renderMap;
	}
	it = map->find(mat);
	if (it != map->end())
	{
		if (object->getIsStatic())
		{
			it->second.staticObjectList->push_back(object);
		}
		else
		{
			it->second.dynamicObjectList->push_back(object);
		}
	}
}
void RenderManager::unRegisterObject(Object* object)
{
	Renderer* renderer = object->getComponent(Renderer);
	Material* mat;
	if (renderer)
	{
		mat = renderer->material;
		if (!mat)
		{
			return;
		}
	}
	else 
	{
		return;
	}
	RenderMap::iterator it;
	RenderMap* map;
	if (mat->hasAlpha)
	{
		map = &renderMapAlpha;
	}
	else
	{
		map = &renderMap;
	}
	it = map->find(mat);
	if (it != map->end())
	{
		if (object->getIsStatic())
		{
			it->second.staticObjectList->remove(object);
		}
		else
		{
			it->second.dynamicObjectList->remove(object);
		}
	}
}

void RenderManager::render()
{
	renderOpaque(Camera::mainCamera);
	renderTransparent(Camera::mainCamera);
}
void RenderManager::renderOpaque(Camera* camera)
{
	render(&renderMap, camera);
}
void RenderManager::renderTransparent(Camera* camera)
{
	render(&renderMapAlpha, camera);
}
void RenderManager::renderOpaqueWithShader(Camera* camera, Shader* shader)
{
	renderWithShader(&renderMap, camera, shader);
}
void RenderManager::renderTransparentWithShader(Camera* camera, Shader* shader)
{
	renderWithShader(&renderMapAlpha, camera, shader);
}
void RenderManager::renderWithShader(RenderMap* map, Camera* camera, Shader* shader)
{
	// Check renderMap is or not empty.
	if (!map->empty())
	{
		shader->Use();
		shader->begin();
		// Go through renderMap.
		for (RenderMap::iterator it = map->begin(); it != map->end(); it++)
		{
			// Check material object list is or not empty.
			if (!it->second.dynamicObjectList->empty())
			{
				
				for (ObjectList::iterator objIt = it->second.dynamicObjectList->begin(); objIt != it->second.dynamicObjectList->end(); objIt++)
				{
					if ((*objIt)->getActiveInParents())
					{
						glUniformMatrix4fv(shader->getUniform("_Model"), 1, GL_FALSE, value_ptr((*objIt)->getTransform()->getModelMatrix()));
						Renderer* renderer = (*objIt)->getComponent(Renderer);
						if (renderer)
						{
							glBindVertexArray(renderer->mesh->VAO);
							glDrawElements(GL_TRIANGLES, renderer->mesh->indicesCount, GL_UNSIGNED_INT, 0);
						}
					}
				}
			}
			if (!it->second.staticObjectList->empty())
			{
				// Start one material.
				glUniformMatrix4fv(shader->getUniform("_Model"), 1, GL_FALSE, value_ptr(mat4()));
				glBindVertexArray(it->second.batchedMesh->VAO);
				glDrawElements(GL_TRIANGLES, it->second.batchedMesh->getIndexCount() * sizeof(Index), GL_UNSIGNED_INT, 0);
			}
		}
	}
}
void RenderManager::render(RenderMap* map, Camera* camera)
{
	// Check renderMap is or not empty.
	if (!map->empty())
	{
		// Go through renderMap.
		for (RenderMap::iterator it = map->begin(); it != map->end(); it++)
		{
			// Check material object list is or not empty.
			if (!it->second.dynamicObjectList->empty())
			{
				// Start one material.
				it->first->shader->Use();
				glUniformMatrix4fv(it->first->shader->getUniform("_Model"), 1, GL_FALSE, value_ptr(mat4()));
				glUniformMatrix4fv(it->first->shader->getUniform("_View"), 1, GL_FALSE, value_ptr(camera->getViewMatrix()));
				glUniformMatrix4fv(it->first->shader->getUniform("_Projection"), 1, GL_FALSE, value_ptr(camera->getProjectionMatrix()));

				it->first->begin();
				it->first->extraBegin();

				for (ObjectList::iterator objIt = it->second.dynamicObjectList->begin(); objIt != it->second.dynamicObjectList->end(); objIt++)
				{
					if ((*objIt)->getActiveInParents())
					{
						glUniformMatrix4fv(it->first->shader->getUniform("_Model"), 1, GL_FALSE, value_ptr((*objIt)->getTransform()->getModelMatrix()));
						it->first->render(*objIt);
					}

				}
				
				it->first->end();
			}
			if (!it->second.staticObjectList->empty())
			{
				// Start one material.
				it->first->shader->Use();
				glUniformMatrix4fv(it->first->shader->getUniform("_Model"), 1, GL_FALSE, value_ptr(mat4()));
				glUniformMatrix4fv(it->first->shader->getUniform("_View"), 1, GL_FALSE, value_ptr(Camera::mainCamera->getViewMatrix()));
				glUniformMatrix4fv(it->first->shader->getUniform("_Projection"), 1, GL_FALSE, value_ptr(Camera::mainCamera->getProjectionMatrix()));

				it->first->begin();
				it->first->extraBegin();
				glBindVertexArray(it->second.batchedMesh->VAO);
				glDrawElements(GL_TRIANGLES, it->second.batchedMesh->getIndexCount() * sizeof(Index), GL_UNSIGNED_INT, 0);
				it->first->end();
			}
		}
	}
}



void RenderManager::makeBatch()
{
	if (!renderMap.empty())
	{
		for (RenderMap::iterator it = renderMap.begin(); it != renderMap.end(); it++)
		{
			// For each Material.
			ObjectList* staticList = it->second.staticObjectList;
			if (!staticList->empty())
			{
				// If having Objects attached.
				Mesh** batched = &it->second.batchedMesh;
				if (*batched != nullptr)
					delete *batched;
				*batched = new Mesh();

				int verticesCount = 0;
				for (ObjectList::iterator objIt = staticList->begin(); objIt != staticList->end(); objIt++)
				{
					// For each object.
					Object* obj = *objIt;
					
					// If static.
					Renderer* renderer = obj->getComponent(Renderer);
					if (renderer)
					{
						Mesh* objectMesh = renderer->mesh;
						int curVerticesCount = 0;
						for each (Vertex ver in objectMesh->vertices)
						{
							(*batched)->vertices.push_back(Vertex(vec3(obj->getTransform()->getModelMatrix() * vec4(ver.position, 1.0f)), ver.normal, ver.texCoord));
							curVerticesCount++;
							//cout << (*batched)->vertices.size() << endl;
						}
						//cout << "Vertices Batched!" << endl;
						for each (Index ind in objectMesh->indices)
						{
							(*batched)->indices.push_back(Index(ind.first + verticesCount, ind.second + verticesCount, ind.third + verticesCount));
						}
						//cout << "Indices Batched!" << endl;
						verticesCount += curVerticesCount;
					}
					
				}
				cout << "static Object counts: " << staticList->size() << endl;
				cout << "batched vertex count: " << (*batched)->getVertexCount() << endl;
				cout << "batched index count:" << (*batched)->getIndexCount() << endl;
				if((*batched)->getIndexCount())
					(*batched)->genBuffer();
			}
		}
	}
}

ObjectListInfo::ObjectListInfo()
{
	dynamicObjectList = new ObjectList();
	staticObjectList = new ObjectList();
	batchedMesh = new Mesh();
}