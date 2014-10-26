#include "stdafx.h"
#include "CharStates.h"
#include "GameTime.h"
#include "CharStateMachine.h"


CCharState::CCharState(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst):stateMachine(stateMachine), character(character), gameTimeInst(gameTimeInst)
{

}
CCharState::~CCharState()
{
}



/////////////////////
CIdleCS::CIdleCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst) :CCharState(stateMachine, character, gameTimeInst)
{
}
CIdleCS::~CIdleCS()
{
}
void CIdleCS::Execute()
{
//	if (character->GetCommands().empty())
//		stateMachine->ChangeState(stateMachine->GetIdleState());
	for (std::vector<charcmd>::const_iterator it = character->GetCommands().begin(); it != character->GetCommands().end(); it++){
		switch (*it)
		{
		case charcmd::moveleft:
			if (character->GetDirection() == 1){
				character->SetDirection(-1);
				stateMachine->ChangeState(stateMachine->GetTurningState());
			}else if (character->GetDirection() == -1){
				stateMachine->ChangeState(stateMachine->GetWalkingState());
			}
			break;
		case charcmd::moveright:
			if (character->GetDirection() == -1){
				character->SetDirection(1);
				stateMachine->ChangeState(stateMachine->GetTurningState());
			}else if (character->GetDirection() == 1){
				stateMachine->ChangeState(stateMachine->GetWalkingState());
			}
			break;
		case charcmd::jump:
			stateMachine->ChangeState(stateMachine->GetJumpingState());
			break;
		case charcmd::shoot:
			stateMachine->ChangeState(stateMachine->GetShootingState());
			break;
		case charcmd::crouch:
			break;
		default:
			break;
		}
	}
	character->UpdateInAir();
	if (character->GetInAir()==true)
		stateMachine->ChangeState(stateMachine->GetInAirState());
}
void CIdleCS::Enter()
{
	std::cout << "Entered Idle\n";
	character->SetVelY(0);
	character->SetVelX(0);
	character->GetSprite()->SetAnimation(0);
}
void CIdleCS::Exit()
{
}



/////////////////////////////
CInAirCS::CInAirCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst) :CCharState(stateMachine, character, gameTimeInst)
{
}
CInAirCS::~CInAirCS()
{
}
void CInAirCS::Execute()
{
	double g = 9.81;
	character->SetVelY(character->GetVelY() - gameTimeInst->GetTimeDiffS()*g);
	for (std::vector<charcmd>::const_iterator it = character->GetCommands().begin(); it != character->GetCommands().end(); it++){
		switch (*it)
		{
		case charcmd::moveleft:
			character->SetVelX(-character->GetWalkSpeed());
			break;
		case charcmd::moveright:
			character->SetVelX(character->GetWalkSpeed());
			break;
		default:
			break;
		}
	}
	character->Move();
	character->UpdateInAir();
	if (character->GetInAir()==false){
		stateMachine->ChangeState(stateMachine->GetIdleState());
	}
	
}
void CInAirCS::Enter()
{
	std::cout << "Entered In air\n";
	character->GetSprite()->SetAnimation(0);
}
void CInAirCS::Exit()
{
}



CWalkingCS::CWalkingCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst) :CCharState(stateMachine, character, gameTimeInst)
{
}
CWalkingCS::~CWalkingCS()
{

}
void CWalkingCS::Execute()
{
	if (character->GetCommands().empty())
		stateMachine->ChangeState(stateMachine->GetIdleState());
	for (std::vector<charcmd>::const_iterator it = character->GetCommands().begin(); it != character->GetCommands().end(); it++){
		switch (*it)
		{
		case charcmd::moveleft:
			if (character->GetDirection() == 1){
				character->SetDirection(-1);
				stateMachine->ChangeState(stateMachine->GetTurningState());
			}else if (character->GetDirection() == -1){
				stateMachine->ChangeState(stateMachine->GetWalkingState());
			}
			break;
		case charcmd::moveright:
			if (character->GetDirection() == -1){
				character->SetDirection(1);
				stateMachine->ChangeState(stateMachine->GetTurningState());
			}else if (character->GetDirection() == 1){
				stateMachine->ChangeState(stateMachine->GetWalkingState());
			}
			break;
		case charcmd::jump:
			stateMachine->ChangeState(stateMachine->GetJumpingState());
			break;
		case charcmd::shoot:
			stateMachine->ChangeState(stateMachine->GetShootingState());
			break;
		case charcmd::crouch:
			break;
		default:
			break;
		}
	}
	character->Move();
	character->UpdateInAir();
	if (character->GetInAir() == true)
		stateMachine->ChangeState(stateMachine->GetInAirState());
}
void CWalkingCS::Enter()
{
	std::cout << "Entered Walking\n";
	if (character->GetDirection() == 1){
		character->SetVelX(character->GetWalkSpeed());
	}
	if (character->GetDirection() == -1){
		character->SetVelX(-character->GetWalkSpeed());
		
	}
	character->GetSprite()->SetAnimation(1);
}
void CWalkingCS::Exit()
{
}






