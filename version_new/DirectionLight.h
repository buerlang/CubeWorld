#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H


#include "Component.h"
class DirectionalLight :
	public Component
{
public:
	Register_Info(DirectionalLight);

	static DirectionalLight* main;
	unsigned int shadowMap;
	unsigned int FBO;
	unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

	virtual void start() override;
	virtual void update() override;

};



#endif // !DIRECTIONAL_LIGHT_H
