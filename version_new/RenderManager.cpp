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
	it = renderMap.find(material);
	if (it != renderMap.end())
	{
		renderMap.erase(it);
	}
}
void RenderManager::registerMaterial(Material* material)
{
	RenderMap::iterator it;
	it = renderMap.find(material);
	if (it == renderMap.end())
	{
		renderMap.insert(RenderMapItem(material, ObjectListInfo()));
	}
}
void RenderManager::registerObject(Object* object)
{
	Renderer* renderer = object->getComponent(Renderer);
	Material* mat;
	if (renderer)
	{
		mat = renderer->material;
	}
	RenderMap::iterator it;
	it = renderMap.find(mat);
	if (it != renderMap.end())
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
	}
	else 
	{
		return;
	}
	RenderMap::iterator it;
	/*for (it == renderMap.begin(); it != renderMap.end(); it++)
	{
		cout << it->first << endl;
	}
	cout << "ddd," << mat << endl;*/
	it = renderMap.find(mat);
	if (it != renderMap.end())
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
	// Check renderMap is or not empty.
	if (!renderMap.empty())
	{
		// Go through renderMap.
		for (RenderMap::iterator it = renderMap.begin(); it != renderMap.end(); it++)
		{
			// Check material object list is or not empty.
			if (!it->second.dynamicObjectList->empty())
			{
				// Start one material.
				glUseProgram(it->first->shader);
				glUniform2f(it->first->getUniform("_ScrSize"), Screen::Width, Screen::Height);
				glUniformMatrix4fv(it->first->getUniform("_Model"), 1, GL_FALSE, glm::value_ptr(mat4()));
				glUniformMatrix4fv(it->first->getUniform("_View"), 1, GL_FALSE, glm::value_ptr(Camera::mainCamera->getViewMatrix()));
				glUniformMatrix4fv(it->first->getUniform("_Projection"), 1, GL_FALSE, glm::value_ptr(Camera::mainCamera->getProjectionMatrix()));

				it->first->begin();
				it->first->extraBegin();

				for (ObjectList::iterator objIt = it->second.dynamicObjectList->begin(); objIt != it->second.dynamicObjectList->end(); objIt++)
				{
					it->first->render(*objIt);
				}
				
				it->first->end();
			}
			if (!it->second.staticObjectList->empty())
			{
				// Start one material.
				glUseProgram(it->first->shader);
				glUniform2f(it->first->getUniform("_ScrSize"), Screen::Width, Screen::Height);
				glUniformMatrix4fv(it->first->getUniform("_Model"), 1, GL_FALSE, glm::value_ptr(mat4()));
				glUniformMatrix4fv(it->first->getUniform("_View"), 1, GL_FALSE, glm::value_ptr(Camera::mainCamera->getViewMatrix()));
				glUniformMatrix4fv(it->first->getUniform("_Projection"), 1, GL_FALSE, glm::value_ptr(Camera::mainCamera->getProjectionMatrix()));

				it->first->begin();
				it->first->extraBegin();
				glBindVertexArray(it->second.batchedMesh->VAO);
				glDrawElements(GL_TRIANGLES, it->second.batchedMesh->getIndexCount(), GL_UNSIGNED_INT, 0);
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
			ObjectList* list = it->second.staticObjectList;
			if (!list->empty())
			{
				// If having Objects attached.
				Mesh** batched = &it->second.batchedMesh;
				if (*batched != nullptr)
					delete *batched;
				*batched = new Mesh();

				int verticesCount = 0;
				for (ObjectList::iterator objIt = list->begin(); objIt != list->end(); objIt++)
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
							(*batched)->vertices.push_back(Vertex(vec3(obj->getTransform()->getModelMatrix() * vec4(ver.position, 1.0f))));
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
				cout << list->size()<<","<< (*batched)->getVertexCount() << "," << (*batched)->getIndexCount() << endl;
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