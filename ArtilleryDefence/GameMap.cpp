#include "stdafx.h"
#include "GameMap.h"
#include "ExtraTypes.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Camera.h"

CGameMap::CGameMap(std::string mapFile)
{
	float tileSide = 0.5;
	charStartX = 5;
	charStartY = 5;
	
	tileWidth = tileSide;
	tileHeight = tileSide;
	ReadMap(mapFile);
	mapWidth = tileSide*nTilesX;
	mapHeight = tileSide*nTilesY;
	/*
	mapTiles = std::vector<std::vector<CMapTile> >(nTilesX, std::vector<CMapTile>(nTilesY));
	for (int i = 0; i < nTilesX; i++){
		for (int j = 0; j < nTilesY; j++){
			mapTiles[i][j].posX=(i*tileWidth + tileWidth / 2.0);
			mapTiles[i][j].posY=(j*tileHeight + tileHeight / 2.0);
			if (j == 0){
				mapTiles[i][j].type = tiletype::flat;
			}
			else if (j == 1){
				mapTiles[i][j].type = tiletype::empty;
			}
			else{
				mapTiles[i][j].type = tiletype::empty;
			}
			if (5<i && i<20 && j<3)
				mapTiles[i][j].type = tiletype::flat;
			if (i == 0){
				mapTiles[i][j].type = tiletype::empty;
			}
		}
	}
	*/
}


CGameMap::~CGameMap()
{
}


void CGameMap::Draw(CCamera* cameraInst)
{
	for (std::vector<CSprite*>::iterator it = tileSprites.begin(); it != tileSprites.end(); it++){
		(*it)->SetWidthPix(cameraInst->WorldWidth2CameraWidth(GetTileWidth()));
		(*it)->SetHeightPix(cameraInst->WorldHeight2CameraHeight(GetTileHeight()));
	}
	for (int i = 0; i < nTilesX; i++){
		for (int j = 0; j < nTilesY; j++){
			if (mapTiles[i][j].type == tiletype::flat){
				tileSprites[0]->SetXPix(cameraInst->WorldX2CameraX(mapTiles[i][j].posX));
				tileSprites[0]->SetYPix(cameraInst->WorldY2CameraY(mapTiles[i][j].posY));
				tileSprites[0]->Draw();
			}
		}
	}
}

float CGameMap::GetTileWidth(){
	return tileWidth;
}
float CGameMap::GetTileHeight(){
	return tileHeight;
}

float CGameMap::GetMapWidth(){
	return mapWidth;
}
float CGameMap::GetMapHeight(){
	return mapHeight;
}

void CGameMap::SetSprites(CSprite* argSprite1, CSprite* argSprite2){
	tileSprites.push_back(argSprite1);
	tileSprites.push_back(argSprite2);
}

float CGameMap::GetCharStartX()
{
	return charStartX;
}


float CGameMap::GetCharStartY()
{
	return charStartX;
}


float CGameMap::CheckYCollition(float y, float xMin, float xMax, float yCheckDist)
{
	float yCollision = yCheckDist;
	int minColumn = std::max(0, std::min(nTilesX - 1, GetColumn(xMin)));
	int maxColumn = std::max(0, std::min(nTilesX - 1, GetColumn(xMax)));
	int currentRow = std::max(0, std::min(nTilesY - 1, GetRow(y)));
	int furthestCheckRow = std::max(0, std::min(nTilesY - 1, GetRow(y + yCheckDist)));
	for (int i = minColumn; i <= maxColumn; i++){
		if (yCheckDist <= 0){
			for (int j = currentRow-1; j >= furthestCheckRow; j = j--){
				if (mapTiles[i][j].type == tiletype::flat){
					yCollision = std::max((j+1)*tileHeight-y, yCollision);
					continue;
				}
			}
		}
		if (yCheckDist > 0){
			for (int j = currentRow+1; j <= furthestCheckRow; j = j++){
				if (mapTiles[i][j].type == tiletype::flat){
					yCollision = std::min(j*tileHeight-y, yCollision);
					continue;
				}
			}
		}
	}
	return yCollision;
}


float CGameMap::CheckXCollition(float x, float yMin, float yMax, float xCheckDist)
{
	//std::cout << GetColumn(x) << std::endl;
	float xCollision = xCheckDist;
	int minRow = std::max(0, std::min(nTilesY - 1,GetRow(yMin)));
	int maxRow = std::max(0, std::min(nTilesY - 1, GetRow(yMax)));
	int currentColumn = std::max(0, std::min(nTilesX - 1, GetColumn(x)));
	int furthestCheckColumn = std::max(0, std::min(nTilesX - 1, GetColumn(x + xCheckDist)));

	for (int i = minRow; i <= maxRow; i++){
		if (xCheckDist <= 0){
			for (int j = currentColumn-1; j >= furthestCheckColumn; j = j--){
				if (mapTiles[j][i].type == tiletype::flat){
					xCollision = std::max((j+1)*tileWidth-x, xCollision);
					continue;
				}
			}
		}
		if (xCheckDist > 0){
			for (int j = currentColumn+1; j <= furthestCheckColumn; j = j++){
				if (mapTiles[j][i].type == tiletype::flat){
					xCollision = std::min(j*tileWidth - x, xCollision);
					continue;
				}
			}
		}
	}
	return xCollision;
}




int CGameMap::GetColumn(float xPos)
{
	return int(xPos / tileWidth);
}

int CGameMap::GetRow(float yPos)
{
	//yRow = std::max(yRow, 0);
	//yRow = std::min(yRow, nTilesY - 1);
	return int(yPos / tileHeight);
}



void CGameMap::ReadMap(std::string argMapFilePath)
{
	std::string line;
	std::ifstream mapfile(argMapFilePath);
	int nLines = 0;
	while (std::getline(mapfile, line)){
		++nLines;
		nTilesX=line.size();
	}
	nTilesY = nLines;
	mapfile.close();
	mapTiles = std::vector<std::vector<CMapTile> >(nTilesX, std::vector<CMapTile>(nTilesY));

	mapfile.open(argMapFilePath.c_str(), std::ifstream::in);
	int j = nTilesY-1;
	while (std::getline(mapfile, line)){
		int i = 0;
		for (std::string::iterator it = line.begin(); it != line.end(); it++){
			mapTiles[i][j].posX = (i*tileWidth + tileWidth / 2.0);
			mapTiles[i][j].posY = (j*tileHeight + tileHeight / 2.0);
			if (*it=='0')
				mapTiles[i][j].type = tiletype::empty;
			if (*it== '1')
				mapTiles[i][j].type = tiletype::flat;
			i++;
		}
		j--;
	}
		
}