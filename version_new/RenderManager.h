#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "IncludeStd.h"

class Material;
class Object;
class Mesh;

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
	void makeBatch();
protected:
	RenderManager();
	static RenderManager* instance;
	RenderMap renderMap;
};



#endif // !RENDER_MANAGER_H
