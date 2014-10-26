#include "stdafx.h"
#include "Camera.h"
#include "GameMap.h"

CCamera::CCamera(int argWindowWidth,int argWindowHeight,float argXMin,float argYMin,float argXMax,float argYMax,CGameMap* argGameMap)
	:windowWidth(argWindowWidth), windowHeight(argWindowHeight), xMin(argXMin), yMin(argYMin), xMax(argXMax), yMax(argYMax), gameMap(argGameMap)
{
	cameraWidth = argXMax - argXMin;
	cameraHeight = argYMax - argYMin;
	ratio = cameraHeight/cameraWidth;
	cameraXOffSet = (argXMax + argXMin)/2.0;
	cameraYOffSet = (argYMax + argYMin) / 2.0;
	followedObject=NULL;
	follow=false;
}


CCamera::~CCamera()
{
}

int CCamera::WorldX2CameraX(float argPosX)
{
	int cameraX=windowWidth*(argPosX-xMin)/(xMax-xMin);
	return cameraX;
}

int CCamera::WorldY2CameraY(float argPosY)
{
	int cameraY = windowHeight-windowHeight*(argPosY - yMin) / (yMax - yMin);
	//std::cout << cameraY << std::endl;
	return cameraY;
}

int CCamera::WorldWidth2CameraWidth(float width)
{
	return windowWidth*(width / (xMax - xMin));
}

int CCamera::WorldHeight2CameraHeight(float height)
{
	return windowHeight*(height / (yMax - yMin));
}

void CCamera::SetFollowedObject(CGameObject* argFollowedOgject)
{
	followedObject = argFollowedOgject;
}

void CCamera::SetFollow(bool argFollow)
{
	follow = argFollow;
}


void CCamera::Update()
{

	if (follow){
		cameraXOffSet = followedObject->GetPosX();
		cameraYOffSet = followedObject->GetPosY();
		//cameraYOffSet = 0;
		xMin = cameraXOffSet - cameraWidth / 2.0;
		xMax = cameraXOffSet + cameraWidth / 2.0;
		if (xMax > gameMap->GetMapWidth()){
			xMax = gameMap->GetMapWidth();
			xMin = gameMap->GetMapWidth() - cameraWidth;
		}
		if (xMin < 0){
			xMin = 0;
			xMax = cameraWidth;
		}

		yMin = cameraYOffSet - cameraHeight / 2.0;
		yMax = cameraYOffSet + cameraHeight / 2.0;
		if (yMax > gameMap->GetMapHeight()){
			yMax = gameMap->GetMapHeight();
			yMin = gameMap->GetMapHeight() - cameraHeight;
		}
		if (yMin < 0){
			yMin = 0;
			yMax = cameraHeight;
		}
	}


	int windowWidth;
	int windowHeight;
	float xMin;
	float yMin;
	float xMax;
	float yMax;
	CGameObject* followedObject;
	bool follow;
}

void CCamera::ZoomIn(float zoomAmount)
{
	cameraWidth = cameraWidth - zoomAmount;
	cameraHeight = cameraHeight - zoomAmount*ratio;
	float minWidthLimit = 5;
	if (cameraWidth < minWidthLimit){
		cameraWidth = minWidthLimit;
		cameraHeight = ratio*cameraWidth;
	}
}

void CCamera::ZoomOut(float zoomAmount)
{
	cameraWidth = cameraWidth + zoomAmount;
	cameraHeight = cameraHeight + zoomAmount*ratio;
	float maxWidthLimit = gameMap->GetMapWidth();
	if (cameraWidth > maxWidthLimit){
		cameraWidth = maxWidthLimit;
		cameraHeight = ratio*cameraWidth;
	}
}