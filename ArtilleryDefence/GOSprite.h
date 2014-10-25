#pragma once
#include "Sprite.h"
#include "GameObject.h"

class CGOSprite: public CSprite
{
public:
	CGOSprite();
	~CGOSprite();
private:
	CGameObject* owner;
};

