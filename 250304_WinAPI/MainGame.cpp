#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TimerManager.h"
#include "KOFKeyManager.h"
#include "UserInterface.h"
#include "ObjectManager.h"
#include "HongCharacter.h"
#include "CollisionManager.h"
#include "Ryo.h"
#include "Mai.h"
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

	UI = new UserInterface();
	UI->Init();

	timerManager = TimerManager::GetInstance();
	if (objectManager = ObjectManager::GetInstance())
	{
		objectManager->Init();

#pragma once region TaeKyung

		Ryo* tempRyo = new Ryo();
		{
			vector<Image> tempImage;

			Image* maiProfile = new Image();
			maiProfile->Init(TEXT("Image/UI/yuri.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255));

			Image Idle;
			Idle.Init(L"Image/Ryo/Ryo_Idle.bmp", 840, 130, 7, 1, true, RGB(255, 0, 255));

			Image Walk;
			Walk.Init(L"Image/Ryo/Ryo_Walk1.bmp", 720, 130, 6, 1, true, RGB(255, 0, 255));

			Image BackWalk;
			BackWalk.Init(L"Image/Ryo/Ryo_BackWalk.bmp", 720, 130, 6, 1, true, RGB(255, 0, 255));

			Image Down;
			Down.Init(L"Image/Ryo/Ryo_Down.bmp", 120, 130, 1, 1, true, RGB(255, 0, 255));

			Image Dash;
			Dash.Init(L"Image/Ryo/Ryo_Dash.bmp", 720, 130, 6, 1, true, RGB(255, 0, 255));

			Image Back;
			Back.Init(L"Image/Ryo/Ryo_BackDash1.bmp", 120, 130, 1, 1, true, RGB(255, 0, 255));
			//idle, 뒷걷기, 앞걷기, 숙이기, 앞대쉬, 백대쉬 순으로 넣어주세요
			tempImage.push_back(Idle);
			tempImage.push_back(BackWalk);
			tempImage.push_back(Walk);
			tempImage.push_back(Down);
			tempImage.push_back(Dash);
			tempImage.push_back(Back);

			tempRyo->Init(1, maiProfile, { 250,200 }, 200.f, 100.f, tempImage);

			Image* ryoLightPunch = new Image();
			ryoLightPunch->Init(L"Image/Ryo/Ryo_LightPunch.bmp", 840, 130, 7, 1, true, RGB(255, 0, 255));

			Image* ryoStrongPunch = new Image();
			ryoStrongPunch->Init(L"Image/Ryo/Ryo_StrongPunch.bmp", 1080, 130, 9, 1, true, RGB(255, 0, 255));

			Image* ryoLightKick = new Image();
			ryoLightKick->Init(L"Image/Ryo/Ryo_LightKick.bmp", 840, 130, 7, 1, true, RGB(255, 0, 255));

			Image* ryoStrongKick = new Image();
			ryoStrongKick->Init(L"Image/Ryo/Ryo_StrongKick.bmp", 1200, 130, 10, 1, true, RGB(255, 0, 255));


			tempRyo->pushSkill("H", ryoLightPunch, 7, 5, 50, true, false, 0);
			tempRyo->pushSkill("Y", ryoStrongPunch, 9, 10, 70, true, false, 0);
			tempRyo->pushSkill("G", ryoLightKick, 7, 7, 60, false, true, 0);
			tempRyo->pushSkill("T", ryoStrongKick, 10, 10, 70, true, false, 0);


			tempRyo->PushSkipFrame(4);
			tempRyo->PushSkipFrame(6);
			tempRyo->PushSkipFrame(5);
			tempRyo->PushSkipFrame(8);

			tempRyo->InitCollider();

			objectManager->AddObject(OBJID::OBJ_CHARACTER, tempRyo);
		}
#pragma once endregion
		

	// tempRyo->pushSkill("TY", Down, 5, 10, 10, false, true, 3);
	
// 		tempRyo2->Init(2, new Image(), { 550,250 }, 200.f, 100.f, tempImage);
// 		objectManager->AddObject(OBJID::OBJ_CHARACTER, tempRyo2);

// 		tempRyo->SetEnemy(tempRyo2);
// 		tempRyo2->SetEnemy(tempRyo);

		HongCharacter* tempHong = new HongCharacter();
		vector<Image> tempImage2;
		{
			Image* maiProfile = new Image();
			maiProfile->Init(TEXT("Image/UI/yuri.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255));

			Image Idle2;
			Idle2.Init(L"Image/converted/akuma-ts-stance.bmp/gouki.bmp", 780, 120, 10, 1, true, RGB(255, 0, 255));

			Image Walk2;
			Walk2.Init(L"Image/converted/akuma-ts-stance.bmp/AkumaWalk.bmp", 1243, 120, 11, 1, true, RGB(255, 0, 255));

			Image BackWalk2;
			BackWalk2.Init(L"Image/converted/akuma-ts-stance.bmp/AkumaWalkB.bmp", 1243, 120, 11, 1, true, RGB(255, 0, 255));

			Image Down2;
			Down2.Init(L"Image/converted/akuma-ts-stance.bmp/AkumaDown.bmp", 990, 120, 11, 1, true, RGB(255, 0, 255));

			Image Dash2;
			Dash2.Init(L"Image/converted/akuma-ts-stance.bmp/AkumaBack.bmp", 17892, 120, 63, 1, true, RGB(255, 0, 255));

			Image Back2;
			Back2.Init(L"Image/converted/akuma-ts-stance.bmp/AkumaWalk.bmp", 1243, 120, 11, 1, true, RGB(255, 0, 255));

			//idle, 뒷걷기, 앞걷기, 숙이기, 앞대쉬, 백대쉬 순으로 넣어주세요
			tempImage2.push_back(Idle2);
			tempImage2.push_back(BackWalk2);
			tempImage2.push_back(Walk2);
			tempImage2.push_back(Down2);
			tempImage2.push_back(Dash2);
			tempImage2.push_back(Back2);


			Image* AkumaRk = new Image();
			AkumaRk->Init(L"Image/converted/akuma-ts-stance.bmp/AkumaRk.bmp", 1026, 120, 9, 1, true, RGB(255, 0, 255));
			
			Image* AkumaLk = new Image();
			AkumaLk->Init(L"Image/converted/akuma-ts-stance.bmp/AkumaLk.bmp", 4920, 120, 30, 1, true, RGB(255, 0, 255));

			Image* AkumaLp = new Image();
			AkumaLp->Init(L"Image/converted/akuma-ts-stance.bmp/AkumaLp.bmp", 1944, 120, 12, 1, true, RGB(255, 0, 255));

			Image* AkumaRp = new Image();
			AkumaRp->Init(L"Image/converted/akuma-ts-stance.bmp/AkumaRp.bmp", 1704, 120, 12, 1, true, RGB(255, 0, 255));

			tempHong->pushSkill("T", AkumaLp, 12, 5, 50, true, false, 4);
			tempHong->pushSkill("Y", AkumaRp, 12, 5, 50, true, false, 8);
			tempHong->pushSkill("G", AkumaLk, 30, 5, 80, false, true, 4);
			tempHong->pushSkill("H", AkumaRk, 9, 5, 50, false, true, 4);

			tempHong->Init(2, maiProfile, { 550,250 }, 200.f, 100.f, tempImage2);
			tempHong->InitCollider();
			objectManager->AddObject(OBJID::OBJ_CHARACTER, tempHong);
		}
		// 차승근 테스트
		// Image* ryoProfile = new Image();
		//ryoProfile->Init(TEXT("Image/UI/yuri.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255));

		//Mai* tempMai = new Mai();
		/*vector<Image> maiImage;
		Image maiIdle;
		Idle.Init(L"Image/Mai/Mai_Endle.bmp", 3000, 300, 12, 1, true, RGB(255, 0, 255));

		Image maiWalk;
		maiWalk.Init(L"Image/Mai/Mai_Smove_Front.bmp", 1901, 300, 6, 1, true, RGB(255, 0, 255));

		Image maiBackWalk;
		maiBackWalk.Init(L"Image/Mai/Mai_Smove_Back.bmp", 1677, 300, 6, 1, true, RGB(255, 0, 255));

		Image maiDown;
		maiDown.Init(L"Image/Mai/Mai_Sit.bmp", 1016, 300, 4, 1, true, RGB(255, 0, 255));

		Image maiDash;
		maiDash.Init(L"Image/Mai/Mai_Run.bmp", 2265, 300, 6, 1, true, RGB(255, 0, 255));

		Image maiBack;
		maiBack.Init(L"Image/Mai/Mai_Smove_Back.bmp", 1677, 300, 6, 1, true, RGB(255, 0, 255));
		maiImage.push_back(maiIdle);
		maiImage.push_back(maiBackWalk);
		maiImage.push_back(maiWalk);
		maiImage.push_back(maiDown);
		maiImage.push_back(maiDash);
		maiImage.push_back(maiBack);
		*/
		/*Image* maiProfile = new Image();
		maiProfile->Init(TEXT("Image/UI/yuri.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255));
		tempMai->Init(1, maiProfile, { 250,250 }, 200.f, 100.f, tempImage);*/
		//objectManager->AddObject(OBJID::OBJ_CHARACTER, tempMai);

		UI->SetPlayer(tempRyo, tempHong);
	}


	if (collisionManager = CollisionManager::GetInstance())
	{
		collisionManager->Init();
	}
}

void MainGame::Release()
{
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

	if (UI)
		UI->Update();

	if (collisionManager)
		collisionManager->Update(TimeDelta);

}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backBuffer->Render(hdc);

	if (UI)
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
