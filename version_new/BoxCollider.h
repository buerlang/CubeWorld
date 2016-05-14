#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H


#include "Component.h"
class BoxCollider :
	public Component
{
public:
	Register_Info(BoxCollider);

	vec3 min;
	vec3 max;

	void setBox(vec3 min, vec3 max);
	virtual void start() override;
	virtual void onDestroy() override;
};



#endif // !BOX_COLLIDER_H
