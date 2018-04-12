#pragma once
#include <SDL2\SDL.h>
#include <iostream>
#include <exception>
#ifndef WINDOW
#define WINDOW


//the below lines describes the basic flags for windows and renderers
#define SDL_WINDOW_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
#define SDL_RENDERER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

//ACCELERATED is for hardware accelaration, VSYNC is to prevent tearing
class window_Exception : public std::runtime_error
{
public:
	window_Exception(const std::string& error) : std::runtime_error(error) {};
};

class gl_context_Exception : public std::runtime_error
{
public:
	gl_context_Exception(const std::string& error) : std::runtime_error(error) {};
};
class Window
{
public:
	Window(const std::string& title, int width, int height);
	Window(const std::string& title, int x, int y, int width, int height);
	void Update();
	~Window();
private:
	void InitRenderer();
	SDL_Window * sdlWindow;
	SDL_GLContext sdlGLContext;
};

#endif // !WINDOW