#pragma once
#include "Component.h"
class UIImage :
	public Component
{
public:
	Register_Info(UIImage)
	
	virtual void start() override;

	//-- Alpha value (Opaque) of this UI image.
	float alpha = 1;

	UIImage* setImage(char* filepath);
};
