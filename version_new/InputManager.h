#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "IncludeStd.h"

#define MOUSE_PRESSED GLFW_PRESS
#define MOUSE_RELEASED GLFW_RELEASE
#define MOUSE_LEFT GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_RIGHT GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE


struct MouseButton
{
	int lastState = MOUSE_RELEASED;
	int curState = MOUSE_RELEASED;
};


class InputManager
{
public:
	~InputManager();
	static InputManager* getInstance();
	int mouseX, mouseY;

	
	bool getMouseButton(int buttonNum);
	bool getMouseButtonDown(int buttonNum);
	bool getMouseButtonUp(int buttonNum);

	void update();

private:
	InputManager();
	static InputManager* instance;
	MouseButton buttons[3];

};



#endif // !INPUT_MANAGER_H
