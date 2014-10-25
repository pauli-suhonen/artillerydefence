#include "stdafx.h"
#include "GameTime.h"


CGameTime::CGameTime()
{
	timeDiff = 0;
	timeDiffS = 0;
	programTime = 0;
	programTimeS = 0;
	gameTime = 0;
	gameTimeS = 0;
}


CGameTime::~CGameTime()
{
}


void CGameTime::Update()
{
	unsigned int newprogramTime = SDL_GetTicks();
	timeDiff = newprogramTime - programTime;
	timeDiffS = (double)timeDiff / 1000.0;
	programTime = newprogramTime;
	programTimeS = (double)programTime / 1000.0;
	gameTime = programTime - gameStartTime;
	gameTimeS = (double)gameTime / 1000.0;
}

void CGameTime::SetGameStartTime(unsigned int newGameStartTime)
{
	gameStartTime = newGameStartTime;
}

unsigned int CGameTime::GetProgramTime()
{
	return programTime;
}

double CGameTime::GetProgramTimeS()
{
	return programTimeS;
}

unsigned int CGameTime::GetGameTime()
{
	return gameTime;
}
double CGameTime::GetGameTimeS()
{
	return gameTimeS;
}

unsigned int CGameTime::GetTimeDiff()
{
	return timeDiff;
}
double CGameTime::GetTimeDiffS()
{
	return timeDiffS;
}