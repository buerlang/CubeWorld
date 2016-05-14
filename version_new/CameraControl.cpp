#include "IncludeClass.h"

void CameraControl::update()
{
	object->getTransform()->localRotation = vec3( - glfwGetTime() * 10, 0, 0);
}