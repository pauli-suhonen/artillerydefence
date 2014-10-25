#include "stdafx.h"
#include "Character.h"
#include "GameObject.h"
#include "SDL_Setup.h"
#include "GameTime.h"
#include "CharStateMachine.h"


//SDL_FLIP_NONE
//SDL_FLIP_HORIZONTAL
//SDL_FLIP_HORIZONTAL

CCharacter::CCharacter(float argPosX, float argPosY, float argVelX, float argVelY, CGameTime* argGameTimeInst, CGameMap* argGameMapInst, double argWidth, double argHeight)
	:CGameObject(argPosX, argPosY, argVelX, argVelY, argGameTimeInst, argGameMapInst), hitBoxWidth(argWidth), hitBoxHeight(argHeight)
{
	direction = 1;
	sprite = NULL; 
	charSpeed = 8;//Not Usain
	walkSpeed = 1.4;//Definately not Usain
	walkSpeed = 2.0;//Definately not Usain
	//walkSpeed = 140;//Definately not Usain
	jumpVel = 8;
	direction = 1;
	stateMachine = new CCharStateMachine(this,gameTimeInst);
	inAir=true;
}


CCharacter::~CCharacter()
{
	delete sprite;
	delete stateMachine;
}



void CCharacter::SetDirection(int newDirection)
{
	direction = newDirection;
	if (direction == -1)
		sprite->SetSpriteDirLeft();
	if (direction == 1)
		sprite->SetSpriteDirRight();
}

int CCharacter::GetDirection()
{
	return direction;
}




void CCharacter::Update()
{
	stateMachine->Update();
}

void CCharacter::Draw(CCamera* cameraInst)
{
	sprite->SetXPix(cameraInst->WorldX2CameraX(posX));
	sprite->SetYPix(cameraInst->WorldY2CameraY(posY));
	sprite->SetDirection(direction);
	sprite->Draw();
}

void CCharacter::AddCommands(std::vector<charcmd> newCommands)
{
	for (std::vector<charcmd>::iterator it = newCommands.begin(); it != newCommands.end(); it++)
		commands.push_back(*it);
}

void CCharacter::ClearCommands()
{
	commands.clear();
}

const std::vector<charcmd>& CCharacter::GetCommands()
{
	return commands;
}

CSprite* CCharacter::GetSprite()
{
	return sprite;
}

CCharStateMachine* CCharacter::GetStateMachine()
{
	return stateMachine;
}

float CCharacter::GetWalkSpeed()
{
	return walkSpeed;
}

float CCharacter::GetJumpVel()
{
	return jumpVel;
}

void CCharacter::SetSprite(CSprite* argSprite)
{
	sprite = argSprite;
}

float CCharacter::GetWidth()
{
	return hitBoxWidth;
}

float CCharacter::GetHeight()
{
	return hitBoxHeight;
}

