#include "IncludeClass.h"

void BoxCollider::setBox(vec3 min, vec3 max)
{
	this->min = min;
	this->max = max;
}

void BoxCollider::start()
{
	PickManager::getInstance()->registerObject(object, false);
}

void BoxCollider::onDestroy()
{
	PickManager::getInstance()->unRegisterObject(object, false);
}