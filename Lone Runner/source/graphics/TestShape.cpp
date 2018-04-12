#include <Windows.h>
#include <GL\glew.h>

#include "graphics\TestShape.h"

GLfloat vData[] = {
	//Vertices				Color
	-0.5f,  0.5f,			 1.0f, 0.0f, 0.0f, // Top-left
	0.5f,  0.5f,			 0.0f, 1.0f, 0.0f, // Top-right
	0.5f, -0.5f,			 0.0f, 0.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f,			 1.0f, 1.0f, 1.0f  // Bottom-left
};
GLuint eData[] = {

	0, 1, 2,
	2, 3, 0

};
TestShape::TestShape(Shader * shader) : Drawable() // so that we can use the vertexArrayObject
{
	this->bindVAO();
	this->loadVertices(vData, 20);
	this->loadElements(eData, 6);
	this->positionAttribute = shader->getAttribute("position");
	this->colorAttribute = shader->getAttribute("color");
	
	glEnableVertexAttribArray(this->positionAttribute);
	glVertexAttribPointer(this->positionAttribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0); // this defines the position, offset by 0
	glEnableVertexAttribArray(this->colorAttribute);
	glVertexAttribPointer(this->colorAttribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)( 2* sizeof(GLfloat))); //this defines the RGB , or in short color, offset by 2 times.
	/* void glVertexAttribPointer(	GLuint index,
 									GLint size,
 									GLenum type,
 									GLboolean normalized,
 									GLsizei stride,
 									const GLvoid * pointer);
 */

}
TestShape::~TestShape()
{

}