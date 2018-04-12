#include <GL/glew.h>
#include "Application.h"

#include <SDL2/SDL.h>
 Application ::Application()
{
	  try{
		  //If an exception occurs we need to handle it
		  //Else we can go through with our application execution.
		 if (SDL_Init(SDL_INIT_EVERYTHING))
		 {
			 throw application_Exception(SDL_GetError());
		 }
		 else
		 {
			 this->window = new Window("SDL First", 800, 600);//This creates a centered window
			 if (glewInit() != GLEW_OK)
			 {
				 std::cout << "Error initializing GLEW!" << std::endl;
			 }
			 else
			 {
				 glEnable(GL_DEPTH_TEST);
			 }
		 }
		 if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
		 {
			 throw application_Exception(SDL_GetError());
		 }
	 }
	  catch (application_Exception& exception)
	  {
		  std::cout << "Application Error: ";
#ifdef _DEBUG
		  std::cout << "Line 18 in Application.cpp : ";	
#endif // DEBUG

		  std ::cout << exception.what() << std::endl;// Describes the exception
	  }
	  catch (window_Exception& exception)
	  {
		  std::cout << "Window Error: ";
#ifdef _DEBUG
		  std::cout << "Line 05 in Window.cpp : ";
#endif // DEBUG

		  std::cout << exception.what() << std::endl;
	  }
	  catch (gl_context_Exception& exception)
	  {
		  std::cout << "GL_context Error: ";
#ifdef _DEBUG
		  std::cout << "in Window.cpp : ";
#endif // DEBUG

		  std::cout << exception.what() << std::endl;
	  }
}

bool Application::Run()
{
	//If we have an active application we need events to navigate through the window
	if (this->active)
	{
		SDL_Event event;
		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: this->Stop();
				break;
			case SDL_KEYDOWN: 
				switch (event.key.keysym.sym)
				{
				
				case SDLK_ESCAPE: this->Stop();
				default:
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				case SDL_BUTTON_RIGHT:
				default:
					break;
				}
			default: SDL_Delay(10);
				break;
			}
		}
		if(this->state != nullptr && this->state->Update())
			this->window->Update();
	}
	return this->active;  
}

void Application::Stop()
{
	this->active = false; // makes the active state false to close the application
}


void Application :: SetState(GameStateBase* state)
{
	if (this->state != nullptr)
	{
		this->state->Destroy();//destroy the state if it has been created 
		delete this->state;
	}
	this->state = state;
	this->state->Init();
}

Application::~Application()
{
	if (this->state != nullptr)
	{
		this->state->Destroy();//destroy the state if it has been created 
		delete this->state;
	}
	SDL_Quit();//To quit the application at the end 
}