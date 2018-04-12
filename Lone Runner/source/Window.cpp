#include "Window.h"

Window::Window(const std::string& title, int x, int y, int width, int height)
{
	this->sdlWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_FLAGS);
	if (this->sdlWindow == nullptr)
	{
		throw window_Exception(SDL_GetError());
	}
	else
	{
		this->InitRenderer();
	}
}

Window::Window(const std::string& title, int width, int height)
{
	this->sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FLAGS);
	if (this->sdlWindow == nullptr)
	{
		throw window_Exception(SDL_GetError());
	}
	else
	{
		this->InitRenderer();
	}
}

Window ::~Window()
{
	SDL_GL_DeleteContext(this->sdlGLContext);
	SDL_DestroyWindow(this->sdlWindow);// To destory the window
}

//function to create a renderer
void Window::InitRenderer()
{
	this->sdlGLContext = SDL_GL_CreateContext(this->sdlWindow);
	if (this->sdlGLContext == nullptr)
	{
		throw gl_context_Exception(SDL_GetError());
	}
	else
	{
		if(SDL_GL_SetSwapInterval(1) < 0)
			throw gl_context_Exception(SDL_GetError());
		else
		{ 
			SDL_UpdateWindowSurface(this->sdlWindow);
		}
	}
}

void Window::Update()
{
	SDL_GL_SwapWindow(this->sdlWindow);
}