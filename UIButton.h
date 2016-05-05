#ifndef UIBUTTON_H
#define UIBUTTON_H

///////////////////////////////////////////////////
//                                               //
//   File:               UIButton.h              //
//   Class:              class UIButton          //
//   Inherit from:       class UIObject          //
//   < Class Declaration >                       //
//   Description:        Class for UI Buttons.   //  
//                                               //
///////////////////////////////////////////////////

#include "UIObject.h"

typedef void(*ButtonOnClickFun)();

//-- Enum for UI Button Mouse Stat
enum MouseStatEnum {
	MOUSE_LEAVE,
	MOUSE_ENTERED,
	MOUSE_PRESSED,
	MOUSE_RELEASED
};

//-- Class UIButton
class UIButton: public UIObject
{
public:
	//==================================================== Consructors & Destructors ==================================================//

	//-- Constructor
	UIButton(char* name, char* imagePath, GLuint width, GLuint height, GLuint program, ButtonOnClickFun func);
	//-- Constructor
	UIButton(char* name, char* imagePath, GLuint width, GLuint height, GLint xPos, GLint yPos, GLuint program, ButtonOnClickFun func);
	//-- Constructor
	UIButton(char* name, char* imagePath, GLuint width, GLuint height, UIAlignmentEnum align, GLint offsetX, GLint offsetY, GLuint program, ButtonOnClickFun func);
	//-- Destructor
	virtual ~UIButton() { std::cout << name << ":destroyed" << std::endl; }

	//==================================================== public overrides ==========================================================//

	//-- Update function.
	//-- Called in every frame.
	void draw() override;
	//-- Mouse Callback Function.
	void onEntered() override;
	//-- Mouse Callback Function.
	void onPressed() override;
	//-- Mouse Callback Function.
	void onClicked() override;
	//-- Mouse Callback Function.
	void onLeaved() override;

protected:
	//===================================================== protected members ==========================================================//

	//-- Current mouse button state.
	//-- The draw() result will vary by different mouse state.
	MouseStatEnum mouseState = MOUSE_LEAVE;

	//-- Callback function pointer.
	//-- 0 parameters.
	//-- return void.
	//-- Call on left mouse button clicked.
	ButtonOnClickFun onClick;
};

#endif // !UIBUTTON_H
