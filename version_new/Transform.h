#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform :
	public Component
{
public:
	Register_Info(Transform)
	
	vec3 localPosition = vec3(0, 0, 0);
	vec3 localRotation = vec3(0, 0, 0);
	vec3 localScale = vec3(1, 1, 1);

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	vec3 getGlobalPosition();
	vec3 getGlobalRotation();
	vec3 getGlobalScale();
	mat4 getModelMatrix();
};



#endif // !TRANSFORM_H
