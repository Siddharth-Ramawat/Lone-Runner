#pragma once

#ifndef ROOMCUBE
#define ROOMCUBE
#include "graphics\Drawable.h"
#include "graphics\Shader.h" //some data will be passed from the shader to the shape

class RoomCube : public Drawable //piublicly extends Drawable
{
public:
	RoomCube(Shader * shader);
	~RoomCube();

private:
	GLint positionAttribute, colorAttribute;
};
#endif
