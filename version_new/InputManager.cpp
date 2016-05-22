#include "IncludeStd.h"
#include "InputManager.h"

InputManager* InputManager::instance;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}


InputManager* InputManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new InputManager();
	}
	return instance;
}

bool InputManager::getMouseButton(int buttonNum)
{
	return buttons[buttonNum].curState == MOUSE_PRESSED;
}
bool InputManager::getMouseButtonDown(int buttonNum)
{
	return buttons[buttonNum].curState == MOUSE_PRESSED && buttons[buttonNum].lastState == MOUSE_RELEASED;
}
bool InputManager::getMouseButtonUp(int buttonNum)
{
	return buttons[buttonNum].curState == MOUSE_RELEASED && buttons[buttonNum].lastState == MOUSE_PRESSED;
}

void InputManager::update()
{
	for (int i = 0; i < 3; i++)
	{
		buttons[i].lastState = buttons[i].curState;
		buttons[i].curState = glfwGetMouseButton(glfwGetCurrentContext(), i);
	}
}