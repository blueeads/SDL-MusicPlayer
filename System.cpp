#include "stdafx.h"
SoundManager* A;
enum state
{
	MAIN,
	GAME,
	CREDIT
}Stage;

CSystem::CSystem(void)
{
	
}

CSystem::~CSystem(void)
{

}

bool CSystem::Initialize()
{
	CBaseWindow::Initialize();
	CTimeManager::Initialize();

	m_pGameFrame = new CFrameSkip;
	m_pGameFrame->SetFramePerSec(60);

	m_pInputManager = new CInputManager;
	m_pInputManager->SetInputHandler(this);

	imgSurface = SDL_LoadBMP("./Image/Sence/Ingame.bmp"); //�ΰ��� �̹���
	imgGame = SDL_CreateTextureFromSurface(m_pRender, imgSurface);
	SDL_FreeSurface(imgSurface);

	imgSurface = SDL_LoadBMP("./Image/Sence/Main.bmp"); //���� �̹���
	imgBg = SDL_CreateTextureFromSurface(m_pRender, imgSurface);

	imgSurface = SDL_LoadBMP("./Image/Sence/Main_Down.bmp"); //ũ������ ����Ǵ� ��ο� ���
	imgDarkBg = SDL_CreateTextureFromSurface(m_pRender, imgSurface);

	//Image(m_pRender, "./Image/Sence/ads", 100, 200);

	char strTemp[2][256] = { IMG_DIR, IMG_DIR };
	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "arrowleft-up.bmp");
	strcat(strTemp[1], "arrowleft-down.bmp");
	btnLeft = InitButton(m_pRender, strTemp[0], strTemp[1], 300, 350, ArrowLeft); //�ΰ���

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "arrowright-up.bmp");
	strcat(strTemp[1], "arrowright-down.bmp");
	btnRight = InitButton(m_pRender, strTemp[0], strTemp[1], 220, 150, ArrowRight); //����

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "arrowup-up.bmp");
	strcat(strTemp[1], "arrowup-down.bmp");
	btnUp = InitButton(m_pRender, strTemp[0], strTemp[1], 190, 80, ArrowUp);

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "arrowdown-up.bmp");
	strcat(strTemp[1], "arrowdown-down.bmp");
	btnDown = InitButton(m_pRender, strTemp[0], strTemp[1], 1150, 30, ArrowDown); //How to

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "arrowdown-up.bmp");
	strcat(strTemp[1], "arrowdown-down.bmp");
	btnExit = InitButton(m_pRender, strTemp[0], strTemp[1], 300, 550, ArrowExit); //��������

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "Credit_Button1.BMP");
	strcat(strTemp[1], "Credit_Button2.BMP");
	btnCredit1 = InitButton(m_pRender, strTemp[0], strTemp[1], 300, 400, ArrowCredit1); //ũ����

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "Credit.bmp");
	strcat(strTemp[1], "Credit.bmp");
	btnCredit2 = InitButton(m_pRender, strTemp[0], strTemp[1], 100, 100, ArrowCredit2); //ũ���� ����

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "Credit_Button1.BMP");
	strcat(strTemp[1], "Credit_Button2.BMP");
	btnMusic_Start = InitButton(m_pRender, strTemp[0], strTemp[1], 1150, 40, Music1_Play); //���� 1 ��ŸƮ

	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "Credit_Button1.BMP");
	strcat(strTemp[1], "Credit_Button2.BMP");
	btnMusic_Stop = InitButton(m_pRender, strTemp[0], strTemp[1], 500, 40, Music1_Stop); //���� 1 ��ž

	//������Ʈ �ʱ�ȭ
	strcpy(strTemp[0], IMG_DIR);
	strcpy(strTemp[1], IMG_DIR);
	strcat(strTemp[0], "Credit_Button1.BMP");
	strcat(strTemp[1], "Credit_Button2.BMP");
	btnCrExit = InitButton(m_pRender, strTemp[0], strTemp[1], 800, 100, CrExit);

	A->AddSong("Night.mp3");

	return true;
}

