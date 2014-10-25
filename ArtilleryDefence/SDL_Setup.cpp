#include "stdafx.h"
#include "SDL_Setup.h"


CSDL_Setup::CSDL_Setup(int screenWidth, int screenHeight) :screenWidth(screenWidth), screenHeight(screenHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
		//return 1;
	}

	mainEvent = new SDL_Event();

	 window = NULL;
	window = SDL_CreateWindow("ArtilleryDefence", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		//return 1;
	}
	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL){
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		//return 1;
	}
}


CSDL_Setup::~CSDL_Setup()
{
	delete mainEvent;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Event* CSDL_Setup::GetMainEvent()
{
	return mainEvent;
}

SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Window* CSDL_Setup::GetMainWindow()
{
	return window;
}

int  CSDL_Setup::GetScreenWidth()
{
	return screenWidth;
}

int  CSDL_Setup::GetScreenHeight()
{
	return screenHeight;
}