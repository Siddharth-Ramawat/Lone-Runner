#include "states\TestState.h"
#include "states\TestState2.h"
#include "Application.h"

TestState::TestState(Application *app) : GameState(app)
{
}

bool TestState::Init()
{

	glClearColor(0, 1, 0, 0);
	this->shader = new Shader("Resources/test_shader.vert", "Resources/test_shader.frag");
	this->shader->Use();

	this->testShape = new TestShape(this->shader);
	this->room = new RoomCube(this->shader);
	this->camera = new Camera(this->shader, 800, 600);
	
	this->camera->setTranslation(0, 0, 2); // anything less than 1 won't be visible so we need to move our camera backwards
	this->camVelocity = glm::vec3(0.1f, 0.1f, 0.1f);
	SDL_WarpMouseGlobal(500, 500);
	SDL_ShowCursor(0);
	return true;
}

bool TestState::Destroy()
{
	return true;
}

bool TestState::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->room->Draw();

	this->testShape->Draw();
	this->camera->Update();
	
	const uint8_t *state = SDL_GetKeyboardState(NULL);
	const float MOUSE_SPEED = 0.05f;
	SDL_WarpMouseGlobal(500, 500);

	int xPos, yPos;
	Uint32 mouseState = SDL_GetGlobalMouseState(&xPos, &yPos);
	
	
	this->camRotation.y += MOUSE_SPEED * float(500 - xPos);
	this->camRotation.x += MOUSE_SPEED * float(500 - yPos);


	if (state[SDL_SCANCODE_A])
	{
		this->camera->Translate(
			-this->camVelocity.x * cos(glm::radians(-this->camRotation.y)),
			0,
			-this->camVelocity.z * sin(glm::radians(-this->camRotation.y)));
	}
	if (state[SDL_SCANCODE_D])
	{
		this->camera->Translate(
			this->camVelocity.x * cos(glm::radians(-this->camRotation.y)),
			0,
			this->camVelocity.z * sin(glm::radians(-this->camRotation.y)));
	}
	if (state[SDL_SCANCODE_S])
	{
		this->camera->Translate(
			this->camVelocity.x * sin(glm::radians(this->camRotation.y)),
			0,
			this->camVelocity.z * cos(glm::radians(this->camRotation.y)));
	}
	if (state[SDL_SCANCODE_W])
	{
		this->camera->Translate(
			-this->camVelocity.x * sin(glm::radians(this->camRotation.y)),
			0,
			-this->camVelocity.z * cos(glm::radians(this->camRotation.y)));
	}
	
	

	if(state[SDL_SCANCODE_SPACE])
	{
		SetState<TestState2>(this->app);
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		this->camRotation.y += 1; //rotates around y axis
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		this->camRotation.y -= 1; //rotates around y axis
	}
	if (state[SDL_SCANCODE_UP])
	{
		this->camRotation.x += 1; //rotates around x axis
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		this->camRotation.x -= 1; //rotates around x axis
	}
	this->camera->setRotaion(0, 1, 1, 1);
	this->camera->Rotate(camRotation.x, 1, 0, 0);
	this->camera->Rotate(camRotation.y, 0, 1, 0);
	
	if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		SetState<TestState2>(this->app);
	}

	
	return true;
}


TestState::~TestState()
{
	delete this->shader;
}


