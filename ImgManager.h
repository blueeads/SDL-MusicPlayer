#pragma once
#include "stdafx.h"

class Image {
private:
	SDL_Texture * imgTexture;
	SDL_Rect imgRect;

public:
	Image(SDL_Renderer* screen, const char* imgDir, int _x, int _y);
	~Image();
	void SetImgRect(int _x, int _y);
	void DrawImg(SDL_Renderer* screen);
	SDL_Rect GetImgRect();
	void Release();
};

