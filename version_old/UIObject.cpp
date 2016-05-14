///////////////////////////////////////////////////
//                                               //
//   File:               UIObject.cpp            //
//   Class:              class UIObject          //
//   < Class function definition >               //
//   Description:        Base class of all UI    //
//                     UI elements.              //  
//                                               //
///////////////////////////////////////////////////

#include "UIObject.h"
#include "UIAnimation.h"
#include <SOIL.h>
#include <iostream>
#include <GLFW\glfw3.h>

//-- Constructor
UIObject::UIObject() 
{
	new(this) UIObject("", "", 0, 0, 0);
}
//-- Constructor
UIObject::UIObject(char* name, char* imagePath, GLuint width, GLuint height, GLuint program)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->program = program;

	genTexture(imagePath);
	genBuffer();

	std::cout << name << " Created!" << std::endl;
}
//-- Constructor
UIObject::UIObject(char* name, char* imagePath, GLuint width, GLuint height, GLint x, GLint y, GLuint program)
{
	new(this) UIObject(name, imagePath, width, height, program);
	this->setLocalPosition(x, y);
}
//-- Constructor
UIObject::UIObject(char* name, char* imagePath, GLuint width, GLuint height, UIAlignmentEnum align, GLint offsetX, GLint offsetY, GLuint program)
{
	new(this) UIObject(name, imagePath, width, height, program);
	this->setAlignment(align, offsetX, offsetY);
}

//-- Update function.
//-- Called in every frame.
void UIObject::update()
{
	//std::cout << name << " updated!" << std::endl;
	std::set<UIAnimation*>::iterator it;
	for (it = animations.begin(); it != animations.end(); )
	{
		if ((*it)->getIsOver())
		{
			(*it)->end();
			delete *it;
			it = animations.erase(it);
		}
		else
		{
			(*it)->update();
			it++;
		}
	}
	draw();
}

//-- Check if any parent UI object is inactive.
//-- Return false if some parent is inactive.
bool UIObject::getActiveInParents()
{
	if (!localActive)
		return false;
	for (UIObject* i = this; i->parent != nullptr; i = i->parent)
	{
		if (!i->parent->localActive)
			return false;
	}
	return true;
}
//-- Active setting.
void UIObject::setActive(bool localActive)
{
	this->localActive = localActive;
}

//-- Alignment setting.
void UIObject::setAlignment(UIAlignmentEnum align, GLint offsetX, GLint offsetY)
{	
	this->align = align;
	this->localOffsetX = offsetX;
	this->localOffsetY = offsetY;
}
//-- Position setting.
void UIObject::setLocalPosition(GLuint x, GLuint y)
{
	//align = UI_BOTTOM_LEFT;
	localOffsetX = x;
	localOffsetY = y;
}
//-- Scale setting.
void UIObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;
}

//-- Set Parent UI Object.
void UIObject::setParent(UIObject* parent)
{
	this->parent = parent;
}
//-- Add a child UI Object.
void UIObject::addChild(UIObject* child)
{
	this->children.insert(child);
}
//-- Detach the link from parent UI object.
void UIObject::detachParent(UIObject* parent)
{
	if (parent != nullptr)
	{
		parent->detachChild(this);
	}
}
//-- Detach the link from a child UI object.
void UIObject::detachChild(UIObject* child)
{
	if (children.find(child) != children.end())
	{
		child->parent = nullptr;
		children.erase(child);
	}
}

//-- Render this UI object.
//-- Should be called in the Update() function.
void UIObject::draw()
{
	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "_Emission"), 0.0f, 0.0f, 0.0f);
	glUniform2f(glGetUniformLocation(program, "_Sink"), 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(program, "_UVFactor"), 0.0f);
	glUniform2f(glGetUniformLocation(program, "_Scale"), scaleX, scaleY);
	glUniform1f(glGetUniformLocation(program, "_Opaque"), alpha);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "_Image"), 0);

	int w, h;
	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	glUniform2f(glGetUniformLocation(program, "_ScrSize"), w, h);
	glUniform2f(glGetUniformLocation(program, "_Position"), getGlobalPosX(), getGlobalPosY());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indecesNum, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//-- Do picking test.
//-- Called by the UIManager class.
void UIObject::pickTest(GLuint mouseX, GLuint mouseY, UIObject** entered)
{	
	std::cout << name << " Do Pick Test: " << receivePick << std::endl;
	if (pickable && receivePick)
	{
		/*std::cout << "left: " << getLeft() << std::endl;
		std::cout << "right: " << getRight() << std::endl;
		std::cout << "top: " << getTop() << std::endl;
		std::cout << "bottom: " << getBottom() << std::endl;
		std::cout << "mouse: " << mouseX << ", " << mouseY << std::endl;
		std::cout << "global: " << getGlobalPosX() << ", " << getGlobalPosY() << std::endl;
		std::cout << "local: " << getLocalPosX() << ", " << getLocalPosY() << std::endl;*/
		if (mouseX >= getLeft() && mouseX <= getRight() && mouseY >= getBottom() && mouseY <= getTop())
		{
			*entered = this;
			return;
		}
	}
	//*entered = nullptr;
}

