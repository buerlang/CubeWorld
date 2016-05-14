#pragma once
#ifndef UI_SLICED_OBJECT
#define UI_SLICED_OBJECT

///////////////////////////////////////////////////
//                                               //
//   File:               UIObjectSliced.h        //
//   Class:              class UIObjectSliced    //
//   Inherit from:       class UIObject          //
//   < Class Declaration >                       //
//   Description:        Class for UI sliced     //  
//                     images.                   //
//                                               //
///////////////////////////////////////////////////

#include "UIObject.h"

//-- Class UIObjectSliced.
class UIObjectSliced :
	public UIObject
{
public:
	//================================================= Constructors & Destructor =======================================================//

	//-- Constructor
	UIObjectSliced(char* name, char* imagePath, GLuint width, GLuint height, GLuint program);
	//-- Constructor
	UIObjectSliced(char* name, char* imagePath, GLuint width, GLuint height, GLint xPos, GLint yPos, GLuint program);
	//-- Constructor
	UIObjectSliced(char* name, char* imagePath, GLuint width, GLuint height, UIAlignmentEnum align, GLint offsetX, GLint offsetY, GLuint program);
	//-- Destructor
	virtual ~UIObjectSliced() { std::cout << name << ":destroyed" << std::endl; }

	//================================================= public functions =======================================================//

	//-- UV Slice setting.
	//-- Should be called rightly after instantiation and before setting its size.
	//-- Members:
	//------ sliceU1: The first slice position of U texcoord (x).
	//------ sliceU2: The second slice position of U texcoord (x).
	//------ sliceV1: The first slice position of V texcoord (y).
	//------ sliceV2: The second slice position of V texcoord (y).
	//-- Range [0.0f, 1.0f]
	void setSlice(float sliceU1, float sliceU2, float sliceV1, float sliceV2);
	//-- Image size setting.
	//-- Make sure slices have been correctly setted before call this function.
	void setSize(int width, int height);

protected:
	//================================================= protected members =======================================================//

	//-- UV slices.
	float sliceU1 = 0, sliceU2 = 1, sliceV1 = 0, sliceV2 = 1;
	//-- sliced image border width. (in pixels) 
	int sliceX1 = 0, sliceX2 = width, sliceY1 = 0, sliceY2 = height;

	//================================================= protected overrides =======================================================//

	//-- Generate VAO & VBO.
	virtual void genBuffer() override;
};




#endif // !UI_SLICED_OBJECT

