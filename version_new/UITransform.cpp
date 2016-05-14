#include "IncludeClass.h"
#include "IncludeStd.h"

void UITransform::start()
{
	Transform::start();
	offset = vec2(0, 0);
	size = vec2(0, 0);
	scale = vec2(1, 1);
	PickManager::getInstance()->registerObject(object, true);
}
void UITransform::update()
{

}
void UITransform::onDestroy()
{
	PickManager::getInstance()->unRegisterObject(object, true);
}

void UITransform::onMouseEnter()
{
	if(object->getComponent(Renderer))
		object->getComponent(Renderer)->setFloat("_UVFactor", 0.5);
}
void UITransform::onMouseOver()
{
	
}
void UITransform::onMouseLeave()
{
	if (object->getComponent(Renderer))
		object->getComponent(Renderer)->resumeMaterial();
}

//-- Alignment setting.
void UITransform::setAlignment(UIAlignmentEnum align, int offsetX, int offsetY)
{
	this->align = align;
	this->offset = vec2(offsetX, offsetY);
}
//-- Position setting.
void UITransform::setLocalPosition(int x, int y)
{
	this->localPosition = vec3(x, y, localPosition.z);
}
//-- Scale setting.
void UITransform::setScale(float x, float y)
{
	this->scale = vec2(x, y);
}
//-- Size setting.
void UITransform::setSize(float width, float height)
{
	this->size = vec2(width, height);
}

//-- Return position in local screen space.
vec2 UITransform::getLocalPosition()
{
	vec2 localPosition = vec2(0, 0);
	vec2 parentSize = vec2(0, 0);
	if (object->parent == nullptr)
	{
		glfwGetWindowSize(glfwGetCurrentContext(), (int*)&(parentSize.x), (int*)&(parentSize.y));
	}
	else
	{
		parentSize = object->parent->getComponent(UITransform)->size;
	}
	switch (align)
	{
	case UI_CENTER:
	case UI_TOP:
	case UI_BOTTOM:
		localPosition.x = parentSize.x / 2 - size.x / 2 + offset.x;
		break;
	case UI_LEFT:
	case UI_TOP_LEFT:
	case UI_BOTTOM_LEFT:
		localPosition.x = 0 + offset.x;
		break;
	case UI_RIGHT:
	case UI_TOP_RIGHT:
	case UI_BOTTOM_RIGHT:
		localPosition.x = parentSize.x - size.x + offset.x;
		break;
	default:
		break;
	}
	switch (align)
	{
	case UI_TOP:
	case UI_TOP_LEFT:
	case UI_TOP_RIGHT:
		localPosition.y = parentSize.y - size.y + offset.y;
		break;
	case UI_CENTER:
	case UI_LEFT:
	case UI_RIGHT:
		localPosition.y = parentSize.y / 2 - size.y / 2 + offset.y;
		break;
	case UI_BOTTOM:
	case UI_BOTTOM_LEFT:
	case UI_BOTTOM_RIGHT:
		localPosition.y = 0 + offset.y;
		break;
	default:
		break;
	}
	return localPosition;
}

//-- Return position in global screen space.
vec2 UITransform::getGlobalPosition()
{
	if (object->parent == nullptr)
	{
		return getLocalPosition();
	}
	else
	{
		return getLocalPosition() + object->parent->getComponent(UITransform)->getGlobalPosition();
	}
}
//-- Return the left boundary in global screen space.
float UITransform::getLeft()
{
	return getGlobalPosition().x;
}
//-- Return the right boundary in global screen space.
float UITransform::getRight()
{
	return getGlobalPosition().x + size.x;
}
//-- Return the top boundary in global screen space.
float UITransform::getTop()
{
	return getGlobalPosition().y + size.y;
}
//-- Return the bottom boundary in global screen space.
float UITransform::getBottom()
{
	return getGlobalPosition().y;
}