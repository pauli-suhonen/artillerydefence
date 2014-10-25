#pragma once
#include "GameTime.h"

class CCharacter;
class CCharStateMachine;

class CCharState
{
public:
	CCharState(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst);
	~CCharState();
	virtual void Execute()=0;
	virtual void Enter()=0;
	virtual void Exit()=0;
protected:
	CCharStateMachine* stateMachine;
	CCharacter* character;
	CGameTime* gameTimeInst;
	float stateTime;
};

class CIdleCS :public CCharState
{
public:
	CIdleCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst);
	~CIdleCS();
	virtual void Execute();
	virtual void Enter();
	virtual void Exit();
};

class CInAirCS :public CCharState
{
public:
	CInAirCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst);
	~CInAirCS();
	virtual void Execute();
	virtual void Enter();
	virtual void Exit();
};

class CWalkingCS :public CCharState
{
public:
	CWalkingCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst);
	~CWalkingCS();
	virtual void Execute();
	virtual void Enter();
	virtual void Exit();
};

class CJumpingCS :public CCharState
{
public:
	CJumpingCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst);
	~CJumpingCS();
	virtual void Execute();
	virtual void Enter();
	virtual void Exit();
};

class CShootingCS :public CCharState
{
public:
	CShootingCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst);
	~CShootingCS();
	virtual void Execute();
	virtual void Enter();
	virtual void Exit();
};

class CTurningCS :public CCharState
{
public:
	CTurningCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst);
	~CTurningCS();
	virtual void Execute();
	virtual void Enter();
	virtual void Exit();
};