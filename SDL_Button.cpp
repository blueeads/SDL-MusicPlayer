#include "stdafx.h"
#include "SDL_Button.h"

BUTTON* InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, int x, int y, void(*f)(void))
{
	BUTTON* Temp;

	Temp = (BUTTON*)malloc(sizeof(BUTTON));

	SDL_Surface* imgTemp;

	imgTemp = SDL_LoadBMP(szUp);
	Uint32 colorkey = SDL_MapRGB(imgTemp->format, 255, 0, 255); //»ö±ò Å° °ª
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //»ö±ò Å° °ª ¼³Á¤
	Temp->imgUp = SDL_CreateTextureFromSurface(screen, imgTemp);
	SDL_FreeSurface(imgTemp);

	imgTemp = SDL_LoadBMP(szDown);
	SDL_SetColorKey(imgTemp, SDL_TRUE, colorkey); //»ö±ò Å° °ª ¼³Á¤
	Temp->imgDown = SDL_CreateTextureFromSurface(screen, imgTemp);
	Temp->imgCurrent = Temp->imgUp;

	Temp->rtClip.x = x;
	Temp->rtClip.y = y;
	Temp->rtClip.w = imgTemp->w;
	Temp->rtClip.h = imgTemp->h;

	SetCoord(Temp, x, y);
	SetVisible(Temp, true);


	Temp->func = f;

	return Temp;
}

void Release(BUTTON* pBtn)
{
	if (pBtn == NULL) return;

	if (pBtn->imgUp != 0)	SDL_DestroyTexture(pBtn->imgUp);
	if (pBtn->imgDown != 0)	SDL_DestroyTexture(pBtn->imgDown);

	free(pBtn);
}

void Draw(SDL_Renderer* screen, BUTTON* pBtn)
{
	if (!pBtn->bIsVisible) return;

	SDL_RenderCopy(screen, pBtn->imgCurrent, NULL, &pBtn->rtClip);
}

BUTTON::eButtonState GetState(BUTTON* pBtn)
{
	if (pBtn->imgCurrent == pBtn->imgDown)
		return BUTTON::eButtonState::BUTTONDOWN;
	else
		return BUTTON::eButtonState::BUTTONUP;
}

void ClickDown(BUTTON* pBtn)
{
	pBtn->imgCurrent = pBtn->imgDown;
}

void ClickUp(BUTTON* pBtn)
{
	pBtn->imgCurrent = pBtn->imgUp;
	if (pBtn->func != 0)
	{
		pBtn->func();
	}
}

bool IsOver(BUTTON* pBtn, int px, int py)
{
	if ((px >= pBtn->nX) && (px < (pBtn->nX + pBtn->rtClip.w)))
	{
		if ((py >= pBtn->nY) && (py < (pBtn->nY + pBtn->rtClip.h)))
		{
			return true;
		}
	}
	return false;
}

void Toggle(BUTTON* pBtn)
{
	if (pBtn->imgCurrent == pBtn->imgUp)
		pBtn->imgCurrent = pBtn->imgDown;
	else
		pBtn->imgCurrent = pBtn->imgUp;
}

void ResetOnUp(BUTTON* pBtn)
{
	pBtn->imgCurrent = pBtn->imgUp;
}

void SetCoord(BUTTON* pBtn, int x, int y)
{
	pBtn->nX = x;
	pBtn->nY = y;
}

void SetVisible(BUTTON* pBtn, bool visible)
{
	pBtn->bIsVisible = visible;
}

bool IsVisible(BUTTON* pBtn)
{
	return pBtn->bIsVisible;
}

void MouseDown(BUTTON* pBtn, int px, int py)
{
	if (IsOver(pBtn, px, py) && IsVisible(pBtn))
	{
		ClickDown(pBtn);
	}
}

void MouseUp(BUTTON* pBtn, int px, int py)
{
	if (IsOver(pBtn, px, py) && IsVisible(pBtn))
	{
		ClickUp(pBtn);
		ResetOnUp(pBtn);
	}
}

