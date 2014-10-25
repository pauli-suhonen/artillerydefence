#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"


CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
}

void CObjectManager::AddGameObject(CGameObject* newGameObject)
{
	objectVector.push_back(newGameObject);
}

void CObjectManager::Update()
{
	for (std::vector<CGameObject*>::iterator it = objectVector.begin(); it != objectVector.end(); it++){
		(*it)->Update();
		//std::cout << (*it)->GetPosX() << "\t" << (*it)->GetPosY()<<std::endl;
	}
}