#pragma once
#include <vector>
#include "GameTime.h"


class CGameMap;
class CGameObject
{
public:
	CGameObject(float, float, float, float, CGameTime*, CGameMap* argGameMapInst);
	~CGameObject();
	virtual void Update();
	float GetPosX();
	float GetPosY();
	float GetVelX();
	float GetVelY();
	void SetPosX(float);
	void SetPosY(float);
	void SetVelX(float);
	void SetVelY(float);
	CGameTime * GetGameTimeInst();
	virtual float CGameObject::GetRendXAdjust();
	virtual float CGameObject::GetRendYAdjust();
	virtual float CGameObject::GetRendRotAdjust();
	void SetMap(CGameMap* argGameMap);
protected:
	bool inAir;
	float posX;
	float velX;
	float posY;
	float velY;
	CGameTime *gameTimeInst;
	CGameMap* gameMap;
private:
};

