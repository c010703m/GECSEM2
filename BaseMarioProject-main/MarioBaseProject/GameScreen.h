#pragma once
#ifndef _GAMESCREEN.H
#define _GAMESCREEN.H

#include <SDL.h>

class GameScreen
{
protected:
	SDL_Renderer* renderer;

public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif //_GAMESCREEN.H