#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "TimerManager.h"
#include "KOFKeyManager.h"
#include "UserInterface.h"
#include "ObjectManager.h"
#include "HongCharacter.h"
#include "CollisionManager.h"
#include "Ryo.h"
/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	backBuffer = new Image();

	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}

	timerManager = TimerManager::GetInstance();
	if (objectManager = ObjectManager::GetInstance())
	{
		objectManager->Init();

	/*	KOF_Iori* tempIori = new KOF_Iori;
		tempIori->Init();
		objectManager->AddObject(OBJID::OBJ_CHARACTER, tempIori);*/

	/*	HongCharacter* tempHong = new HongCharacter;
		tempHong->Init();
		tempHong->SetPos({ 100.f, 100.f });
		objectManager->AddObject(OBJID::OBJ_CHARACTER, tempHong);*/

		Ryo* tempRyo = new Ryo();
		vector<Image> tempImage;
		Image Idle;
		Idle.Init(L"Image/Ryo/Ryo_Idle.bmp", 840, 109, 7, 1, true, RGB(255, 0, 255));

		Image Walk;
		Walk.Init(L"Image/Ryo/Ryo_Walk1.bmp", 720, 109, 6, 1, true, RGB(255, 0, 255));

		Image BackWalk;
		BackWalk.Init(L"Image/Ryo/Ryo_BackWalk.bmp", 720, 109, 6, 1, true, RGB(255, 0, 255));

		Image Down;
		Down.Init(L"Image/Ryo/Ryo_DownUp.bmp", 600, 109, 5, 1, true, RGB(255, 0, 255));

		Image Dash;
		Dash.Init(L"Image/Ryo/Ryo_Walk1.bmp", 720, 109, 6, 1, true, RGB(255, 0, 255));

		Image Back;
		Back.Init(L"Image/Ryo/Ryo_Walk1.bmp", 720, 109, 6, 1, true, RGB(255, 0, 255));
		//idle, 뒷걷기, 앞걷기, 숙이기, 앞대쉬, 백대쉬 순으로 넣어주세요
		tempImage.push_back(Idle);
		tempImage.push_back(BackWalk);
		tempImage.push_back(Walk);
		tempImage.push_back(Down);
		tempImage.push_back(Dash);
		tempImage.push_back(Back);

		tempRyo->Init(1, new Image(),{250,250},200.f,100.f, tempImage);

		Image* tempAttack1 = new Image();
		tempAttack1->Init(L"Image/Ryo/Ryo_Attack1.bmp", 840, 109, 7, 1, true, RGB(255, 0, 255));

		tempRyo->pushSkill("Y", tempAttack1, 7, 5, 10, true, false, 2, 3, 0, 0);
		objectManager->AddObject(OBJID::OBJ_CHARACTER, tempRyo);
	}

	UI = new UserInterface();
	UI->Init();

	if (collisionManager = CollisionManager::GetInstance())
	{
		collisionManager->Init();
	}
}

void MainGame::Release()
{
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
		timerManager->Release();
	
	ReleaseDC(g_hWnd, hdc);
	if (UI)
	{
		UI->Release();
		delete UI;
		UI = nullptr;
	}

	if (KOFKeyManager* kofKeyMgr = KOFKeyManager::GetInstance())
		kofKeyMgr->Release();

	if (KeyManager* keyMgr = KeyManager::GetInstance())
		keyMgr->Release();

	if (objectManager)
		objectManager->Release();

	if (collisionManager)
		collisionManager->Release();
}

void MainGame::Update()
{
	float TimeDelta = timerManager->GetTimeDelta(TEXT("Timer60"));
	
	if (KOFKeyManager* kofKeyMgr = KOFKeyManager::GetInstance())
		kofKeyMgr->Update(TimeDelta);

	if (objectManager)
		objectManager->Update(TimeDelta);

	UI->Update();

	if (collisionManager)
		collisionManager->Update(TimeDelta);

}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backBuffer->Render(hdc);

	backGround->Render(hBackBufferDC);

	if(UI)
		UI->Render(hBackBufferDC);

	if (objectManager)
		objectManager->Render(hBackBufferDC);
	
#ifdef _DEBUG
	if (collisionManager)
		collisionManager->Render(hBackBufferDC);
#endif
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
