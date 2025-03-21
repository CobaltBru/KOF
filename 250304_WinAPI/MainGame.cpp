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
#include "Chang.h"
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

			Image* RyoProfile = new Image();
			RyoProfile->Init(TEXT("Image/UI/yuri.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255));

			//ryoProfile->Init(TEXT("Image/Ryo/Ryo_Profile.bmp"), 80, 86, true, RGB(255, 0, 255));

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

			Image UpBlock;
			UpBlock.Init(L"Image/Ryo/Ryo_UpperBlock.bmp", 600, 130, 5, 1, true, RGB(255, 0, 255));

			Image LowerBlock;
			LowerBlock.Init(L"Image/Ryo/Ryo_LowerBlock.bmp", 480, 130, 4, 1, true, RGB(255, 0, 255));

			Image UpHit;
			UpHit.Init(L"Image/Ryo/Ryo_UpperHit.bmp", 960, 130, 8, 1, true, RGB(255, 0, 255));

			Image LowerHit;
			LowerHit.Init(L"Image/Ryo/Ryo_LowerHit.bmp", 960, 130, 8, 1, true, RGB(255, 0, 255));

			Image Dead;
			Dead.Init(L"Image/Ryo/Ryo_Dead.bmp", 720, 130, 6, 1, true, RGB(255, 0, 255));

			//idle, �ްȱ�, �հȱ�, ���̱�, �մ뽬, ��뽬,������,�Ʒ����� ������ �־��ּ���
			tempImage.push_back(Idle);
			tempImage.push_back(BackWalk);
			tempImage.push_back(Walk);
			tempImage.push_back(Down);
			tempImage.push_back(Dash);
			tempImage.push_back(Back);
			tempImage.push_back(UpBlock);
			tempImage.push_back(LowerBlock);
			tempImage.push_back(UpHit);
			tempImage.push_back(LowerHit);
			tempImage.push_back(Dead);

			tempRyo->Init(1, RyoProfile, { 250,200 }, 200.f, 100.f, tempImage);

			Image* ryoLightPunch = new Image();
			ryoLightPunch->Init(L"Image/Ryo/Ryo_LightPunch.bmp", 840, 130, 7, 1, true, RGB(255, 0, 255));

			Image* ryoStrongPunch = new Image();
			ryoStrongPunch->Init(L"Image/Ryo/Ryo_StrongPunch.bmp", 1080, 130, 9, 1, true, RGB(255, 0, 255));

			Image* ryoLightKick = new Image();
			ryoLightKick->Init(L"Image/Ryo/Ryo_LightKick.bmp", 840, 130, 7, 1, true, RGB(255, 0, 255));

			Image* ryoStrongKick = new Image();
			ryoStrongKick->Init(L"Image/Ryo/Ryo_StrongKick.bmp", 1200, 130, 10, 1, true, RGB(255, 0, 255));

			Image* ryoHadogen = new Image();
			ryoHadogen->Init(L"Image/Ryo/Ryo_Hadoken.bmp", 1080, 130, 9, 1, true, RGB(255, 0, 255));

			Image* ryoHadogen2 = new Image();
			ryoHadogen2->Init(L"Image/Ryo/Ryo_Hadoken.bmp", 1080, 130, 9, 1, true, RGB(255, 0, 255));

			tempRyo->pushSkill("SDYT", ryoHadogen, 9, 20, 0, true, false, 3, 0, { 0.f,-60.f });
			tempRyo->pushSkill("SDHG", ryoHadogen2, 9, 20, 0, false, true, 3, 0, { 0.f,-20.f });
			tempRyo->pushSkill("H", ryoLightPunch, 7, 5, 45, true, false, 2, 4, { 0.f,-30.f });
			tempRyo->pushSkill("Y", ryoStrongPunch, 9, 10, 70, true, false, 3, 6, { 0.f,-10.f });
			tempRyo->pushSkill("G", ryoLightKick, 7, 7, 60, false, true, 2, 5, { 0.f,-10.f });
			tempRyo->pushSkill("T", ryoStrongKick, 10, 10, 70, true, false, 4, 8, { 0.f,-20.f });

			tempRyo->InitCollider();

			objectManager->AddObject(OBJID::OBJ_CHARACTER, tempRyo);
		}
#pragma once endregion

		//Chang Character Test//
		/*Chang* tempChang = new Chang();
		tempChang->InitCollider();
		objectManager->AddObject(OBJID::OBJ_CHARACTER, tempChang);*/
		//Ryo* tempRyo2 = new Ryo();
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

			//idle, �ްȱ�, �հȱ�, ���̱�, �մ뽬, ��뽬 ������ �־��ּ���
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
		// ���±� �׽�Ʈ
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
	// ����ۿ� ���� ����
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
