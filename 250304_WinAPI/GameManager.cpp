#include "GameManager.h"
#include "Ryo.h"
#include "Image.h"
#include "HongCharacter.h"
#include "UserInterface.h"
#include "CollisionManager.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "Mai.h"
#include "Chang.h"
#include "Kusanagi.h"

void GameManager::Init()
{
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

		//idle, 뒷걷기, 앞걷기, 숙이기, 앞대쉬, 백대쉬,윗막기,아래막기 순으로 넣어주세요
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

		tempRyo->Init(1, RyoProfile, { 250.f,320.f }, 200.f, 100.f, tempImage);

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
	}
#pragma once endregion

#pragma region Hong
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

		tempHong->Init(2, maiProfile, { 550.f,320.f }, 200.f, 100.f, tempImage2);
		tempHong->InitCollider();
	}
#pragma endregion

#pragma 차승근 테스트
	Mai* tempMai = new Mai();
	{
		vector<Image> maiImage;
		Image maiIdle;
		maiIdle.Init(L"Image/Mai/Mai_Endle.bmp", 1200, 100, 12, 1, true, RGB(255, 0, 255));

		Image maiWalk;
		maiWalk.Init(L"Image/Mai/Mai_Smove_Front.bmp", 600, 100, 6, 1, true, RGB(255, 0, 255));

		Image maiBackWalk;
		maiBackWalk.Init(L"Image/Mai/Mai_Smove_Back.bmp", 600, 100, 6, 1, true, RGB(255, 0, 255));

		Image maiDown;
		maiDown.Init(L"Image/Mai/Mai_Sit.bmp", 100, 100, 4, 1, true, RGB(255, 0, 255));

		Image maiDash;
		maiDash.Init(L"Image/Mai/Mai_Run.bmp", 800, 100, 6, 1, true, RGB(255, 0, 255));

		Image maiBack;
		maiBack.Init(L"Image/Mai/Mai_Smove_Back.bmp", 600, 100, 6, 1, true, RGB(255, 0, 255));
		maiImage.push_back(maiIdle);
		maiImage.push_back(maiBackWalk);
		maiImage.push_back(maiWalk);
		maiImage.push_back(maiDown);
		maiImage.push_back(maiDash);
		maiImage.push_back(maiBack);


		Image* maiProfile = new Image();
		maiProfile->Init(TEXT("Image/UI/yuri.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255));
		tempMai->Init(2, maiProfile, { 550.f,320.f }, 200.f, 100.f, maiImage);

		Image* maiLightPunch = new Image();
		maiLightPunch->Init(L"Image/Mai/Mai_Wpunch.bmp", 533, 100, 4, 1, true, RGB(255, 0, 255));

		Image* maiStrongPunch = new Image();
		maiStrongPunch->Init(L"Image/Mai/Mai_Spunch.bmp", 801, 165, 5, 1, true, RGB(255, 0, 255));

		Image* maiLightKick = new Image();
		maiLightKick->Init(L"Image/Mai/Mai_Middlekick.bmp", 961, 149, 6, 1, true, RGB(255, 0, 255));

		Image* maiStrongKick = new Image();
		maiStrongKick->Init(L"Image/Mai/Mai_HighKick.bmp", 961, 165, 6, 1, true, RGB(255, 0, 255));


		tempMai->pushSkill("H", maiLightPunch, 7, 5, 50, true, false, 2);
		tempMai->pushSkill("Y", maiStrongPunch, 9, 10, 70, true, false, 4);
		tempMai->pushSkill("G", maiLightKick, 7, 7, 60, true, false, 3);
		tempMai->pushSkill("T", maiStrongKick, 10, 10, 70, true, false, 3);

		tempMai->InitCollider();
		
	}
#pragma endregion

#pragma region Kusanagi
	Kusanagi* kusanagi = new Kusanagi();
	vector<Image>kusaImages;
	{
		Image* kusaProfile = new Image;
		kusaProfile->Init(TEXT("Image/Kusanagi/Kusanagip.bmp"), 97, 111, 1, 1, true, RGB(248, 0, 248));
		Image* IDLE = new Image;
		IDLE->Init(TEXT("Image/Kusanagi/idle.bmp"), 850, 130, 10, 1, true, RGB(248, 0, 248));
		Image* DASH = new Image;
		DASH->Init(TEXT("Image/Kusanagi/run2.bmp"), 630, 130, 6, 1, true, RGB(248, 0, 248));
		Image* DOWN = new Image;
		DOWN->Init(TEXT("Image/Kusanagi/down.bmp"), 85, 130, 1, 1, true, RGB(248, 0, 248));
		Image* WALK = new Image;
		WALK->Init(TEXT("Image/Kusanagi/run1.bmp"), 510, 130, 6, 1, true, RGB(248, 0, 248));
		Image* BACK = new Image;
		BACK->Init(TEXT("Image/Kusanagi/back3.bmp"), 510, 130, 6, 1, true, RGB(248, 0, 248));
		Image* BACKDASH = new Image;
		BACKDASH->Init(TEXT("Image/Kusanagi/back3.bmp"), 510, 130, 6, 1, true, RGB(248, 0, 248));
		Image* BLOCKUPPER = new Image;
		BLOCKUPPER->Init(TEXT("Image/Kusanagi/block2.bmp"), 900, 110, 10, 1, true, RGB(248, 0, 248));
		Image* BLOCKLOWER = new Image;
		BLOCKLOWER->Init(TEXT("Image/Kusanagi/block2.bmp"), 900, 110, 10, 1, true, RGB(248, 0, 248));

		Image* PUNCH1 = new Image;
		PUNCH1->Init(TEXT("Image/Kusanagi/punch1.bmp"), 400, 130, 4, 1, true, RGB(248, 0, 248));
		Image* PUNCH2 = new Image;
		PUNCH2->Init(TEXT("Image/Kusanagi/punch2.bmp"), 910, 130, 7, 1, true, RGB(248, 0, 248));
		Image* KICK1 = new Image;
		KICK1->Init(TEXT("Image/Kusanagi/kick1.bmp"), 960, 130, 8, 1, true, RGB(248, 0, 248));
		Image* KICK2 = new Image;
		KICK2->Init(TEXT("Image/Kusanagi/kick2.bmp"), 990, 130, 11, 1, true, RGB(248, 0, 248));
		Image* COMBO1 = new Image;
		COMBO1->Init(TEXT("Image/Kusanagi/combo1.bmp"), 1210, 130, 11, 1, true, RGB(248, 0, 248));

		Image* COMBO2 = new Image;
		COMBO2->Init(TEXT("Image/Kusanagi/combo2.bmp"), 1375, 130, 11, 1, true, RGB(248, 0, 248));

		//idle, 뒷걷기, 앞걷기, 숙이기, 앞대쉬, 백대쉬,윗방어,아랫방어
		kusaImages.push_back(*IDLE);
		kusaImages.push_back(*BACK);
		kusaImages.push_back(*WALK);
		kusaImages.push_back(*DOWN);
		kusaImages.push_back(*DASH);
		kusaImages.push_back(*BACKDASH);
		kusaImages.push_back(*BLOCKUPPER);
		kusaImages.push_back(*BLOCKLOWER);


		kusanagi->Init(2, kusaProfile, { 550.f,320.f }, 100, 100, kusaImages);
		kusanagi->pushSkill("SG", COMBO2, 11, 10, 40, false, true, 0);
		kusanagi->pushSkill("SH", COMBO1, 11, 10, 40, true, false, 0);
		kusanagi->pushSkill("T", PUNCH1, 4, 5, 25, true, false, 0);
		kusanagi->pushSkill("Y", PUNCH2, 7, 5, 35, true, false, 0);
		kusanagi->pushSkill("G", KICK1, 8, 10, 40, false, true, 0);
		kusanagi->pushSkill("H", KICK2, 11, 10, 40, false, true, 0);
		
		kusanagi->InitCollider();
	}
#pragma endregion

#pragma region Chang
	Chang* tempChang = new Chang();
	tempChang->InitCollider();
#pragma endregion

	tempChang->SetActive(false);
	tempMai->SetActive(false);
	kusanagi->SetActive(false);

	//1p에 맞춰서 넣어주기
	P1Players.push_back(tempRyo);
	P1Players.push_back(tempChang);

	//2p에 맞춰서 넣어주기
	P2Players.push_back(tempHong);
	P2Players.push_back(kusanagi);
	P2Players.push_back(tempMai);

	ObjectManager::GetInstance()->AddObject(OBJID::OBJ_CHARACTER, tempRyo);
	ObjectManager::GetInstance()->AddObject(OBJID::OBJ_CHARACTER, tempHong);
	ObjectManager::GetInstance()->AddObject(OBJID::OBJ_CHARACTER, tempMai);
	ObjectManager::GetInstance()->AddObject(OBJID::OBJ_CHARACTER, kusanagi);
	ObjectManager::GetInstance()->AddObject(OBJID::OBJ_CHARACTER, tempChang);

	CurrentPlayer[P1] = P1Players[0];
	CurrentPlayer[P2] = P2Players[0];

	UserInterface::GetInstance()->SetPlayer(CurrentPlayer[P1], CurrentPlayer[P2]);

	{
		FPOINT p0 = { 0.f, 70.f };  // 시작점
		FPOINT p1 = { 200.f, 70.f };  // 제어점
		FPOINT p2 = { 300.f, 320.f };  // 끝점

		P1TagPath.push_back(p0);
		P1TagPath.push_back(p1);
		P1TagPath.push_back(p2);
	}

	{
		FPOINT p0 = { 1080.f, 70.f };  // 시작점
		FPOINT p1 = { 880.f, 70.f };  // 제어점
		FPOINT p2 = { 780.f, 320.f };  // 끝점

		P2TagPath.push_back(p0);
		P2TagPath.push_back(p1);
		P2TagPath.push_back(p2);
	}
}

void GameManager::Update(float TimeDelta)
{
	if (UserInterface::GetInstance())
		UserInterface::GetInstance()->Update();

	//태그중이 아닐 때
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE) && !P1Tag)
	{
		if (++NextP1Player >= P1Players.size())
		{
			NextP1Player = 0;
		}

		//살아있다면
		if (*P1Players[NextP1Player]->getCurrentHp() >= 0)
		{
			CurrentPlayer[P1]->SetActive(false);
			CurrentPlayer[P1] = P1Players[NextP1Player];
			P1Tag = true;
			CurrentPlayer[P1]->SetActive(true);
			UserInterface::GetInstance()->SetPlayer(CurrentPlayer[P1], CurrentPlayer[P2]);
		}
	}

	//태그중이 아닐 때
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_ADD) && !P2Tag)
	{
		if (++NextP2Player >= P2Players.size())
		{
			NextP2Player = 0;
		}
		//살아있다면
		if (*P2Players[NextP2Player]->getCurrentHp() >= 0.f)
		{
			CurrentPlayer[P2]->SetActive(false);
			CurrentPlayer[P2] = P2Players[NextP2Player];
			P2Tag = true;
			CurrentPlayer[P2]->SetActive(true);

			UserInterface::GetInstance()->SetPlayer(CurrentPlayer[P1], CurrentPlayer[P2]);
		}
	}

	if (P1Tag)
	{
		P1TagTime += TimeDelta * TagSpeed;
		if (P1TagTime >= 1.f)
		{
			P1TagTime = 0.f;
			P1Tag = false;
			UpdateCharacterPosition(CurrentPlayer[P1], 1.f, P1TagPath[0], P1TagPath[1], P1TagPath[2]);
		}
		else
		{
			UpdateCharacterPosition(CurrentPlayer[P1], P1TagTime, P1TagPath[0], P1TagPath[1], P1TagPath[2]);
		}
	}

	if (P2Tag)
	{
		P2TagTime += TimeDelta * TagSpeed;
		if (P2TagTime >= 1.f)
		{
			P2TagTime = 0.f;
			P2Tag = false;
			UpdateCharacterPosition(CurrentPlayer[P2], 1.f, P2TagPath[0], P2TagPath[1], P2TagPath[2]);
		}
		else
		{
			UpdateCharacterPosition(CurrentPlayer[P2], P2TagTime, P2TagPath[0], P2TagPath[1], P2TagPath[2]);
		}
	}
}

void GameManager::Release()
{
	ReleaseInstance();
}

void GameManager::Render(HDC hdc)
{
	if (UserInterface::GetInstance())
		UserInterface::GetInstance()->Render(hdc);
}

void GameManager::UpdateCharacterPosition(Character* newPlayer, float Time, const FPOINT& P0, const FPOINT& P1, const FPOINT& P2)
{
	if (Time <= 1.0f) {
		float u = 1 - Time;

		FPOINT newPos = { (u * u * P0.x + 2 * u * Time * P1.x + Time * Time * P2.x),
							(u * u * P0.y + 2 * u * Time * P1.y + Time * Time * P2.y) };

		newPlayer->SetPos(newPos);
	}
}
