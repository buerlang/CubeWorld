#ifndef UI_BUTTON_H
#define UI_BUTTON_H


#include "Component.h"
class UIButton :
	public Component
{
public:
	Register_Info(UIButton);

	function<void()> onClick;
	Renderer* renderer;

	virtual void start() override;
	virtual void onMouseEnter() override;
	virtual void onMousePress() override;
	virtual void onMouseLeave() override;
	virtual void onMouseClick() override;
};



#endif // !UI_BUTTON_H
