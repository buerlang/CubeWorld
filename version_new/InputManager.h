#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define MOUSE_PRESSED 0
#define MOUSE_RELEASED 1
#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2


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

	
	bool getMouseButtonPressed(int buttonNum);
	bool getMouseButtonDown(int buttonNum);
	bool getMouseButtonUp(int buttonNum);

	void update();

private:
	InputManager();
	static InputManager* instance;
	MouseButton buttons[3];

};



#endif // !INPUT_MANAGER_H
