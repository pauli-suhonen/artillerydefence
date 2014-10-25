#pragma once
class CCamera
{
public:
	CCamera(int argWindowWidth,int argWindowHeight,float argXMin,float argYMin,float argXMax,float argYMax);
	~CCamera();
	int WorldX2CameraX(float);
	int WorldY2CameraY(float);
	int WorldWidth2CameraWidth(float);
	int WorldHeight2CameraHeight(float);
private:
	int windowWidth;
	int windowHeight;
	float xMin;
	float yMin;
	float xMax;
	float yMax;
};

