#pragma once
#include "Character.h"
#include "CharStates.h"


class CCharStateMachine
{
public:
	void Update();
	void ChangeState(CCharState* newState);
	CCharStateMachine(CCharacter* prmOwner, CGameTime* gameTimeInst);
	~CCharStateMachine();
	CIdleCS* GetIdleState();
	CInAirCS* GetInAirState();
	CWalkingCS* GetWalkingState();
	CJumpingCS* GetJumpingState();
	CShootingCS* GetShootingState();
	CTurningCS* GetTurningState();
private:
	CCharacter* owner;
	CCharState* currentState;
	CIdleCS* idleState;
	CInAirCS* inAirState;
	CWalkingCS* walkingState;
	CJumpingCS* jumpingState;
	CShootingCS* shootingState;
	CTurningCS* turningState;
};

