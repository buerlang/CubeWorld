///////////////////////////////////////////////////
//                                               //
//   File:               UIButton.cpp            //
//   Class:              class UIButton          //
//   Inherit from:       class UIObject          //
//   < Class Function Definitions >              //
//   Description:        Class for UI Buttons.   //  
//                                               //
///////////////////////////////////////////////////

#include "UIButton.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include <math.h>

//-- Constructor
UIButton::UIButton(char* name, char* image, GLuint width, GLuint height, GLuint program, ButtonOnClickFun func)
		:UIObject(name, image, width, height, program)
{
	setReceivePick(true);
	this->onClick = func;
}
//-- Constructor
UIButton::UIButton(char* name, char* image, GLuint width, GLuint height, GLint xPos, GLint yPos, GLuint program, ButtonOnClickFun func)
	: UIObject(name, image, width, height, xPos, yPos, program)
{
	setReceivePick(true);
	this->onClick = func;
}
//-- Constructor
UIButton::UIButton(char* name, char* image, GLuint width, GLuint height, UIAlignmentEnum align, GLint offsetX, GLint offsetY, GLuint program, ButtonOnClickFun func)
	: UIObject(name, image, width, height, align, offsetX, offsetY, program)
{
	setReceivePick(true);
	this->onClick = func;
}

//-- Update function.
//-- Called in every frame.
void UIButton::draw()
{
	glUseProgram(program);

	if (receivePick)
	{
		switch (mouseState)
		{
		case MOUSE_LEAVE:
			//glUniform3f(glGetUniformLocation(program, "_Emission"), 0.0f, 0.0f, 0.0f);
			//glUniform2f(glGetUniformLocation(program, "_Sink"), 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(program, "_UVFactor"), 0.0f);
			setScale(1, 1);
			break;
		case MOUSE_ENTERED:
			//glUniform3f(glGetUniformLocation(program, "_Emission"), 0.2f, 0.2f, 0.4f);
			//glUniform2f(glGetUniformLocation(program, "_Sink"), 0.0f, -5.0f * sin(5 * glfwGetTime()) + 5.0f);
			glUniform1f(glGetUniformLocation(program, "_UVFactor"), 0.3f);
			setScale(1.05f, 1.05f);
			break;
		case MOUSE_PRESSED:
			//glUniform3f(glGetUniformLocation(program, "_Emission"), 0.4f, 0.2f, 0.2f);
			//glUniform2f(glGetUniformLocation(program, "_Sink"), 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(program, "_UVFactor"), -0.3f);
			setScale(0.95f, 0.95f);
			break;
		default:
			break;
		}
	}
	else
	{
		//glUniform3f(glGetUniformLocation(program, "_Emission"), 0.0f, 0.0f, 0.0f);
		//glUniform2f(glGetUniformLocation(program, "_Sink"), 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(program, "_UVFactor"), 0.0f);
	}

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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//-- Mouse Callback Function.
void UIButton::onEntered()
{
	if (!receivePick)
		return;
	//std::cout << name + ":Entered!" << std::endl;
	mouseState = MOUSE_ENTERED;
}
//-- Mouse Callback Function.
void UIButton::onPressed()
{
	if (!receivePick)
		return;
	//std::cout << name + ":Pressed!" << std::endl;
	mouseState = MOUSE_PRESSED;
}
//-- Mouse Callback Function.
void UIButton::onClicked()
{
	if (!receivePick)
		return;
	//std::cout << name + ":Clicked!" << std::endl;
	onClick();
}
//-- Mouse Callback Function.
void UIButton::onLeaved()
{
	if (!receivePick)
		return;
	//std::cout << name + ":Leaved!" << std::endl;
	mouseState = MOUSE_LEAVE;
}