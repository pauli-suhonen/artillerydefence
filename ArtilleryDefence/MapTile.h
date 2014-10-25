#pragma once
#include "ExtraTypes.h"
#include "Camera.h"
#include "Sprite.h"

class CMapTile
{
public:
	CMapTile();
	~CMapTile();
	float posX;
	float posY;
	float hitBoxXMin;
	float hitBoxXMax;
	float hitBoxYMin;
	float hitBoxYMax;
	tiletype type;
};

