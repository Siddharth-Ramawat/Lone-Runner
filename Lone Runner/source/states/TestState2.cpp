#include "states\TestState.h"
#include "states\TestState2.h"

TestState2::TestState2(Application *app) : GameState(app)
{
}

bool TestState2::Init()
{

	glClearColor(0, 0, 1, 1);

	return true;
}

bool TestState2::Destroy()
{
	return true;
}

bool TestState2::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const uint8_t *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT ])
	{
		SetState<TestState>(this->app);
	}
	return true;
}

TestState2::~TestState2()
{
}
