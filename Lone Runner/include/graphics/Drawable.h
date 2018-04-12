#pragma once

#ifndef DRAWABLE
#define DRAWABLE
#include <vector>
#include <iterator>
#include <iostream>
class Drawable {
public:
	Drawable();
	bool Draw();
	~Drawable();
private:
	GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
	std::vector<GLuint> elements;
	std::vector<float> vertices;

protected:
	void loadVertices(float data[], size_t size);
	void loadVertices(std::vector<float> data);

	void loadElements(GLuint data[], size_t size);
	void loadElements(std::vector<GLuint> data);

	void bindVAO();
	void unbindVAO();

};

#endif