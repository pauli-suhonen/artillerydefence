#pragma once
#include<vector>
#include "SDL_Setup.h"
#include "ExtraTypes.h"
#include "Character.h"

class CUserInput
{
public:
	CUserInput(CSDL_Setup* sdlSetup, CCharacter* controlledUnit);
	CUserInput(CSDL_Setup* sdlSetup);
	~CUserInput();
	void ParseMenuInput();
	void ParseGameInput();
	std::vector<generalcmd>* GetGeneralCommands();
	void SetControlledUnit(CCharacter* controlledUnit);
private:
	CSDL_Setup* sdlSetup;
	std::vector<generalcmd>* parsedGeneralCmds;
	CCharacter* controlledUnit;
};

