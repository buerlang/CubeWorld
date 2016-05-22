#include "IncludeClass.h"

Camera* Camera::mainCamera;


void Camera::start()
{
	if (mainCamera == nullptr)
	{
		mainCamera = this;
	}
}

void Camera::update()
{
	//Position = object->getTransform()->getGlobalPosition();
	AutoTransView(InputManager::getInstance()->mouseX, InputManager::getInstance()->mouseY);
}

void Camera::onDestroy()
{

}

mat4 Camera::getViewMatrix()
{
	//Transform* transform = object->getTransform();
	//vec3 eye = transform->getGlobalPosition();
	//vec3 rot = transform->getGlobalRotation();
	//mat4 rotation = rotate(mat4(), radians(rot.x), vec3(1.0, 0.0, 0.0));
	//rotation = rotate(rotation, radians(rot.y), vec3(0.0, 1.0, 0.0));
	//rotation = rotate(rotation, radians(rot.z), vec3(0.0, 0.0, 1.0));
	//vec3 front = vec3(rotation * vec4(0, 0, -1, 1));
	//vec3 center = eye + front;
	//vec3 up = vec3(rotation * vec4(0, 1, 0, 1));
	///*std::cout << "eye: " << eye.x << "," << eye.y << "," << eye.z << std::endl;
	//std::cout << "rot: " << rot.x << "," << rot.y << "," << rot.z << std::endl;
	//std::cout << "front: " << front.x << "," << front.y << "," << front.z << std::endl;
	//std::cout << "center: " << center.x << "," << center.y << "," << center.z << std::endl;
	//std::cout << "up: " << up.x << "," << up.y << "," << up.z << std::endl;*/
	//return lookAt(eye, center, up);
	return lookAt(this->Position, this->TargetPosition, this->WorldUp);
}

mat4 Camera::getProjectionMatrix()
{
	return perspective(fieldOfView, (float)Screen::Width / (float)Screen::Height, nearClip, farClip);
}

void Camera::setLookAt(vec3 at)
{

}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::AutoTransView(float now_mouseX, float now_mouseY)
{
	float cameraSpeed = 0.1f;
	if (now_mouseX >= Screen::Width - minDetect && now_mouseX <= Screen::Width)
	{
		this->Direction = RIGHT;
	}
	if (now_mouseX <= minDetect)
	{
		this->Direction = LEFT;
	}
	if (now_mouseY >= Screen::Height - minDetect)
	{
		this->Direction = FORWARD;
	}
	if (now_mouseY <= minDetect)
	{
		this->Direction = BACKWARD;
	}
	if (now_mouseX > minDetect && now_mouseX < Screen::Width - minDetect&& now_mouseY>minDetect && now_mouseY < Screen::Width - minDetect) {

		this->Direction = NONE;
	}

	switch (Direction)
	{
	case RIGHT:
		Position += glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
		TargetPosition += glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
		break;
	case LEFT:
		Position -= glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
		TargetPosition -= glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
		break;
	case FORWARD:
		Position -= glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp))* cameraSpeed;
		TargetPosition -= glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp)) * cameraSpeed;
		break;
	case BACKWARD:
		Position += glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp))* cameraSpeed;
		TargetPosition += glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp)) * cameraSpeed;
		break;
	default:
		break;
	}
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::RotateView(GLfloat xoffset, GLfloat yoffset)
{
	glm::vec3 positionSaved;
	positionSaved = Position;
	Position = glm::vec3(glm::rotate(glm::mat4(), -((GLint)xoffset)* 10.0f / Screen::Width, WorldUp) * glm::vec4(positionSaved, 1.0f));
}