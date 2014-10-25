#pragma once
#include "GameObject.h"
#include <vector>
class CObjectManager
{
public:
	CObjectManager();
	~CObjectManager();
	void Update();
	void CObjectManager::AddGameObject(CGameObject* newObject);
private:
	std::vector<CGameObject*> objectVector;
};

