#include "stdafx.h"
#include "GameObject.h"
#include "GameTime.h"
#include "GameMap.h"

CGameObject::CGameObject(float argPosX, float argPosY, float argVelX, float argVelY,CGameTime* argGameTimeInst, CGameMap* argGameMapInst)
{
	posX = argPosX;
	posY = argPosY;
	velX = argVelX;
	velY = argVelY;
	gameTimeInst = argGameTimeInst;
	gameMap = argGameMapInst;
}

void CGameObject::Update()
{
}

CGameObject::~CGameObject()
{
}

float CGameObject::GetPosX()
{
	return posX;
}

float CGameObject::GetVelX()
{
	return velX;
}
float CGameObject::GetPosY()
{
	return posY;
}

float CGameObject::GetVelY()
{
	return velY;
}


void CGameObject::SetPosX(float newPosX)
{
	posX = newPosX;
}
void CGameObject::SetPosY(float newPosY)
{
	posY = newPosY;
}


void CGameObject::SetVelX(float newVelX)
{
	velX = newVelX;
}

void CGameObject::SetVelY(float newVelY)
{
	velY = newVelY;
}

CGameTime * CGameObject::GetGameTimeInst()
{
	return gameTimeInst;
}

float CGameObject::GetRendXAdjust()
{
	return -0.5;
}

float CGameObject::GetRendYAdjust()
{
	return 1.0;
}

float CGameObject::GetRendRotAdjust()
{
	return 0;
}

void CGameObject::SetMap(CGameMap* argGameMap)
{
	gameMap = argGameMap;
}
