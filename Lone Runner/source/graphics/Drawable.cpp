#include <Windows.h>
#include <GL\glew.h>
#include "graphics\Drawable.h"

Drawable::Drawable()
{
	this->vertexArrayObject = 0;
	this->vertexBufferObject = 0;
	this->elementBufferObject = 0;

	glGenVertexArrays(1, &this->vertexArrayObject);

}

void Drawable::loadVertices(float data[], size_t size)
{
	this->vertices.insert(this->vertices.end(), data, data + size);

	glGenBuffers(1, &this->vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
}
void Drawable::loadVertices(std::vector<float> data)
{
	this->vertices.insert(this->vertices.end(), data.begin(), data.end());

	glGenBuffers(1, &this->vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
	

}

void Drawable::loadElements(GLuint data[], size_t size)
{
	this->elements.insert(this->elements.end(), data, data + size);
	
	glGenBuffers(1, &this->elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)  * this->elements.size(), this->elements.data(), GL_STATIC_DRAW);

}void Drawable::loadElements(std::vector<unsigned int>)
{
	this->elements.insert(this->elements.end(), this->elements.begin(), this->elements.end());
	glGenBuffers(1, &this->elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(unsigned int) * this->elements.size()), (const void *) this->elements.data(), GL_STATIC_DRAW);

}
void Drawable::bindVAO()
{
	glBindVertexArray(this->vertexArrayObject);
}

void Drawable::unbindVAO()
{
	glBindVertexArray(0);
}


bool Drawable::Draw()
{
	if (!this->vertexArrayObject || !this->vertexBufferObject || !this->elementBufferObject) // if any one of those are 0 then we do not want to keep drawing
	{
		return false;
	}
	this->bindVAO(); // the buffers that we are using 
	glDrawElements(GL_TRIANGLES, this->elements.size(),	GL_UNSIGNED_INT, 0); // 0 is the offset of data depth, this is used to draw the elements
	this->unbindVAO();
	return true;
}

Drawable ::~Drawable()
{
	//elements are dependent on the vertices 
	if (this->elementBufferObject)
	{
		glDeleteBuffers(1, &this->elementBufferObject);
	}
	//vertices are dependant on the vertex array
	if (this->vertexBufferObject)
	{
		glDeleteBuffers(1, &this->vertexBufferObject);
	}
	if (this->vertexArrayObject)
	{// there is no need for this if check as we are creating one at the constructor 
		//the below line doesn't do anything if the buffer doesn't exist
		glDeleteVertexArrays(1, &this->vertexArrayObject);
	}
}