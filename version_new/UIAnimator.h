#ifndef UI_ANIMATOR_H
#define UI_ANIMATOR_H


#include "Component.h"
#include "UIAnimation.h"

class UIAnimator :
	public Component
{
public:
	Register_Info(UIAnimator);

	set<UIAnimation*> animations;

	//-- Add a new UI animation to the animation set.
	void addAnimation(UIAnimation* animation);
	//-- Clear the animation set of this UI object.
	void clearAnimation();

	virtual void update() override;
};



#endif // !UI_ANIMATOR_H
