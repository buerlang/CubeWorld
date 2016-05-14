#include "Transform.h"

#include "Object.h"

void Transform::start()
{
	
}
void Transform::update()
{
	//vec3 p;
	//getGlobalPosition(p);
	//std::cout << "[" << object->name << "]" << "[Transform Update Info]: " << p.x << ", " << p.y << ", " << p.z << std::endl;
}
void Transform::onDestroy()
{

}

vec3 Transform::getGlobalPosition()
{
	vec3 out = localPosition;
	if (object->parent != nullptr)
	{
		out += object->parent->getTransform()->getGlobalPosition();
	}
	return out;
}
vec3 Transform::getGlobalRotation()
{
	vec3 out = localRotation;
	if (object->parent != nullptr)
	{
		out += object->parent->getTransform()->getGlobalRotation();
	}
	return out;
}
vec3 Transform::getGlobalScale()
{
	vec3 out = localScale;
	if (object->parent != nullptr)
	{
		vec3 p = object->parent->getTransform()->getGlobalScale();
		out = vec3(out.x * p.x, out.y * p.y, out.z * p.z);
	}
	return out;
}

mat4 Transform::getModelMatrix()
{
	mat4 out = translate(glm::mat4(), getGlobalPosition());
	out = rotate(out, getGlobalRotation().x, vec3(1.0f, 0.0f, 0.0f));
	out = rotate(out, getGlobalRotation().y, vec3(0.0f, 1.0f, 0.0f));
	out = rotate(out, getGlobalRotation().z, vec3(0.0f, 0.0f, 1.0f));
	out = scale(out, getGlobalScale());
	return out;
}