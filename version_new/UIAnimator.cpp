#include "UIAnimator.h"


//-- Add a new UI animation to the animation set.
void UIAnimator::addAnimation(UIAnimation* animation)
{
	this->animations.insert(animation);
}
//-- Clear the animation set of this UI object.
void UIAnimator::clearAnimation()
{
	set<UIAnimation*>::iterator it;
	for (it = animations.begin(); it != animations.end(); )
	{
		if (*it != nullptr)
			delete *it;
	}
	this->animations.clear();
}

void UIAnimator::update()
{
	std::set<UIAnimation*>::iterator it;
	for (it = animations.begin(); it != animations.end(); )
	{
		if ((*it)->getIsOver())
		{
			(*it)->end();
			delete *it;
			it = animations.erase(it);
		}
		else
		{
			(*it)->update();
			it++;
		}
	}
}