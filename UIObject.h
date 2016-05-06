#ifndef UIOBJECT_H
#define UIOBJECT_H

///////////////////////////////////////////////////
//                                               //
//   File:               UIObject.h              //
//   Class:              class UIObject          //
//   < Class Declaration >                       //
//   Description:        Base class of all UI    //
//                     UI elements.              //  
//                                               //
///////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <set>
#include <gl\glew.h>

class UIAnimation;

//-- Enum for UI layout alignments
enum UIAlignmentEnum {
	UI_TOP,
	UI_BOTTOM,
	UI_LEFT,
	UI_RIGHT,
	UI_CENTER,
	UI_TOP_LEFT,
	UI_TOP_RIGHT,
	UI_BOTTOM_LEFT,
	UI_BOTTOM_RIGHT
};

//-- Class UIObject
//-- Base class of all UI elements.
class UIObject
{
public:
	//=============================================== public Members ===================================================//

	//-- The custom name of this UI Object.
	std::string name;
	//-- Whether this UI object should be updated & rendered.
	bool localActive = true;
	//-- The position of this UI Object.(in pixel)
	int localOffsetX = 0, localOffsetY = 0;
	//-- The size of this UI Object.(in pixel)
	int width = 0, height = 0;
	//-- The scale of this UI Object.
	float scaleX = 1, scaleY = 1;
	//-- Alpha value (Opaque) of this UI image.
	float alpha = 1;
	//-- Parent UI object.
	UIObject* parent = nullptr;
	//-- Can this UI object picked by mouse.
	bool pickable = false;

	//=========================================== Constructors and Destructors ===========================================//
	
	//-- Constructor
	UIObject();
	//-- Constructor
	UIObject(char* name, char* imagePath, GLuint width, GLuint height, GLuint program);
	//-- Constructor
	UIObject(char* name, char* imagePath, GLuint width, GLuint height, GLint xPos, GLint yPos, GLuint program);
	//-- Constructor
	UIObject(char* name, char* imagePath, GLuint width, GLuint height, UIAlignmentEnum align, GLint offsetX, GLint offsetY, GLuint program);
	
	//-- Destructor
	virtual ~UIObject() { std::cout << name << ":destroyed" << std::endl; }

	//=============================================== public functions ==================================================//

	//-- Check if any parent UI object is inactive.
	//-- Return false if some parent is inactive.
	bool getActiveInParents();
	//-- Active setting.
	void setActive(bool localActive);


	//-- Alignment setting.
	void setAlignment(UIAlignmentEnum align, GLint offsetX, GLint offsetY);
	//-- Position setting.
	void setLocalPosition(GLuint x, GLuint y);
	//-- Scale setting.
	void setScale(float x, float y);
	//-- Set whether this UI object should receive mouse picking.
	void setReceivePick(bool receive);

	//-- Set Parent UI Object.
	void setParent(UIObject* parent);
	//-- Add a child UI Object.
	void addChild(UIObject* child);
	//-- Detach the link from parent UI object.
	void detachParent(UIObject* child);
	//-- Detach the link from a child UI object.
	void detachChild(UIObject* child);

	//-- Do picking test.
	//-- Called by the UIManager class.
	void pickTest(GLuint mouseX, GLuint mouseY, UIObject** entered);

	//-- Add a new UI animation to the animation set.
	void addAnimation(UIAnimation* animation);
	//-- Clear the animation set of this UI object.
	void clearAnimation();

	//=============================================== public virtual functions ==================================================//

	//-- Update function.
	//-- Called in every frame.
	virtual void update();

	//-- Render this UI object.
	//-- Should be called in the Update() function.
	virtual void draw();

	//-- Mouse Callback Function.
	virtual void onEntered();
	//-- Mouse Callback Function.
	virtual void onPressed();
	//-- Mouse Callback Function.
	virtual void onClicked();
	//-- Mouse Callback Function.
	virtual void onLeaved();


protected:
	//=================================================== protected members ======================================================//

	//-- UI Alignment type in local.
	UIAlignmentEnum align = UI_BOTTOM_LEFT;
	//-- Texture ID of this UI object in GPU.
	//-- Bound in the Draw() function.
	GLuint texture = 0;
	//-- Number of indeces.
	int indecesNum = 0;
	//-- Vertex Array Object(VAO) ID of this UI object in GPU.
	//-- Bound in the Draw() function.
	GLuint VAO = 0;
	//-- Vertex Buffer Object(VBO) ID of this UI object in GPU.
	//-- Bound in VAO.
	GLuint VBO = 0;
	//-- Shader program ID of this UI object in GPU.
	//-- Used in the Draw() function.
	GLuint program = 0;
	//-- Set of available UI animations of this UI object.
	//-- Each animation would be updated in the Update() function.
	std::set<UIAnimation*> animations;
	//-- Whether to receive mouse picking.
	bool receivePick = true;
	//-- Set of children UI objects.
	std::set<UIObject*> children;

	//=================================================== protected functions ======================================================//

	//-- Return the x position in local screen space.
	float getLocalPosX();
	//-- Return the y position in local screen space.
	float getLocalPosY();
	//-- Return the x position in global screen space.
	float getGlobalPosX();
	//-- Return the y position in global screen space.
	float getGlobalPosY();
	//-- Return the left boundary in global screen space.
	float getLeft();
	//-- Return the right boundary in global screen space.
	float getRight();
	//-- Return the top boundary in global screen space.
	float getTop();
	//-- Return the bottom boundary in global screen space.
	float getBottom();

	//-- Generate GPU texture ID from the give image path.
	void genTexture(char* imagePath);
	//-- Generate VAO & VBO.
	virtual void genBuffer();
};


#endif // !UIOBJECT_H