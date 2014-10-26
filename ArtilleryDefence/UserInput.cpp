#include "stdafx.h"
#include "UserInput.h"


CUserInput::CUserInput(CSDL_Setup* sdlSetup, CCharacter* controlledUnit) :sdlSetup(sdlSetup), controlledUnit(controlledUnit)
{
	parsedGeneralCmds = new std::vector < generalcmd >;
}

CUserInput::CUserInput(CSDL_Setup* sdlSetup) : sdlSetup(sdlSetup)
{
	parsedGeneralCmds = new std::vector < generalcmd >;
}

CUserInput::~CUserInput()
{
	delete parsedGeneralCmds;
}

void CUserInput::ParseGameInput()
{
	controlledUnit->ClearCommands();
	std::vector<charcmd> parsedCharCmds;

	while (SDL_PollEvent(sdlSetup->GetMainEvent())){
		switch (sdlSetup->GetMainEvent()->type){
		case SDL_QUIT:
			parsedGeneralCmds->push_back(generalcmd::quitprogram);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (sdlSetup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
				parsedCharCmds.push_back(charcmd::shoot);
		break;
		case SDL_MOUSEBUTTONUP:
			if (sdlSetup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
				parsedCharCmds.push_back(charcmd::release);
			break;
		case SDL_MOUSEWHEEL:
			std::cout << sdlSetup->GetMainEvent()->wheel.y << std::endl;
			if (sdlSetup->GetMainEvent()->wheel.y > 0)
				parsedGeneralCmds->push_back(generalcmd::zoomin);
			if (sdlSetup->GetMainEvent()->wheel.y < 0)
				parsedGeneralCmds->push_back(generalcmd::zoomout);
			break;
		}
	}


	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A]) 
		parsedCharCmds.push_back(charcmd::moveleft);
	if (state[SDL_SCANCODE_D])
		parsedCharCmds.push_back(charcmd::moveright);
	if (state[SDL_SCANCODE_W])
		parsedCharCmds.push_back(charcmd::jump);
	if (state[SDL_SCANCODE_S])
		parsedCharCmds.push_back(charcmd::crouch);

	

	controlledUnit->AddCommands(parsedCharCmds);

}


std::vector<generalcmd>* CUserInput::GetGeneralCommands(){

	return parsedGeneralCmds;
}

void CUserInput::SetControlledUnit(CCharacter* newControlledUnit)
{
	controlledUnit = newControlledUnit;
}
