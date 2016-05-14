#include "IncludeClass.h"

using namespace glm;

Camera* Camera::mainCamera;


void Camera::start()
{

}

void Camera::update()
{
	if (mainCamera == nullptr)
	{
		mainCamera = this;
	}
}

void Camera::onDestroy()
{

}

mat4 Camera::getViewMatrix()
{
	Transform* transform = object->getTransform();
	vec3 eye = transform->getGlobalPosition();
	vec3 rot = transform->getGlobalRotation();
	mat4 rotation = rotate(mat4(), radians(rot.x), vec3(1.0, 0.0, 0.0));
	rotation = rotate(rotation, radians(rot.y), vec3(0.0, 1.0, 0.0));
	rotation = rotate(rotation, radians(rot.z), vec3(0.0, 0.0, 1.0));
	vec3 front = vec3(rotation * vec4(0, 0, -1, 1));
	vec3 center = eye + front;
	vec3 up = vec3(rotation * vec4(0, 1, 0, 1));
	/*std::cout << "eye: " << eye.x << "," << eye.y << "," << eye.z << std::endl;
	std::cout << "rot: " << rot.x << "," << rot.y << "," << rot.z << std::endl;
	std::cout << "front: " << front.x << "," << front.y << "," << front.z << std::endl;
	std::cout << "center: " << center.x << "," << center.y << "," << center.z << std::endl;
	std::cout << "up: " << up.x << "," << up.y << "," << up.z << std::endl;*/
	return lookAt(eye, center, up);
}

mat4 Camera::getProjectionMatrix()
{
	return perspective(fieldOfView, (float)Screen::Width / (float)Screen::Height, nearClip, farClip);
}

void Camera::setLookAt(vec3 at)
{

}