#ifndef PICK_MANAGER_H
#define PICK_MANAGER_H

#include "IncludeStd.h"

struct Ray
{
	vec3 origin;
	vec3 direction;
};

class Object;
class PickManager
{
public:
	~PickManager();
	static PickManager* getInstance();

	Object* lastPick = nullptr;
	Object* curPick = nullptr;
	float distance = INFINITY;
	vec3 pickPoint;

	list<Object*> objectList;
	list<Object*> UIObjectList;
	void registerObject(Object* object, bool isUI);
	void unRegisterObject(Object* object, bool isUI);
	void update();
	static void ScreenPosToWorldRay(
		int mouseX, int mouseY,
		int screenWidth, int screenHeight,
		mat4& ViewMatrix,
		mat4& ProjectionMatrix,
		Ray* ray_out
		);
	void pickTest(Object* object, Ray* ray, Object** out, float* distance, vec3* pickPoint);
	void pickTestForUI(Object* object, int mouseX, int mouseY, Object** out);
	bool TestRayOBBIntersection(Ray* ray, Object* object, float* distance_out, vec3* pickPoint);
protected:
	PickManager();
	static PickManager* instance;
};



#endif // !PICK_MANAGER_H
