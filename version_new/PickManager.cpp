#include "IncludeClass.h"

PickManager* PickManager::instance;

PickManager::PickManager()
{
}


PickManager::~PickManager()
{
}

PickManager* PickManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new PickManager();
	}
	return instance;
}

void PickManager::registerObject(Object* object, bool isUI)
{
	if (!isUI)
		objectList.push_back(object);
	else
		UIObjectList.push_back(object);
}

void PickManager::unRegisterObject(Object* object, bool isUI)
{
	if (!isUI)
		objectList.remove(object);
	else
		UIObjectList.remove(object);
}


void PickManager::update()
{
	lastPick = curPick;
	curPick = nullptr;
	distance = MAX_DISTANCE;

	bool uiPicked = false;
	//cout << UIObjectList.empty() << endl;
	if (!UIObjectList.empty())
	{
		for each (Object* obj in UIObjectList)
		{
			pickTestForUI(obj, InputManager::getInstance()->mouseX, InputManager::getInstance()->mouseY, &curPick);
			if (curPick)
			{
				uiPicked = true;
			}
		}
	}
	if (!uiPicked && !objectList.empty())
	{
		Ray ray;
		ScreenPosToWorldRay(
			InputManager::getInstance()->mouseX,
			InputManager::getInstance()->mouseY,
			Screen::Width, Screen::Height,
			Camera::mainCamera->getViewMatrix(),
			Camera::mainCamera->getProjectionMatrix(),
			&ray
			);
		for each (Object* obj in objectList)
		{
			pickTest(obj, &ray, &curPick, &distance);
		}
	}
	//if(curPick)
		//cout << curPick->name << endl;
	// Update the picking state of the picked UI Object
	if (curPick == nullptr)
	{
		if (lastPick != nullptr)
		{
			lastPick->onMouseLeave();
		}
	}
	else
	{
		//std::cout << curUIEntered->name << std::endl;
		curPick->onMouseOver();
		if (lastPick == nullptr)
		{
			if (!InputManager::getInstance()->getMouseButtonDown(MOUSE_LEFT))
				curPick->onMouseEnter();
		}
		else
		{
			if (lastPick == curPick)
			{
				if (InputManager::getInstance()->getMouseButtonUp(MOUSE_LEFT))
				{
					curPick->onMouseClick();
					curPick->onMouseEnter();
				}
				else if (InputManager::getInstance()->getMouseButtonDown(MOUSE_LEFT))
				{
					curPick->onMousePress();
				}
			}
			else
			{
				lastPick->onMouseLeave();
				curPick->onMouseEnter();
			}
		}
	}
}

void PickManager::ScreenPosToWorldRay(
	int mouseX, int mouseY,              // Mouse position, in pixels, from bottom-left corner of the window
	int screenWidth, int screenHeight,   // Window size, in pixels
	mat4& ViewMatrix,               // Camera position and orientation
	mat4& ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
	Ray* ray_out)
{
	glm::vec4 lRayStart_NDC(
		((float)mouseX / (float)screenWidth - 0.5f) * 2.0f, // [0,640] -> [-1,1]
		((float)mouseY / (float)screenHeight - 0.5f) * 2.0f, // [0, 480] -> [-1,1]
		-1.0f, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
		);
	glm::vec4 lRayEnd_NDC(
		((float)mouseX / (float)screenWidth - 0.5f) * 2.0f,
		((float)mouseY / (float)screenHeight - 0.5f) * 2.0f,
		1.0f,
		1.0f
		);

	// Faster way (just one inverse)
	glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
	glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world /= lRayStart_world.w;
	glm::vec4 lRayEnd_world = M * lRayEnd_NDC; lRayEnd_world /= lRayEnd_world.w;


	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);

	// Output
	ray_out->origin = glm::vec3(lRayStart_world);
	ray_out->direction = glm::normalize(lRayDir_world);
}


void PickManager::pickTest(Object* object, Ray* ray, Object** out, float* distance)
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
void PickManager::pickTestForUI(Object* object, int mouseX, int mouseY, Object** out)
{
	UITransform* trans = object->getComponent(UITransform);
	if (trans)
	{
		if (mouseX > trans->getLeft() && mouseX < trans->getRight() && mouseY > trans->getBottom() && mouseY < trans->getTop())
		{
			*out = object;
		}
	}
}

bool PickManager::TestRayOBBIntersection(Ray* ray, Object* object, float* distance_out)
{
	float tMin = 0.0f;
	float tMax = 100000.0f;

	vec3 OBBposition_worldspace = object->getTransform()->getGlobalPosition();
	mat4 modelMatrix = object->getTransform()->getModelMatrix();

	if (object->getComponent(BoxCollider))
		return false;
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