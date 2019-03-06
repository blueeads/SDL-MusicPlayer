#pragma once
#include "stdafx.h"

typedef struct M_BUTTON
{
	enum eButtonState { BUTTONDOWN, BUTTONUP };

	SDL_Texture* imgUp;
	SDL_Texture* imgDown;
	SDL_Texture* imgCurrent;

	SDL_Rect rtClip;

	int nX, nY;

	bool bIsVisible = true;

	void(*func)(void);
}BUTTON;

BUTTON* InitButton(SDL_Renderer* screen, const char* szUp, const char* szDown, int x, int y, void(*f)(void)); //초기화
void Release(BUTTON* pBtn); //메모리해제
void Draw(SDL_Renderer* screen, BUTTON* pBtn); //그리기

BUTTON::eButtonState GetState(BUTTON* pBtn); //버튼상태
void ClickDown(BUTTON* pBtn);
void ClickUp(BUTTON* pBtn);

bool IsOver(BUTTON* pBtn, int px, int py); //좌표 위에있나
void Toggle(BUTTON* pBtn); //반대
void ResetOnUp(BUTTON* pBtn); //up상태
void SetCoord(BUTTON* btn, int x, int y); //좌표바꾸기
void SetVisible(BUTTON* btn, bool visible); //셋팅
bool IsVisible(BUTTON* btn); //물어보는거

void MouseDown(BUTTON* pBtn, int px, int py);
void MouseUp(BUTTON* pBtn, int px, int py);

void ArrowUp();
void ArrowDown();
void ArrowLeft();
void ArrowRight();
void MusicUp();
void MusicDown();
void ArrowExit();
void ArrowCredit1();
void ArrowCredit2();
void CrExit();
void Music1_Play();
void Music1_Stop();
