#pragma once
class CSDL_Setup
{


public:
	CSDL_Setup(int screenWidth,int screenHeight);
	~CSDL_Setup();
	SDL_Event* GetMainEvent();
	SDL_Renderer* CSDL_Setup::GetRenderer();
	SDL_Window* CSDL_Setup::GetMainWindow();
	int GetScreenWidth();
	int GetScreenHeight();
private:
	SDL_Event* mainEvent;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int screenHeight;
	int screenWidth;
};