CTurningCS::CTurningCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst) :CCharState(stateMachine, character, gameTimeInst)
{
	
}
CTurningCS::~CTurningCS()
{

}
void CTurningCS::Execute()
{
	stateTime += gameTimeInst->GetTimeDiff();
	if (stateTime > 100){
		if (character->GetCommands().empty())
			stateMachine->ChangeState(stateMachine->GetIdleState());
		for (std::vector<charcmd>::const_iterator it = character->GetCommands().begin(); it != character->GetCommands().end(); it++){
			switch (*it)
			{
			case charcmd::moveleft:
				if (character->GetDirection() == 1){
					character->SetDirection(-1);
					stateMachine->ChangeState(stateMachine->GetTurningState());
				}
				else if (character->GetDirection() == -1){
					stateMachine->ChangeState(stateMachine->GetWalkingState());
				}
				break;
			case charcmd::moveright:
				if (character->GetDirection() == -1){
					character->SetDirection(1);
					stateMachine->ChangeState(stateMachine->GetTurningState());
				}
				else if (character->GetDirection() == 1){
					stateMachine->ChangeState(stateMachine->GetWalkingState());
				}
				break;
			case charcmd::jump:
				stateMachine->ChangeState(stateMachine->GetJumpingState());
				break;
			case charcmd::shoot:
				stateMachine->ChangeState(stateMachine->GetShootingState());
				break;
			case charcmd::crouch:
				break;
			default:
				break;
			}
		}
	}
}
void CTurningCS::Enter()
{
	stateTime = 0;
	character->GetSprite()->SetAnimation(4);
	character->SetVelY(0);
	character->SetVelX(0);
}
void CTurningCS::Exit()
{

}






CJumpingCS::CJumpingCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst) :CCharState(stateMachine, character, gameTimeInst)
{

}
CJumpingCS::~CJumpingCS()
{

}
void CJumpingCS::Execute()
{
	character->Move();
	stateTime += gameTimeInst->GetTimeDiff();
	for (std::vector<charcmd>::const_iterator it = character->GetCommands().begin(); it != character->GetCommands().end(); it++){
		switch (*it)
		{
		case charcmd::moveleft:
			character->SetVelX(-character->GetWalkSpeed());
			break;
		case charcmd::moveright:
			character->SetVelX(character->GetWalkSpeed());
			break;
		default:
			break;
		}
	}
	if (stateTime > 200){
		character->SetVelY(character->GetJumpVel());
		stateMachine->ChangeState(stateMachine->GetInAirState());
	}
}
void CJumpingCS::Enter()
{
	stateTime = 0;
	character->GetSprite()->SetAnimation(3);
}
void CJumpingCS::Exit()
{

}

CShootingCS::CShootingCS(CCharStateMachine* stateMachine, CCharacter* character, CGameTime* gameTimeInst) :CCharState(stateMachine, character, gameTimeInst)
{

}
CShootingCS::~CShootingCS()
{

}
void CShootingCS::Execute()
{
	for (std::vector<charcmd>::const_iterator it = character->GetCommands().begin(); it != character->GetCommands().end(); it++){
		switch (*it)
		{
		case charcmd::release:
			stateMachine->ChangeState(stateMachine->GetIdleState());
			break;
		default:
			break;
		}
	}
}
void CShootingCS::Enter()
{
	character->SetVelY(0);
	character->SetVelX(0);
	character->GetSprite()->SetAnimation(2);
}
void CShootingCS::Exit()
{

}




