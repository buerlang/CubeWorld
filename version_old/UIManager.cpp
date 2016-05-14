///////////////////////////////////////////////////
//                                               //
//   File:               UIManager.cpp           //
//   Class:              class UIManager         //
//   < Class functions definitions >             //
//   Description:        Singleton.              //
//                       Hold & manage all UI.   //  
//                                               //
///////////////////////////////////////////////////


#include "UIManager.h"
#include <GLFW\glfw3.h>

UIManager::UIManager()
{
	
}

UIManager::~UIManager() 
{
	objects.clear();
}

//-- Add a new UI element to the UI Manager.
//-- UIObject must be pre-initialized.
void UIManager::add(UIObject* object)
{
	std::cout << object->name << " Added!" << std::endl;
	objects.push_back(object);
}

//-- Chek for any UI element being picked by mouse or not.
//-- Return True if any UI element is picked, and GameManager needn't do other picking tests.
bool UIManager::checkForMouseEvent(unsigned int mouseX, unsigned int mouseY)
{
	bool ret = false;

	// Keep the UI Object picked last frame
	lastUIEntered = curUIEntered;
	lastMouseState = curMouseState;

	// Do Pick Test for each UI Object
	curUIEntered = nullptr;
	std::list<UIObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		if ((*it)->getActiveInParents())
		{
			(*it)->pickTest(mouseX, mouseY, &curUIEntered);
			if (curUIEntered != nullptr)
			{
				ret = true;
				//break;
			}
		}			
	}
	
	curMouseState = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT);

	// Update the picking state of the picked UI Object
	if (curUIEntered == nullptr)
	{
		if (lastUIEntered != nullptr)
		{
			lastUIEntered->onLeaved();
		}
	}
	else
	{
		//std::cout << curUIEntered->name << std::endl;
		if (lastUIEntered == nullptr)
		{
			if(curMouseState == GLFW_RELEASE)
				curUIEntered->onEntered();
		}
		else
		{
			if (lastUIEntered == curUIEntered)
			{
				if (lastMouseState == GLFW_PRESS && curMouseState == GLFW_RELEASE)
				{
					curUIEntered->onClicked();
					curUIEntered->onEntered();
				}
				else if (lastMouseState == GLFW_RELEASE && curMouseState == GLFW_PRESS)
				{
					curUIEntered->onPressed();
				}
			}
			else
			{
				lastUIEntered->onLeaved();
				curUIEntered->onEntered();		
			}
		}
	}
	return ret;
}

//-- Draw all the UI elements.
void UIManager::update()
{
	std::list<UIObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		if ((*it)->getActiveInParents())
		{
			(*it)->update();
		}
	}
}
