#pragma once
class CGameTime
{
	
public:
	void Update();
	void SetGameStartTime(unsigned int newGameStartTime);
	unsigned int GetProgramTime();
	double GetProgramTimeS();
	unsigned int GetGameTime();
	double GetGameTimeS();
	unsigned int GetTimeDiff();
	double GetTimeDiffS();
	CGameTime();
	~CGameTime();
private:
	unsigned int gameStartTime;
	unsigned int programTime;
	double programTimeS;
	unsigned int gameTime;
	double gameTimeS;
	unsigned int timeDiff;
	double timeDiffS;
};

