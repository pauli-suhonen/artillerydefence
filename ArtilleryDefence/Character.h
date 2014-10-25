#pragma once
#include "GameObject.h"
#include <vector>
#include "Sprite.h"
#include "SDL_Setup.h"
#include "ExtraTypes.h"
#include "Camera.h"

class CCharStateMachine;

class CCharacter: public CGameObject
{
public:
	CCharacter::CCharacter(float argPosX, float argPosY, float argVelX, float argVelY, CGameTime* argGameTimeInst, CGameMap* argGameMapInst, double argWidth, double argHeight);
	~CCharacter();
	void Draw(CCamera* cameraInst);
	void Update();
	void SetDirection(int);
	int GetDirection();
	float GetWalkSpeed();
	float GetJumpVel();
	CCharStateMachine* GetStateMachine();
	void AddCommands(std::vector<charcmd>);
	void ClearCommands();
	const std::vector<charcmd>& GetCommands();
	CSprite* GetSprite();
	void SetSprite(CSprite*);
	float GetWidth();
	float GetHeight();
	void Move();
	float GetHitBoxMinY();
	float GetHitBoxMaxY();
	float GetHitBoxMinX();
	float GetHitBoxMaxX();
	void UpdateInAir();
	bool GetInAir();
private:
	int direction;
	CSprite* sprite;
	float hitBoxWidth;
	float hitBoxHeight;
	float charSpeed;
	float walkSpeed;
	float jumpVel;
	bool inAir;
	std::vector<charcmd> commands;

	CCharStateMachine* stateMachine;

	CSDL_Setup* sdlSetup;
};

