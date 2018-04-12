#include <Windows.h>
#include <GL\glew.h>

#include "graphics\RoomCube.h"

GLfloat roomVertices[] = {
	//Positions					Color
	-10.0f, 0.5f, -10.0f,		1.0f, 0.0f, 0.0f,// 0 Top Left-front  //x - y - r - g- b
	10.0f, 0.5f, -10.0f,		0.0f, 1.0f, 0.0f,// 1 Top Right-front
	10.0f, -0.5f, -10.0f,		0.0f, 0.0f, 1.0f,// 2 Bottom Right-front
	-10.0f, -0.5f, -10.0f,		1.0f, 1.0f, 1.0f,// 3 Bottom Left-front
	
	
	-10.0f, 0.5f, 10.0f,		1.0f, 0.0f, 0.0f,// 4 Top Left-back  //x - y - r - g- b
	10.0f, 0.5f, 10.0f,			0.0f, 1.0f, 0.0f,// 5 Top Right-back
	10.0f, -0.5f, 10.0f,		0.0f, 0.0f, 1.0f,// 6 Bottom Right-back
	-10.0f, -0.5f, 10.0f,		1.0f, 1.0f, 1.0f // 7 Bottom Left-back
};
GLuint roomElements[] = {
	//Front Wall
	0, 1, 2,
	2, 3, 0,

	//Back Wall
	4, 5, 6,
	6, 7, 4,

	//Left Wall
	4, 0, 3,
	3, 7, 4,

	//Right Wall
	1, 5, 6,
	6, 2, 1,

	//Ceiling
	4, 5, 1,
	1, 0, 4,
	
	//Floor
	7, 6, 2,
	2, 3, 7

};
RoomCube::RoomCube(Shader * shader) : Drawable() // so that we can use the vertexArrayObject
{
	this->bindVAO();
	this->loadVertices(roomVertices, 48);
	this->loadElements(roomElements, 36);
	this->positionAttribute = shader->getAttribute("position");
	this->colorAttribute = shader->getAttribute("color");

	glEnableVertexAttribArray(this->positionAttribute);
	glVertexAttribPointer(this->positionAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0); // this defines the position, offset by 0
	glEnableVertexAttribArray(this->colorAttribute);
	glVertexAttribPointer(this->colorAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //this defines the RGB , or in short color, offset by 2 times.
	/* void glVertexAttribPointer(	GLuint index,
	GLint size,
	GLenum type,
	GLboolean normalized,
	GLsizei stride,
	const GLvoid * pointer);
	*/

}
RoomCube::~RoomCube()
{

}