#pragma once
#include <vector>
#include "Sprite.h"
#include "Camera.h"
#include "MapTile.h"
#include "ExtraTypes.h"

class CGameMap
{
public:
	CGameMap(std::string mapFile);
	~CGameMap();
	float GetTileWidth();
	float GetTileHeight();
	float GetMapWidth();
	float GetMapHeight();
	void SetSprites(CSprite* sprite1, CSprite* sprite2);
	void Draw(CCamera* cameraInst);
	float GetCharStartX();
	float GetCharStartY();
	float CheckYCollition(float yPos, float xMin, float xMax, float yCheckDist);
	float CheckXCollition(float xPos, float yMin, float yMax, float xCheckDist);
	void ReadMap(std::string mapFile);
	int GetColumn(float);
	int GetRow(float);
private:
	std::vector<CSprite*> tileSprites;
	std::vector<std::vector<CMapTile> > mapTiles;
	int nTilesX;
	int nTilesY;
	float mapWidth;
	float mapHeight;
	float tileWidth;
	float tileHeight;
	float charStartX;
	float charStartY;
};

