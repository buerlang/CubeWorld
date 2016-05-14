#include "TimeManager.h"

#include <GLFW\glfw3.h>

TimeManager* TimeManager::instance = nullptr;

TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{
	if (TimeManager::instance != nullptr)
		delete TimeManager::instance;
}

TimeManager* TimeManager::getInstance()
{
	if (instance == nullptr)
		instance = new TimeManager();
	return instance;
}

void TimeManager::beginDelta()
{
	mark = glfwGetTime();
}

void TimeManager::endDelta()
{
	delta = glfwGetTime() - mark;
}

float TimeManager::getFPS()
{
	if (delta == 0)
		return 0;
	return 1.0 / delta;
}