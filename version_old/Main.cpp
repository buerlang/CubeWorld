#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <list>

#include "TimeManager.h"
#include "Shader.h"
#include "UIManager.h"
#include "UIObject.h"
#include "UIButton.h"
#include "UIObjectSliced.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursor_pos_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int mouse, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);

void setupUI();
void moveAway();

const int WIDTH = 1080, HEIGHT = 720;

GLuint mouseX, mouseY;

GLuint UIProgram;
UIManager *UI;
UIButton *UI1, *UI2, *UI3;
UIObjectSliced *Image;
UIButton *Back;


// The MAIN function, from here we start the application and run the game loop
int main()
{
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// window resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	// window borders and title
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "UI Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setupUI();
	
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		TimeManager::getInstance()->beginDelta();

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		UI->checkForMouseEvent(mouseX, mouseY);
		UI->update();

		glfwSwapBuffers(window);

		TimeManager::getInstance()->endDelta();
	}
	
	delete UI;

	glfwTerminate();
	system("pause");
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void cursor_pos_callback(GLFWwindow* window, double x, double y)
{
	mouseX = x;
	mouseY = HEIGHT - y;
}

void mouse_button_callback(GLFWwindow* window, int mouse, int action, int mode)
{
	
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void setupUI()
{
	// Create shader programs
	UIProgram = LoadShader("UIvertex.vert", "UIfragment.frag");

	UI = new UIManager();

	Image = new UIObjectSliced("Image", "sliceimage.png", 100, 100, UI_CENTER, 0, 0, UIProgram);
	Image->setSlice(0.25f, 0.75f, 0.25f, 0.75f);
	UI->add(Image);
	Back = new UIButton("Back", "button_start_default.png", 200, 40, UI_BOTTOM, 0, 40, UIProgram, 
		[]() {		
			UITransAnimation* anim = new UITransAnimation(Image, 0, 0, 0, HEIGHT, 0.4f, false, STOP_AT_DESTINATION);
			anim->start();
			anim->setOnStop([]() { Image->setActive(false); });
		});
	UI->add(Back);
	Back->setParent(Image);
	Image->setSize(Back->width + 20, Back->height + 200);
	Image->setActive(false);

	// The width of source image MUST! BE! MULTIPLE! OF! 4! !!!!!
	UI1 = new UIButton("UI 1", "button_start_default.png", 200, 40, UI_LEFT, 20, 20, UIProgram, []() {Image->setSize(200, 200); });
	UI2 = new UIButton("UI 2", "button_start_default.png", 200, 40, UI_LEFT, 20, -40, UIProgram, 
		[]() { 
			Image->setActive(true);
			UITransAnimation* anim = new UITransAnimation(Image, 0, -HEIGHT / 2 - Image->height, 0, 0, 0.4f, false, STOP_AT_DESTINATION);
			anim->start();
		});
	UI3 = new UIButton("UI 3", "button_start_default.png", 200, 40, UI_LEFT, 20, -100, UIProgram, moveAway);
	UI->add(UI1);
	UI->add(UI2);
	UI->add(UI3);
}

void moveAway()
{
	UITransAnimation* anim1 = new UITransAnimation(UI1, UI1->localOffsetX, UI1->localOffsetY, WIDTH + UI1->width / 2, UI1->localOffsetY, 0.5f, false, STOP_AT_DESTINATION);
	UITransAnimation* anim2 = new UITransAnimation(UI2, UI2->localOffsetX, UI2->localOffsetY, WIDTH + UI2->width / 2, UI2->localOffsetY, 0.5f, false, STOP_AT_DESTINATION);
	UIScaleAnimation* anim3 = new UIScaleAnimation(UI3, UI3->scaleX, UI3->scaleY, 3.0f, 3.0f, 0.5f, false, STOP_AT_DESTINATION);
	UITransAnimation* anim4 = new UITransAnimation(UI3, UI3->localOffsetX, UI3->localOffsetY, WIDTH + UI3->width / 2, UI3->localOffsetY, 0.5f, false, STOP_AT_DESTINATION);
	UIAlphaAnimation* anim5 = new UIAlphaAnimation(UI1, 1, 0, 0.5f, false, STOP_AT_DESTINATION);
	UIAlphaAnimation* anim6 = new UIAlphaAnimation(UI2, 1, 0, 0.5f, false, STOP_AT_DESTINATION);
	UIAlphaAnimation* anim7 = new UIAlphaAnimation(UI3, 1, 0, 0.5f, false, STOP_AT_DESTINATION);
	anim1->startAfter(0.0f);
	anim5->startAfter(0.0f);
	anim2->startAfter(0.2f);
	anim6->startAfter(0.2f);
	anim3->startAfter(0.4f);
	anim4->startAfter(0.4f);
	anim7->startAfter(0.4f);
}
