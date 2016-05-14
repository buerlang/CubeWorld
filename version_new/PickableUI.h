#ifndef PICKABLE_UI_H
#define PICKABLE_UI_H


#include "Pickable.h"
class PickableUI :
	public Pickable
{
public:
	Register_Info(PickableUI)

	void pickTest(int mouseX, int mouseY, Object** out);
};



#endif // !PICKABLE_UI_H
