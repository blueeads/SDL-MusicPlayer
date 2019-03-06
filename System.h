#include "stdafx.h"
#define IMG_DIR		"./Image/Button/"
#define MUCIS_DIR	"./Image/Music/"


class CSystem : public CBaseWindow,
	public CTimeManager,
	public IInputHandler
{
private:
	/*enum DrawingState{ POINTS = 0, LINES, BOXES, END };
	int m_nIsDrawingState = POINTS;*/

private:
	CFrameSkip * m_pGameFrame;
	CInputManager*	m_pInputManager;

public:
	CSystem(void);
	~CSystem(void);

private:
	void Pulse();

public:
	bool Initialize();
	void Terminate();
	void Run();

public:
	void KeyboardHandler();
	void MouseHandler(MOUSESTATE mouseState);

private:
	bool bIsGameRun = true;

public:
	SDL_Surface* imgSurface;
	SDL_Texture* imgBg;
	SDL_Texture* imgGame;
	SDL_Texture* imgDarkBg;

public:
	BUTTON* btnLeft;
	BUTTON* btnRight;
	BUTTON* btnUp;
	BUTTON* btnDown;
	BUTTON* btnExit;
	BUTTON* btnCredit1;
	BUTTON* btnCredit2;
	BUTTON* btnMusic_Start;
	BUTTON* btnMusic_Stop;
	BUTTON* btnCrExit;
};
