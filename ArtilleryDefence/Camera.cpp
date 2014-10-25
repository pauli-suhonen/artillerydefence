#include "stdafx.h"
#include "Camera.h"


CCamera::CCamera(int argWindowWidth,int argWindowHeight,float argXMin,float argYMin,float argXMax,float argYMax)
	:windowWidth(argWindowWidth),windowHeight(argWindowHeight),xMin(argXMin),yMin(argYMin),xMax(argXMax),yMax(argYMax)
{
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