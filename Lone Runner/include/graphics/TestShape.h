#pragma once

#ifndef TESTSHAPE
#define TESTSHAPE
#include "graphics\Drawable.h"
#include "graphics\Shader.h" //some data will be passed from the shader to the shape

class TestShape : public Drawable //piublicly extends Drawable
{
public:
	TestShape(Shader * shader);
	~TestShape();

private:
	GLint positionAttribute, colorAttribute;
};
#endif
