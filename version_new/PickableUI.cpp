#include "IncludeClass.h"

void PickableUI::pickTest(int mouseX, int mouseY, Object** out)
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