#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H


#include "Component.h"
class CameraControl :
	public Component
{
public:
	Register_Info(CameraControl);

	void update() override;
};



#endif // !CAMERA_CONTROL_H
