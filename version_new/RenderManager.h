#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "IncludeStd.h"

class Material;
class Object;
class Mesh;
class Camera;

typedef std::list<Object*> ObjectList;
struct ObjectListInfo
{
	ObjectList* dynamicObjectList;
	ObjectList* staticObjectList;
	Mesh* batchedMesh;
	ObjectListInfo();
};
typedef std::pair<Material*, ObjectListInfo> RenderMapItem;
typedef std::map<Material*, ObjectListInfo> RenderMap;


class RenderManager
{
public:
	~RenderManager();
	static RenderManager* getInstance();
	void unRegisterMaterial(Material* material);
	void registerMaterial(Material* material);
	void registerObject(Object* object);
	void unRegisterObject(Object* object);
	void render();
	void renderOpaque(Camera* camera);
	void renderTransparent(Camera* camera);
	void renderOpaqueWithShader(Camera* camera, Shader* shader);
	void renderTransparentWithShader(Camera* camera, Shader* shader);
	void renderWithShader(RenderMap* map, Camera* camera, Shader* shader);
	void render(RenderMap* map, Camera* camera);
	void makeBatch();
protected:
	RenderManager();
	static RenderManager* instance;
	RenderMap renderMap;
	RenderMap renderMapAlpha;
};



#endif // !RENDER_MANAGER_H
