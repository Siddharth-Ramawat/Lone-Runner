#pragma once
#include "Application.h"
#include "graphics\\TestShape.h"
#include "graphics\RoomCube.h"
#include "graphics\Shader.h"
#include "graphics\Camera.h" 
class TestState :
	public GameState
{
public:
	TestState(Application *app);
	bool Init();
	bool Update();
	bool Destroy();
	~TestState();
private:
	Shader * shader;
	TestShape *testShape;
	RoomCube *room;
	Camera *camera;
	glm::vec3 camRotation;
	glm::vec3 camVelocity;
};

