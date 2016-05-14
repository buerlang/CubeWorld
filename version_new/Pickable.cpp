#include "IncludeClass.h"


void Pickable::onEntered()
{
	
}
void Pickable::onPressed()
{

}
void Pickable::onLeaved()
{

}
void Pickable::onClicked()
{

}

void Pickable::start()
{
	if (!object->getComponent(BoxCollider))
	{
		object->addComponent(BoxCollider);
	}
	PickManager::getInstance()->registerObject(object, false);
}
void Pickable::update()
{

}
void Pickable::onDestroy()
{

}
void Pickable::pickTest(Ray* ray, Object** out, float* distance)
{
	float distance_out;
	if (TestRayOBBIntersection(ray, object, &distance_out))
	{
		if (distance_out < *distance)
		{
			*out = object;
			*distance = distance_out;
		}
	}
}

bool Pickable::TestRayOBBIntersection(Ray* ray, Object* object, float* distance_out)
{
	float tMin = 0.0f;
	float tMax = 100000.0f;

	vec3 OBBposition_worldspace = object->getTransform()->getGlobalPosition();
	mat4 modelMatrix = object->getTransform()->getModelMatrix();

	vec3 aabb_min = object->getComponent(BoxCollider)->min;
	vec3 aabb_max = object->getComponent(BoxCollider)->max;

	glm::vec3 delta = OBBposition_worldspace - ray->origin;	// from Ray Origin to OBB position

															// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		glm::vec3 xaxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
		float e = glm::dot(xaxis, delta);
		float f = glm::dot(ray->direction, xaxis);

		if (fabs(f) > 0.001f) { // Standard case

			float t1 = (e + aabb_min.x) / f; // Intersection with the "left" plane
			float t2 = (e + aabb_max.x) / f; // Intersection with the "right" plane
			if (t1>t2) {
				float w = t1; t1 = t2; t2 = w; // swap t1 and t2
			}

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;

			if (tMax < tMin)
				return false;
		}
		else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if (-e + aabb_min.x > 0.0f || -e + aabb_max.x < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		glm::vec3 yaxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(ray->direction, yaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.y) / f;
			float t2 = (e + aabb_max.y) / f;

			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;
		}
		else {
			if (-e + aabb_min.y > 0.0f || -e + aabb_max.y < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		glm::vec3 zaxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(ray->direction, zaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.z) / f;
			float t2 = (e + aabb_max.z) / f;

			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;
		}
		else {
			if (-e + aabb_min.z > 0.0f || -e + aabb_max.z < 0.0f)
				return false;
		}
	}

	*distance_out = tMin;
	return true;
}