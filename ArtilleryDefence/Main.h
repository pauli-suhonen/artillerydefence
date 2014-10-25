#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "UserInput.h"
#include "ObjectManager.h"
#include "GameTime.h"
#include "Character.h"
#include "Camera.h"
#include "GameMap.h"

class CMain
{
public:
	CMain();
	~CMain();
	int MenuLoop();
	int GameLoop();
	void HandleGeneralCmds(std::vector<generalcmd>*);
private:
	CSDL_Setup* sdlSetup;
	CUserInput* userInputInstance;
	bool quit;
	CCharacter* roboman;


	CSprite* background;
	CSprite* robomanSprite;
	CObjectManager * objectManagerInstance;
	CGameTime* gameTimeInst;
	CGameMap* gameMapInst;
	CCamera* cameraInst;
};

