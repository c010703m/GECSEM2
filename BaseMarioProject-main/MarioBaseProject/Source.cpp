//Be grateful for humble beginnings, because the next level will always require so much more of you

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"

#include <iostream>

using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);


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
			Render();
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

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer != nullptr)
	{
			//init PNG loading
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image could not be initialise. Error: " << IMG_GetError();
			return false;
		}
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}

	//Load the background texture
	g_texture = new Texture2D(g_renderer);

	if (!g_texture ->LoadFromFile("Images / test.bmp"))
	{
		return false;
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

	//Release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//release the texture
	delete g_texture;
	g_texture = nullptr;
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
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return true;
			break;
		}
		break;
	}
	return false;
}

void Render()
{
	//Clear the screen
	SDL_GetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);

	g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);
}





