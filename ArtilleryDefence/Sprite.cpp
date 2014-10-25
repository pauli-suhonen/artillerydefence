#include "stdafx.h"
#include "Sprite.h"
#include <string>
#include "GameTime.h"

CSprite::CSprite(SDL_Renderer* argRenderer, std::string argImagePath, int argWidthPix, int argHeightPix, int argXPix, int argYPix, int argNRow, int argNColumn, CGameTime* argGameTimeInst)
	:renderer(argRenderer), imagePath(argImagePath), widthPix(argWidthPix), heightPix(argHeightPix), xPix(argXPix), yPix(argYPix), nRow(argNRow), nColumn(argNColumn), gameTimeInst(argGameTimeInst)
{
	SDL_Surface *surf = IMG_Load(imagePath.c_str());
	if (surf == NULL){
		std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	if (texture == NULL){
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
	}
	direction=1;
	animationRowNew = 0;
	animationLoopTime = 1000;
	animationFrameTime = animationLoopTime / nColumn;

	rect.x = xPix;
	rect.y = yPix;
	rect.w = widthPix;
	rect.h = heightPix;

	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	crop.x = 0;
	crop.y = 0;
	crop.w = textureWidth/nColumn;
	crop.h = textureHeight/nRow;

	flip = SDL_FLIP_NONE;
}


CSprite::~CSprite()
{
}

void CSprite::Draw()
{
		//rect.x = sdlSetup->GetRendPosX(owner->GetPosX() + owner->GetRendXAdjust());
		//rect.y = sdlSetup->GetRendPosY(owner->GetPosY() + owner->GetRendYAdjust());
	rect.x = xPix-widthPix/2;
	rect.y = yPix-heightPix/2;
	//std::cout << heightPix << std::endl;
	//std::cout << widthPix << std::endl;
	//std::cout << xPix << "\t" << yPix << std::endl;
	Animation(animationRowNew);
	//SDL_FLIP_NONE
	//SDL_FLIP_HORIZONTAL
	//SDL_FLIP_HORIZONTAL
	SDL_RenderCopyEx(renderer, texture, &crop, &rect, 0.0, NULL,flip );
}

void CSprite::SetSpriteDirLeft()
{
	flip = SDL_FLIP_HORIZONTAL;
}

void CSprite::SetSpriteDirRight()
{
	
	flip = SDL_FLIP_NONE;
}


void CSprite::SetAnimation(int row)
{
	animationRowNew = row;
}


void CSprite::Animation(int animationRow)
{
	//std::cout << animationRowNew << std::endl;
	if (animationRowNew == animationRowCurrent){
		ellapsedFrameTime += gameTimeInst->GetTimeDiff();
		while (ellapsedFrameTime > animationFrameTime){
			//std::cout << "WOOOOOOOOOOOO!\n";
			animationColumnCurrent = (animationColumnCurrent + 1) % nColumn;
			ellapsedFrameTime -= animationFrameTime;
		}
	}
	else{
		//std::cout << "EEEEEEEEEEEEEEEEEE!\n";
		animationColumnCurrent = 0;
		animationRowCurrent = animationRowNew;
		ellapsedFrameTime = 0;
	}
	crop.x = animationColumnCurrent*crop.w;
	//std::cout <<"e"<< crop.x << "\n";
	crop.y = animationRowCurrent*crop.h;
	animationRowNew = animationRowCurrent;
}

void CSprite::SetXPix(int argXPix)
{
	xPix=argXPix;
}
void CSprite::SetYPix(int argYPix)
{
	yPix=argYPix;
}
void CSprite::SetDirection(int argDirection)
{
	direction=argDirection;
}