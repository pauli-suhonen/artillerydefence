#pragma once
#include "GameObject.h"


class CGameMap;
class CCamera
{
public:
	CCamera(int argWindowWidth,int argWindowHeight,float argXMin,float argYMin,float argXMax,float argYMax, CGameMap* argGameMap);
	~CCamera();
	int WorldX2CameraX(float);
	int WorldY2CameraY(float);
	int WorldWidth2CameraWidth(float);
	int WorldHeight2CameraHeight(float);
	void SetFollowedObject(CGameObject*);
	void SetFollow(bool);
	void Update();
	void ZoomIn(float zoomAmount);
	void ZoomOut(float zoomAmount);
private:
	int windowWidth;
	int windowHeight;
	float cameraWidth;
	float cameraHeight;
	float cameraXOffSet;
	float cameraYOffSet;
	float xMin;
	float yMin;
	float xMax;
	float yMax;
	double ratio;
	CGameObject* followedObject;
	bool follow;
	CGameMap* gameMap;
};

