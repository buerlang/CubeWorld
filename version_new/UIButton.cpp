#include "IncludeClass.h"


void UIButton::start()
{
	object->addComponent(UIImage);
	object->addComponent(UIAnimator);
	renderer = object->getComponent(Renderer);
}

void UIButton::onMouseEnter()
{
	object->getComponent(UITransform)->localPosition += vec3(-2, 2, 0);
	renderer->setValue("_Emission", vec3(0.2f, 0.2f, 0.2f));
	/*UITransAnimation* anim = new UITransAnimation(object, object->getComponent(UITransform)->offset.x, object->getComponent(UITransform)->offset.y, object->getComponent(UITransform)->offset.x - 20, object->getComponent(UITransform)->offset.y, 0.2f, false, STOP_AT_DESTINATION);
	anim->start();*/
}
void UIButton::onMousePress()
{
	renderer->setValue("_Sink", vec2(2.0f, -2.0f));
	renderer->setValue("_Emission", vec3(-0.2f, -0.2f, -0.2f));
}
void UIButton::onMouseLeave()
{
	renderer->resumeMaterial();
}
void UIButton::onMouseClick()
{
	if (onClick)
		onClick();
}