//-- Add a new UI animation to the animation set.
void UIObject::addAnimation(UIAnimation* animation)
{
	this->animations.insert(animation);
}
//-- Clear the animation set of this UI object.
void UIObject::clearAnimation()
{
	std::set<UIAnimation*>::iterator it;
	for (it = animations.begin(); it != animations.end(); )
	{
		if (*it != nullptr)
			delete *it;
	}
	this->animations.clear();
}

//-- Set whether this UI object should receive mouse picking.
void UIObject::setReceivePick(bool receive)
{
	if (receive)
	{
		//std::cout << name + ": Receive Pick." << std::endl;
		receivePick = true;
	}
	else
	{
		//std::cout << name + ": Doesn't Receive Pick." << std::endl;
		onLeaved();
		receivePick = false;
	}
}

//-- Mouse Callback Function.
void UIObject::onEntered()
{
	//std::cout << name + ":Entered!" << std::endl;
}
//-- Mouse Callback Function.
void UIObject::onPressed()
{

}
//-- Mouse Callback Function.
void UIObject::onClicked()
{
	//std::cout << name + ":Clicked!" << std::endl;
}
//-- Mouse Callback Function.
void UIObject::onLeaved()
{
	//std::cout << name + ":Leaved!" << std::endl;
}

//-- Return the x position in local screen space.
float UIObject::getLocalPosX()
{
	float localPosX = 0;
	int w, h;
	if (parent == nullptr)
	{		
		glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	}
	else
	{
		w = parent->width;
	}
	switch (align)
	{
	case UI_CENTER:
	case UI_TOP:
	case UI_BOTTOM:
		localPosX = w / 2 - width / 2 + localOffsetX;
		break;
	case UI_LEFT:
	case UI_TOP_LEFT:
	case UI_BOTTOM_LEFT:
		localPosX = 0 + localOffsetX;
		break;
	case UI_RIGHT:
	case UI_TOP_RIGHT:
	case UI_BOTTOM_RIGHT:
		localPosX = w - width + localOffsetX;
		break;
	default:
		break;
	}
	return localPosX;
}
//-- Return the y position in local screen space.
float UIObject::getLocalPosY()
{
	float localPosY = 0;
	int w, h;
	if (parent == nullptr)
	{
		glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	}
	else
	{
		h = parent->height;
	}
	switch (align)
	{
	case UI_TOP:
	case UI_TOP_LEFT:
	case UI_TOP_RIGHT:
		localPosY = h - height + localOffsetY;
		break;
	case UI_CENTER:
	case UI_LEFT:
	case UI_RIGHT:
		localPosY = h / 2 - height / 2 + localOffsetY;
		break;
	case UI_BOTTOM:
	case UI_BOTTOM_LEFT:
	case UI_BOTTOM_RIGHT:
		localPosY = 0 + localOffsetY;
		break;
	default:
		break;
	}
	return localPosY;
}
//-- Return the x position in global screen space.
float UIObject::getGlobalPosX()
{
	if (parent == nullptr)
	{
		return getLocalPosX();
	}
	else
	{
		return parent->getGlobalPosX() + getLocalPosX();
	}
}
//-- Return the y position in global screen space.
float UIObject::getGlobalPosY()
{
	if (parent == nullptr)
	{
		return getLocalPosY();
	}
	else
	{
		return parent->getGlobalPosY() + getLocalPosY();
	}
}
//-- Return the left boundary in global screen space.
float UIObject::getLeft()
{
	return getGlobalPosX();
}
//-- Return the right boundary in global screen space.
float UIObject::getRight()
{
	return getGlobalPosX() + width;
}
//-- Return the top boundary in global screen space.
float UIObject::getTop()
{
	return getGlobalPosY() + height;
}
//-- Return the bottom boundary in global screen space.
float UIObject::getBottom()
{
	return getGlobalPosY();
}

//-- Generate GPU texture ID from the give image path.
void UIObject::genTexture(char* imagePath)
{
	// Generate Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture
	int w, h;
	unsigned char* image = SOIL_load_image(imagePath, &w, &h, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//-- Generate VAO & VBO.
void UIObject::genBuffer()
{
	// Mesh
	GLfloat vertices[] = {
		// Positions				// Texture Coords
		0,			height,			0.0f, 0.0f, // <-- ^
		0,			0,				0.0f, 1.0f, // <-- v
		width,		height,			1.0f, 0.0f, // --> ^
		width,		0,				1.0f, 1.0f  // --> v
	};
	GLuint indeces[] = {
		0, 1, 2,
		2, 1, 3
	};
	indecesNum = sizeof(indeces) / sizeof(GLuint);

	// Bind VAO
	GLuint EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
