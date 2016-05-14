#ifndef UI_MANAGER_H
#define UI_MANAGER_H

///////////////////////////////////////////////////
//                                               //
//   File:               UIManager.h             //
//   Class:              class UIManager         //
//   < Class Declaration >                       //
//   Description:        The UI Root class.      //
//                       Hold & manage all UI.   //  
//                                               //
///////////////////////////////////////////////////

#include <list>
#include "UIObject.h"
#include "UIButton.h"
#include "UIAnimation.h"


//-- The UI Root class.
//-- Containing & Managing all the UI elements.
class UIManager
{
public:
	UIManager();
	~UIManager();

	//-- Chek for any UI element being picked by mouse or not.
	//-- Return True if any UI element is picked, and GameManager needn't do other picking tests.
	bool checkForMouseEvent(unsigned int mouseX, unsigned int mouseY);

	//-- Add a new UI element to the UI Manager.
	//-- UIObject must be pre-initialized.
	void add(UIObject* object);

	//-- Draw all the UI elements.
	void update();

private:
	//-- List for storing all the UI elements.
	std::list<UIObject*> objects;
	//-- The UI element picked by mouse in the current frame.
	UIObject* curUIEntered = nullptr;
	//-- The UI element picked by mouse in the last frame.
	UIObject* lastUIEntered = nullptr;
	//-- The state of mouse in the current frame.
	int curMouseState;
	//-- The state of mouse in the last frame.
	int lastMouseState;
};

#endif // !UI_MANAGER_H
