///////////////////////////////////////////////////
//                                               //
//   File:               UIObjectSliced.h        //
//   Class:              class UIObjectSliced    //
//   Inherit from:       class UIObject          //
//   < Class Function Definitions >              //
//   Description:        Class for UI sliced     //  
//                     images.                   //
//                                               //
///////////////////////////////////////////////////

#include "UIObjectSliced.h"

#pragma region Vertices_DEFINE
/*	   uv(0, 0)          xy(width, height)       */
/*	   	     0---1---2---3/                      */
/*	   	     | \ | \ | \ |/                      */
/*	   	     4---5---6---7                       */
/*	   	     | \ | \ | \ |                       */
/*	   	     8---9---10--11                      */
/*	   	     | \ | \ | \ |                       */
/*	   	     12--13--14--15                      */
/*	   xy(0, 0)			uv(1, 1)                 */
#define GenVertices() \
{ \
/* Positions */									/* Texture Coords */\
0,					height,						0.0f,    0.0f,		/*0*/\
sliceX1,			height,						sliceU1, 0.0f,		/*1*/\
width - sliceX2,	height,						sliceU2, 0.0f,		/*2*/\
width,				height,						1.0f,    0.0f,		/*3*/\
\
0,					height - sliceY2,			0.0f,    sliceV1,	/*4*/\
sliceX1,			height - sliceY2,			sliceU1, sliceV1,	/*5*/\
width - sliceX2,	height - sliceY2,			sliceU2, sliceV1,	/*6*/\
width,				height - sliceY2,			1.0f,    sliceV1,	/*7*/\
\
0,					sliceY1,					0.0f,    sliceV2,	/*8*/\
sliceX1,			sliceY1,					sliceU1, sliceV2,	/*9*/\
width - sliceX2,	sliceY1,					sliceU2, sliceV2,	/*10*/\
width,				sliceY1,					1.0f,    sliceV2,	/*11*/\
\
0,					0,							0.0f,    1.0f,		/*12*/\
sliceX1,			0,							sliceU1, 1.0f,		/*13*/\
width - sliceX2,	0,							sliceU2, 1.0f,		/*14*/\
width,				0,							1.0f,    1.0f		/*15*/\
}\

#pragma endregion

//-- Constructor
UIObjectSliced::UIObjectSliced(char* name, char* imagePath, GLuint width, GLuint height, GLuint program)
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
UIObjectSliced::UIObjectSliced(char* name, char* imagePath, GLuint width, GLuint height, GLint xPos, GLint yPos, GLuint program)
{
	new(this) UIObjectSliced(name, imagePath, width, height, program);
	setLocalPosition(xPos, yPos);
}
//-- Constructor
UIObjectSliced::UIObjectSliced(char* name, char* imagePath, GLuint width, GLuint height, UIAlignmentEnum align, GLint offsetX, GLint offsetY, GLuint program)
{
	new(this) UIObjectSliced(name, imagePath, width, height, program);
	setAlignment(align, offsetX, offsetY);
}

//-- UV Slice setting.
//-- Should be called rightly after instantiation and before setting its size.
void UIObjectSliced::setSlice(float sliceU1, float sliceU2, float sliceV1, float sliceV2)
{
	this->sliceU1 = sliceU1;	this->sliceX1 = width * sliceU1;
	this->sliceU2 = sliceU2;	this->sliceX2 = width * (1 - sliceU2);
	this->sliceV1 = sliceV1;	this->sliceY1 = height * (1 - sliceV2);
	this->sliceV2 = sliceV2;	this->sliceY2 = height * sliceV1;
	GLfloat vertices[] = GenVertices();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof vertices, vertices);
	glBindVertexArray(0);
}

//-- Image size setting.
//-- Make sure slices have been correctly setted before call this function.
void UIObjectSliced::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
	GLfloat vertices[] = GenVertices();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof vertices, vertices);
	glBindVertexArray(0);
}

//-- Generate VAO & VBO.
void UIObjectSliced::genBuffer()
{
	GLfloat vertices[] = GenVertices();
	GLuint indeces[] = {
		0, 4, 5,   0, 5, 1,
		1, 5, 6,   1, 6, 2,
		2, 6, 7,   2, 7, 3,
		4, 8, 9,   4, 9, 5,
		5, 9,10,   5,10, 6,
		6,10,11,   6,11, 7,
		8,12,13,   8,13, 9,
		9,13,14,   9,14,10,
		10,14,15,  10,15,11
	};
	indecesNum = sizeof (indeces) / sizeof (GLuint);


	// Bind VAO
	GLuint EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}