#ifndef PICKABLE_H
#define PICKABLE_H

#include "Component.h"

struct Ray
{
	vec3 origin;
	vec3 direction;
};

class Pickable: public Component
{
public:
	Register_Info(Pickable)


	virtual void onEntered();
	virtual void onPressed();
	virtual void onLeaved();
	virtual void onClicked();

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	virtual void pickTest(Ray* ray, Object** out, float* distance);
	bool TestRayOBBIntersection(Ray* ray, Object* object, float* distance_out);
};


#endif // !PICKABLE_H