/*
void CCharacter::Move()
{
//	std::cout << inAir << std::endl;
	float hitBoxPosMinX = posX - hitBoxWidth / 2.0;
	float hitBoxPosMaxX = posX + hitBoxWidth / 2.0;
	float hitBoxPosMinY = posY - hitBoxHeight / 2.0;
	float hitBoxPosMaxY = posY + hitBoxHeight / 2.0;


	float attemptPosX = posX + velX*gameTimeInst->GetTimeDiffS();
	float attemptHitBoxPosMinX = attemptPosX - hitBoxWidth / 2.0;
	float attemptHitBoxPosMaxX = attemptPosX + hitBoxWidth / 2.0;
	

	float allowedPosX=posX;
	if (attemptPosX < posX){
		float attemptHitBoxPosX = attemptHitBoxPosMinX;
		float hitBoxPosX = hitBoxPosMinX;
		float allowedHitBoxPosX = gameMap->GetAllowedXMove(hitBoxPosMinY, hitBoxPosMaxY, hitBoxPosX, attemptHitBoxPosX);
		allowedPosX = allowedHitBoxPosX + hitBoxWidth / 2.0;
	}
	if (attemptPosX > posX){
		float attemptHitBoxPosX = attemptHitBoxPosMaxX;
		float hitBoxPosX = hitBoxPosMaxX;
		float allowedHitBoxPosX = gameMap->GetAllowedXMove(hitBoxPosMinY, hitBoxPosMaxY, hitBoxPosX, attemptHitBoxPosX);
		allowedPosX = allowedHitBoxPosX - hitBoxWidth / 2.0;
	}
	posX = allowedPosX;




	float attemptPosY = posY + velY*gameTimeInst->GetTimeDiffS();
	float attemptHitBoxPosMinY = attemptPosY - hitBoxHeight / 2.0;
	float attemptHitBoxPosMaxY = attemptPosY + hitBoxHeight / 2.0;

	float allowedPosY = posY;
	if (attemptPosY < posY){
		float attemptHitBoxPosY = attemptHitBoxPosMinY;
		float hitBoxPosY = hitBoxPosMinY;
		bool hit;
		float allowedHitBoxPosY = gameMap->GetAllowedYMove(hitBoxPosMinX, hitBoxPosMaxX, hitBoxPosY, attemptHitBoxPosY,hit);
		std::cout << gameTimeInst->GetTimeDiffS() << std::endl;
		if (hit)
			inAir = false;
		allowedPosY = allowedHitBoxPosY + hitBoxHeight / 2.0;
	}
	if (attemptPosY > posY){
		float attemptHitBoxPosY = attemptHitBoxPosMaxY;
		float hitBoxPosY = hitBoxPosMaxY;
		bool hit;
		float allowedHitBoxPosY = gameMap->GetAllowedYMove(hitBoxPosMinX, hitBoxPosMaxX, hitBoxPosY, attemptHitBoxPosY, hit);
		allowedPosY = allowedHitBoxPosY - hitBoxHeight / 2.0;
	}



	posY = allowedPosY;
}

*/


float CCharacter::GetHitBoxMinY()
{
	return posY - hitBoxHeight / 2.0;
}

float CCharacter::GetHitBoxMaxY()
{
	return posY + hitBoxHeight / 2.0;
}

float CCharacter::GetHitBoxMinX()
{
	return posX - hitBoxWidth / 2.0;
}

float CCharacter::GetHitBoxMaxX()
{
	return posX + hitBoxWidth / 2.0;
}




void CCharacter::Move()
{
	float xDisplacement = velX*gameTimeInst->GetTimeDiffS();
	if (velX > 0){
		float xCollisionDist = gameMap->CheckXCollition(GetHitBoxMaxX(), GetHitBoxMinY(), GetHitBoxMaxY(), 1.1*xDisplacement);
		if (xCollisionDist >= xDisplacement)
			posX += xDisplacement;
		else{
			posX += xCollisionDist - 0.001;
			//velX = 0;
		}
	}
	if (velX < 0){
		float xCollisionDist = gameMap->CheckXCollition(GetHitBoxMinX(), GetHitBoxMinY(), GetHitBoxMaxY(), 1.1*xDisplacement);
		//std::cout << xDisplacement <<"\t"<< xCollisionDist << std::endl;
		if (xCollisionDist <= xDisplacement)
			posX += xDisplacement;
		else{
			posX += xCollisionDist + 0.001;
			//velX = 0;
		}
	}
	


	float yDisplacement = velY*gameTimeInst->GetTimeDiffS();
	if (velY > 0){
		float yCollisionDist = gameMap->CheckYCollition(GetHitBoxMaxY(), GetHitBoxMinX(), GetHitBoxMaxX(), 1.1*yDisplacement);
		if (yCollisionDist >= yDisplacement)
			posY += yDisplacement;
		else{
			posY += yCollisionDist - 0.001;
			velY = 0;
		}
	}
	if (velY < 0){
		float yCollisionDist = gameMap->CheckYCollition(GetHitBoxMinY(), GetHitBoxMinX(), GetHitBoxMaxX(), 1.1*yDisplacement);
		if (yCollisionDist <= yDisplacement)
			posY += yDisplacement;
		else{
			posY += yCollisionDist + 0.001;
			velY = 0;
			inAir = false;
		}
	}
}


bool CCharacter::GetInAir()
{
	return inAir;
}

void CCharacter::UpdateInAir()
{
	float drop=gameMap->CheckYCollition(GetHitBoxMinY(), GetHitBoxMinX(), GetHitBoxMaxX(), -0.02);
	if (drop < -0.01)
		inAir=true;
	else
		inAir=false;
}