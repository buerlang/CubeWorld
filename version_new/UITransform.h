#ifndef UI_TRANSFORM_H
#define UI_TRANSFORM_H

#include "Transform.h"

//-- Enum for UI layout alignments
enum UIAlignmentEnum {
	UI_TOP,
	UI_BOTTOM,
	UI_LEFT,
	UI_RIGHT,
	UI_CENTER,
	UI_TOP_LEFT,
	UI_TOP_RIGHT,
	UI_BOTTOM_LEFT,
	UI_BOTTOM_RIGHT
};

class UITransform :
	public Transform
{
public:
	Register_Info(UITransform)


	//-- The offset based on alignment mode of this UI Object.(in pixel)
	vec2 offset;
	//-- The size of this UI Object.(in pixel)
	vec2 size;
	//-- The scale of this UI Object.
	vec2 scale;

	//-- Alignment setting.
	void setAlignment(UIAlignmentEnum align, int offsetX, int offsetY);
	//-- Position setting.
	void setLocalPosition(int x, int y);
	//-- Scale setting.
	void setScale(float x, float y);
	//-- Size setting.
	void setSize(float width, float height);

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;
	virtual void onMouseEnter() override;
	virtual void onMouseOver() override;
	virtual void onMouseLeave() override;

	//-- UI Alignment type in local.
	UIAlignmentEnum align = UI_BOTTOM_LEFT;

	//-- Return the x position in local screen space.
	vec2 getLocalPosition();

	//-- Return the y position in global screen space.
	vec2 getGlobalPosition();
	//-- Return the left boundary in global screen space.
	float getLeft();
	//-- Return the right boundary in global screen space.
	float getRight();
	//-- Return the top boundary in global screen space.
	float getTop();
	//-- Return the bottom boundary in global screen space.
	float getBottom();
};




#endif // !UI_TRANSFORM_H
