#include "stdafx.h"
#include "Main.h"
#include "SDL_Setup.h"
#include "Character.h"
#include "Sprite.h"
#include <vector>
#include <algorithm>
#include "UserInput.h"


CMain::CMain()
{
	quit = false;
	sdlSetup = new CSDL_Setup(1280, 720);
	userInputInstance = new CUserInput(sdlSetup);
	gameTimeInst = new CGameTime();



	gameMapInst = new CGameMap("data/map1.txt");
	cameraInst = new CCamera(sdlSetup->GetScreenWidth(), sdlSetup->GetScreenHeight(), 0, 0, 20, 20*720.0/1280.0,gameMapInst);
	CSprite* tileSprite1 = new CSprite(sdlSetup->GetRenderer(), "data/terrainTile1.png", cameraInst->WorldWidth2CameraWidth(gameMapInst->GetTileWidth()), cameraInst->WorldHeight2CameraHeight(gameMapInst->GetTileHeight()), 0, 0, 1, 1, gameTimeInst);
	CSprite* tileSprite2 = new CSprite(sdlSetup->GetRenderer(), "data/terrainTile2.png", cameraInst->WorldWidth2CameraWidth(gameMapInst->GetTileWidth()), cameraInst->WorldHeight2CameraHeight(gameMapInst->GetTileHeight()), 0, 0, 1, 1, gameTimeInst);
	gameMapInst->SetSprites(tileSprite1, tileSprite2);


	
	roboman = new CCharacter(gameMapInst->GetCharStartX(), gameMapInst->GetCharStartY(), 0, 0, gameTimeInst, gameMapInst, 1.99*16.0/80.0, 1.99);
	robomanSprite = new CSprite(sdlSetup->GetRenderer(), "data/Robomies_kaikki_sheet5.png", cameraInst->WorldWidth2CameraWidth((100.0 / 16.0)*roboman->GetWidth()), (150.0 / 80.0)*cameraInst->WorldHeight2CameraHeight(roboman->GetHeight()), cameraInst->WorldX2CameraX(roboman->GetPosX()), cameraInst->WorldY2CameraY(roboman->GetPosY() - roboman->GetHeight()), 5, 8, gameTimeInst);
	roboman->SetSprite(robomanSprite, (100.0 / 16.0), (150.0 / 80.0), cameraInst);
	cameraInst->SetFollowedObject(roboman);
	cameraInst->SetFollow(true);
	background = new CSprite(sdlSetup->GetRenderer(), "data/tausta.png", sdlSetup->GetScreenWidth(), sdlSetup->GetScreenHeight(), sdlSetup->GetScreenWidth() / 2, sdlSetup->GetScreenHeight()/2, 1, 1, gameTimeInst);
	objectManagerInstance = new CObjectManager();
	objectManagerInstance->AddGameObject(roboman);
}


CMain::~CMain()
{
	delete roboman;
	delete sdlSetup;
	delete userInputInstance;
	delete background;
	delete gameMapInst;
	delete cameraInst;
}

int CMain::MenuLoop()
{
	return 0;
}

void CMain::HandleGeneralCmds(std::vector<generalcmd>* generalCmds)
{
	//generalCmds->push_back(generalcmd::zoomin);
	for (std::vector<generalcmd>::iterator it = generalCmds->begin(); it != generalCmds->end(); it++){
		switch (*it)
		{
		case generalcmd::quitprogram:
			quit = true;
			break;
		case generalcmd::zoomin:
			cameraInst->ZoomIn(0.5);
			break;
		case generalcmd::zoomout:
			cameraInst->ZoomOut(0.5);
			break;
		default:
			break;
		}
	}
	generalCmds->clear();
}




int CMain::GameLoop()
{
	unsigned int lastTime = 0, currentTime = SDL_GetTicks();
	gameTimeInst->SetGameStartTime(SDL_GetTicks());
	userInputInstance->SetControlledUnit(roboman);
	while (!quit){
		userInputInstance->ParseGameInput();
		HandleGeneralCmds(userInputInstance->GetGeneralCommands());
		gameTimeInst->Update();
		objectManagerInstance->Update();
		cameraInst->Update();
		SDL_RenderClear(sdlSetup->GetRenderer());
		background->Draw();
		gameMapInst->Draw(cameraInst);
		roboman->Draw(cameraInst);
		SDL_RenderPresent(sdlSetup->GetRenderer());
	}
	return 0;
}