void CSystem::Pulse()
{
	CTimeManager::Pulse();
	m_pInputManager->Pulse();

	float fTimeStep = CTimeManager::GetTimeStep();

	if (m_pGameFrame->Update(fTimeStep))
	{
		//SDL_SetRenderDrawColor(m_pRender, MIN8, MIN8, MAX8, MAX8);
		SDL_RenderClear(m_pRender);

		if (Stage == MAIN) //���������� �����϶�
		{
			SDL_RenderCopy(m_pRender, imgBg, NULL, NULL);

			Draw(m_pRender, btnLeft);
			Draw(m_pRender, btnExit);
			Draw(m_pRender, btnCredit1);
			Draw(m_pRender, btnDown);
		}
		if (Stage == GAME) //�ΰ����϶�
		{
			SDL_RenderCopy(m_pRender, imgGame, NULL, NULL);

			Draw(m_pRender, btnRight);
			Draw(m_pRender, btnMusic_Start);
			Draw(m_pRender, btnMusic_Stop);
		}
		if (Stage == CREDIT) // ũ����ȭ��
		{
			SDL_RenderCopy(m_pRender, imgDarkBg, NULL, NULL);

			Draw(m_pRender, btnCredit2);
			Draw(m_pRender, btnCrExit);
		}
	}
	SDL_RenderPresent(m_pRender);
}

void CSystem::Terminate()
{
	//������Ʈ ����

	m_pInputManager->Terminate();

	Release(btnLeft);
	Release(btnRight);
	Release(btnUp);
	Release(btnDown);
	Release(btnExit);
	Release(btnCredit1);
	Release(btnCredit2);
	Release(btnMusic_Start);
	Release(btnMusic_Stop);
	Release(btnCrExit);
	SDL_DestroyTexture(imgGame);

	CBaseWindow::Terminate();
	CTimeManager::Terminate();
}

void CSystem::Run()
{
	while (m_bIsGameRun)
	{
		Pulse(); //Update()
	}
}

#define g_pKeyCodeScan(vk) (m_pInputManager->GetOldKeyState(vk)&&m_pInputManager->GetCurKeyState(vk))

void CSystem::KeyboardHandler() //Ű���� �Է�
{
	/*if (g_pKeyCodeScan(SDL_SCANCODE_1))
	m_nIsDrawingState = DrawingState::POINTS;
	*/
}

void CSystem::MouseHandler(MOUSESTATE mouseState) // ���콺 �Է�
{
	if (mouseState.btn[MOUSE_BUTTON::LEFT])
	{
		if (Stage == MAIN) //���������� �����϶� ���콺 �Է��� �޴´�
		{
			MouseUp(btnLeft, mouseState.x, mouseState.y);
			MouseUp(btnExit, mouseState.x, mouseState.y);
			MouseUp(btnCredit1, mouseState.x, mouseState.y);
		}
		if (Stage == GAME) //���������� �����϶� ���콺 �Է��� �޴´�
		{
			/*MouseUp(btnUp, mouseState.x, mouseState.y);
			MouseUp(btnDown, mouseState.x, mouseState.y);*/
			MouseUp(btnRight, mouseState.x, mouseState.y);
			MouseUp(btnMusic_Start, mouseState.x, mouseState.y);
			MouseUp(btnMusic_Stop, mouseState.x, mouseState.y);
		}
		if (Stage == CREDIT) //���������� ũ�����϶� ���콺 �Է��� �޴´�
		{
			MouseUp(btnCrExit, mouseState.x, mouseState.y);
		}
	}
	if (mouseState.btn[MOUSE_BUTTON::RIGHT])
	{
		if (Stage == MAIN)
		{
			MouseDown(btnLeft, mouseState.x, mouseState.y);
			MouseDown(btnExit, mouseState.x, mouseState.y);
			MouseDown(btnCredit1, mouseState.x, mouseState.y);
		}
		if (Stage == GAME)
		{
			//MouseDown(btnUp, mouseState.x, mouseState.y);
			//MouseDown(btnDown, mouseState.x, mouseState.y);
			MouseDown(btnRight, mouseState.x, mouseState.y);
			MouseDown(btnMusic_Stop, mouseState.x, mouseState.y);
		}
		if (Stage == CREDIT)
		{
			MouseDown(btnCrExit, mouseState.x, mouseState.y);
		}
	}
}

void ArrowDown()
{
}

void ArrowUp()
{
}

void ArrowLeft()
{
	Stage = GAME;
}

void ArrowRight()
{
	Stage = MAIN;
}

void MusicUp()
{
}

void MusicDown()
{
}

void ArrowExit()
{
	SDL_Quit();
}

void ArrowCredit1()
{
	Stage = CREDIT;
}

void ArrowCredit2()
{
	Stage = MAIN;
}

void Music1_Play()
{
	mciSendString("play IU - Rain Drop.mp3", NULL, 0, NULL);
}

void Music1_Stop()
{
	mciSendString("pause Intro.mp3", NULL, 0, NULL);
}

void CrExit()
{
	Stage = MAIN;
}

