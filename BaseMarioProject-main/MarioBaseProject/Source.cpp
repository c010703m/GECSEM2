//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"

#include <iostream>

using namespace std;

//Globals
SDL_Window* g_window = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[])
{
	//check if sdl was setup correctly
	if (InitSDL())
	{
		//Flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			quit = Update();
		}
	}
	CloseSDL();
	return 0;
}

bool InitSDL()
{
//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise, Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window has not been created, Error: " << SDL_GetError();
			return false;
		}
	}
}

void CloseSDL()
{
	//release the window 
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//Handle the events
	switch (e.type)
	{
			//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}
	return false;
}