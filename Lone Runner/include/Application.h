#pragma once
#include <Windows.h>
#include <GL/GL.h>
#include "Window.h"
#include <SDL2\SDL_image.h>
/* This file contains all the basic stuff that 
are going to be implemented and used throughout the game*/
#ifndef APPLICATION
#define APPLICATION
class application_Exception : public std ::runtime_error
{ 
public:
	application_Exception(const std::string& error) : std::runtime_error(error) {};

};

class GameStateBase
{
public:
	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool Destroy() = 0;
};

class Application
{
	
	//The below part is done for our safety so only one instance of our game is running 
public:
	Application();
	bool Run(); //returns true while the application is running
	void Stop(); //allows our application to be stopped at any point of time 
	void SetState(GameStateBase *state);
	~Application();
private:
	bool active = true;//for the application is running or not(kind of GameLoop)
 	GameStateBase *state = nullptr;
	Window * window; // for the window

	 
};

class GameState : public GameStateBase
{
public:
	GameState(Application *app)
	{
		this->app = app;
	}
protected: 
	Application * app;
};

template<class StateClass>
void SetState(Application * app)
{
	app->SetState(new StateClass(app));
}
#endif