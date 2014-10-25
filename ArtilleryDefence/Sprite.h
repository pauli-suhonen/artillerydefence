#pragma once
#include <vector>
#include <string>
#include "GameTime.h"
#include  "SDL_Setup.h"

class CSprite
{
public:
	CSprite(SDL_Renderer* argRenderer, std::string argImagePath, int argWidthPix, int argHeightPix, int argXPix, int argYPix, int argNRow, int argNColumn, CGameTime* argGameTimeInst);
	~CSprite();
	void Draw();
	void CSprite::Animation(int);
	void SetAnimation(int row);
	void SetXPix(int);
	void SetYPix(int);
	void SetDirection(int);
	void SetSpriteDirLeft();
	void SetSpriteDirRight();
private:
	std::string imagePath;
	int widthPix;
	int heightPix;
	int xPix;
	int yPix;
	int nRow;
	int nColumn;
	CGameTime* gameTimeInst;
	int direction;

	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Rect crop;
	SDL_Renderer* renderer;
	int textureWidth;
	int textureHeight;
	int rendPosX;
	int rendPosY;
	SDL_RendererFlip flip;
	
	int animationRowCurrent;
	int animationRowNew;
	int animationColumnCurrent;
	int ellapsedFrameTime;
	int animationLoopTime;
	int animationFrameTime;
	CSDL_Setup* sdlSetup;
};

