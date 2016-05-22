#ifndef CAMERA_H
#define CAMERA_H



#include "IncludeStd.h"
#include "Component.h"

enum Camera_Movement {
	NONE,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera :
	public Component
{
public:
	Register_Info(Camera);

	vec3 Position = vec3(10, 2, 10);
	vec3 TargetPosition = vec3(0, 0, 0);
	vec3 WorldUp = vec3(0, 1, 0);
	int Direction;

	static Camera* mainCamera;

	float fieldOfView = 45.0f;
	float nearClip = 0.1f;
	float farClip = 100.0f;
	float minDetect = 10.0f;

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	void setLookAt(vec3 at);

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void AutoTransView(float now_mouseX, float now_mouseY);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void RotateView(GLfloat xoffset, GLfloat yoffset);

	//// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	//void ProcessMouseScroll(GLfloat yoffset)
	//{
	//	if (this->fieldOfView >= 1.0f && this->fieldOfView <= 45.0f)
	//		this->fieldOfView -= yoffset;
	//	if (this->fieldOfView <= 1.0f)
	//		this->fieldOfView = 1.0f;
	//	if (this->fieldOfView >= 45.0f)
	//		this->fieldOfView = 45.0f;

	//}

};



#endif // !CAMERA_H

