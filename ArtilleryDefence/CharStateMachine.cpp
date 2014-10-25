#include "stdafx.h"
#include "CharStateMachine.h"


CCharStateMachine::CCharStateMachine(CCharacter* prmOwner, CGameTime* gameTimeInst)
{
	owner = prmOwner;
	idleState = new CIdleCS(this, owner, gameTimeInst);
	inAirState = new CInAirCS(this, owner, gameTimeInst);
	walkingState = new CWalkingCS(this, owner, gameTimeInst);
	jumpingState = new CJumpingCS(this, owner, gameTimeInst);
	shootingState = new CShootingCS(this, owner, gameTimeInst);
	turningState = new CTurningCS(this, owner, gameTimeInst);
	currentState = idleState;
}


CCharStateMachine::~CCharStateMachine()
{
	delete idleState;
	delete inAirState;
	delete walkingState;
	delete jumpingState;
	delete shootingState;
}

void CCharStateMachine::Update()
{
	currentState->Execute();
}

void CCharStateMachine::ChangeState(CCharState* newState)
{
	currentState->Exit();
	currentState = newState;
	currentState->Enter();
}
CIdleCS* CCharStateMachine::GetIdleState()
{
	return idleState;
}
CInAirCS* CCharStateMachine::GetInAirState()
{
	return inAirState;
}
CWalkingCS* CCharStateMachine::GetWalkingState()
{
	return walkingState;
}
CJumpingCS* CCharStateMachine::GetJumpingState()
{
	return jumpingState;
}
CShootingCS* CCharStateMachine::GetShootingState()
{
	return shootingState;
}

CTurningCS* CCharStateMachine::GetTurningState()
{
	return turningState;
}