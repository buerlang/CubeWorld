#include "IncludeClass.h"
#include "Shader.h"

const int mapWidth = 50, mapHeight = 50;

Object *obj1, *mainCamera, *obj3;
Object* objs[mapWidth][mapHeight];
Material *uiMaterial, *redMaterial, *blueMaterial;
Mesh *UIQuad, *pyramid;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursor_pos_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int mouse, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);

void registerComponents()
{
	Transform::regist();
	TestComponent::regist();
	UITransform::regist();
	Renderer::regist();
	UIRenderer::regist();
	Camera::regist();
	Pickable::regist();
	PickableUI::regist();
	BoxCollider::regist();
	CameraControl::regist();
}

void setupMeshes()
{
	UIQuad = new Mesh();
	UIQuad->vertices.push_back(Vertex(0, 200, 0, 0, 0, 0, 0, 0));
	UIQuad->vertices.push_back(Vertex(0, 0, 0, 0, 0, 0, 0, 1));
	UIQuad->vertices.push_back(Vertex(200, 200, 0, 0, 0, 0, 1, 0));
	UIQuad->vertices.push_back(Vertex(200, 0, 0, 0, 0, 0, 1, 1));
	UIQuad->indices.push_back(Index(0, 1, 2));
	UIQuad->indices.push_back(Index(2, 1, 3));
	UIQuad->genBuffer();

	pyramid = new Mesh();
	pyramid->vertices.push_back(Vertex(0.5f, 0.0f, -0.5f));
	pyramid->vertices.push_back(Vertex(0.2f, 1.0f, -0.5f));
	pyramid->vertices.push_back(Vertex(0.9f, 1.0f, 0.1f));
	pyramid->vertices.push_back(Vertex(0.9f, 1.0f, -0.9f));
	pyramid->indices.push_back(Index(0, 1, 2));
	pyramid->indices.push_back(Index(0, 2, 3));
	pyramid->indices.push_back(Index(0, 3, 1));
	pyramid->indices.push_back(Index(1, 2, 3));
	pyramid->genBuffer();
}

void setupMaterials()
{
	uiMaterial = new Material();
	uiMaterial->setShader(LoadShader("UIVertex.vert", "UIFragment.frag"));
	uiMaterial->setTexture("container.png");
	uiMaterial->registerUniform("_Position");
	uiMaterial->registerUniform("_Sink");
	uiMaterial->registerUniform("_Scale");
	uiMaterial->registerUniform("_ScrSize");
	uiMaterial->registerUniform("_Image");
	uiMaterial->registerUniform("_UVFactor");
	uiMaterial->registerUniform("_Emission");
	uiMaterial->registerUniform("_Opaque");
	uiMaterial->setBegin([]() {
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, uiMaterial->texture);
		glUniform1i(uiMaterial->getUniform("Image"), 0);
		glUniform3f(uiMaterial->getUniform("_Emission"), 0.0f, 0.0f, 0.0f);
		glUniform2f(uiMaterial->getUniform("_Sink"), 0.0f, 0.0f);
		glUniform1f(uiMaterial->getUniform("_UVFactor"), 0.0f);
		glUniform2f(uiMaterial->getUniform("_Scale"), 1, 1);
		glUniform1f(uiMaterial->getUniform("_Opaque"), 1);
	});

	redMaterial = new Material();
	redMaterial->setShader(LoadShader("SingleColor.vert", "SingleColor.frag"));
	redMaterial->registerUniform("_Model");
	redMaterial->registerUniform("_View");
	redMaterial->registerUniform("_Projection");
	redMaterial->registerUniform("_Color");
	redMaterial->setBegin([]() {
		glUniform4f(redMaterial->getUniform("_Color"), 1, 0, 0, 1);
	});

	blueMaterial = new Material();
	blueMaterial->setShader(LoadShader("SingleColor.vert", "SingleColor.frag"));
	blueMaterial->registerUniform("_Model");
	blueMaterial->registerUniform("_View");
	blueMaterial->registerUniform("_Projection");
	blueMaterial->registerUniform("_Color");
	blueMaterial->setBegin([]() {
		glUniform4f(blueMaterial->getUniform("_Color"), 0, 0, 1, 1);
	});
}

void setupObjects()
{
	mainCamera = (new Object("Main Camera"))->addComponent(Camera)->addComponent(CameraControl);
	mainCamera->getTransform()->localPosition = vec3(10, 10, 10);
	mainCamera->getTransform()->localRotation = vec3(-45, 0, 0);

	obj1 = (new Object("obj1"))->addComponent(UITransform)->addComponent(Renderer);
	obj1->getComponent(UITransform)->setSize(200, 200);
	obj1->getComponent(Renderer)->setMesh(UIQuad);
	obj1->getComponent(Renderer)->setMaterial(uiMaterial);

	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			objs[i][j] = (new Object("obj3"))->addComponent(Renderer);
			objs[i][j]->setIsStatic(true);
			objs[i][j]->getComponent(Renderer)->setMesh(pyramid);
			if(i == j)
				objs[i][j]->getComponent(Renderer)->setMaterial(redMaterial);
			else
				objs[i][j]->getComponent(Renderer)->setMaterial(blueMaterial);
			objs[i][j]->getTransform()->localPosition = vec3(i, 0, j);		
		}
	}
}


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

	GLFWwindow* window = glfwCreateWindow(Screen::Width, Screen::Height, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	
	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, Screen::Width, Screen::Height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Setup Game
	registerComponents();
	setupMeshes();
	setupMaterials();
	setupObjects();
	RenderManager::getInstance()->makeBatch();
	

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		TimeManager::getInstance()->beginDelta();

		glfwPollEvents();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		InputManager::getInstance()->update();
		PickManager::getInstance()->update();
		ObjectManager::getInstance()->update();
		RenderManager::getInstance()->render();

		glfwSwapBuffers(window);

		TimeManager::getInstance()->endDelta();
		//cout << "[FPS]" << TimeManager::getInstance()->getFPS() << endl;
	}
	
	
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
	InputManager::getInstance()->mouseX = x;
	InputManager::getInstance()->mouseY = Screen::Height - y;
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
	/*UIProgram = LoadShader("UIvertex.vert", "UIfragment.frag");

	UI = new UIManager();

	UI1 = new Object("UI 1");
	UI1->addComponent("UIObject");*/

	/*Image = new UIObjectSliced("Image", "sliceimage.png", 100, 100, UI_CENTER, 0, 0, UIProgram);
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
	UI->add(UI3);*/
}
/*
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
}*/