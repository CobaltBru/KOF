#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "KOFKeyManager.h"
#include "TimerManager.h"
#include "ObjectManager.h"
/*
	�ǽ�1. �̿��� ���� ������
	�ǽ�2. ��� �ٲٱ� (ŷ���� �ִϸ��̼� ���)
*/

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	backBuffer = new Image();

	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);
	}

	iori = new KOF_Iori();
	iori->Init();

	timerManager = new TimerManager;
	if (objectManager = ObjectManager::GetInstance())
	{
		objectManager->Init();

		KOF_Iori* tempIori = new KOF_Iori;
		tempIori->Init();
		objectManager->AddObject(OBJID::OBJ_CHARACTER, tempIori);
	}
}

void MainGame::Release()
{
	if (iori)
	{
		iori->Release();
		delete iori;
		iori = nullptr;
	}

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	if (timerManager)
	{
		timerManager->Release();
		delete timerManager;
		timerManager = nullptr;
	}
	
	ReleaseDC(g_hWnd, hdc);

	if (KOFKeyManager* keyMgr = KOFKeyManager::GetInstance())
		keyMgr->Release();

	if (KeyManager* keyMgr = KeyManager::GetInstance())
		keyMgr->Release();

	if (objectManager)
		objectManager->Release();
}

void MainGame::Update()
{
	float TimeDelta = timerManager->GetTimeDelta(TEXT("Timer60"));
	
	/*if (iori)
		iori->Update(fTimeDelta);*/

	if (KOFKeyManager* keyMgr = KOFKeyManager::GetInstance())
		keyMgr->Update();

	if (objectManager)
		objectManager->Update(TimeDelta);

}

void MainGame::Render()
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backBuffer->Render(hdc);

	backGround->Render(hBackBufferDC);

	if (objectManager)
		objectManager->Render(hBackBufferDC);
}

float MainGame::GetTimeDelta(const wchar_t* pTimerTag)
{
	if (nullptr == timerManager)
		return 0.0f;

	return timerManager->GetTimeDelta(pTimerTag);
}

void MainGame::AddTimer(const wchar_t* pTimerTag)
{
	if (nullptr == timerManager)
		return;

	return timerManager->AddTimer(pTimerTag);
}

void MainGame::UpdateTimer(const wchar_t* pTimerTag)
{
	if (nullptr == timerManager)
		return;

	return timerManager->UpdateTimer(pTimerTag);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
