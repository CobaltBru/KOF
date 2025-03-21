#include "KOF_Iori.h"
#include "Image.h"
#include "KOFKeyManager.h"

void KOF_Iori::Init()
{
	pos = { 0.0f, 0.0f };
	moveSpeed = 5.0f;
	image = new Image();
	/*if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1,
		true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}*/

	if (FAILED(image->Init(L"Image/Ryo/Ryo_Walk1.bmp", 422, 105, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	
	

	elapsedFrame = 0;
	currAnimaionFrame = 0;


	attackImage = new Image();
	if (FAILED(attackImage->Init(TEXT("Image/iori_kick.bmp"), 1170, 106, 10, 1,
		true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	bAttack = false;
}

void KOF_Iori::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}

	if (attackImage)
	{
		attackImage->Release();
		delete attackImage;
		attackImage = nullptr;
	}
}

void KOF_Iori::Update(float TimeDelta)
{
	elapsedFrame++;
	//if (elapsedFrame >= 5)

	if (KeyManager::GetInstance()->IsOnceKeyUp(VK_SPACE))
	{
		currAnimaionFrame++;
		Move();

		if (currAnimaionFrame > 5)
		{
			currAnimaionFrame = 0;
		}
		elapsedFrame = 0;
	}


	// TODO : 김태경이 테스트하려고 만듦
#pragma once region TaeKyung
	KeyUpdate(TimeDelta);

	//Attack();
	Move();

	/*if (KOFKeyManager::GetInstance()->GetPlayer1Command() != "")
	{
		string command = KOFKeyManager::GetInstance()->GetPlayer1Command();
		if (command.size() >= 3)
		{

		}
	}*/

	currAnimaionFrame = elapsedFrame / 5;
	if (currAnimaionFrame > 5)
	{
		currAnimaionFrame = 0;
		elapsedFrame = 0;

		if (bAttack)
			bAttack = false;
	}
#pragma once endregion
}

void KOF_Iori::Render(HDC hdc)
{
	if (bAttack)
	{
		attackImage->Render(hdc, pos.x, pos.y, currAnimaionFrame);
	}
	else
	{
		if (image)
			image->Render(hdc, pos.x, pos.y, currAnimaionFrame);
	}
}

void KOF_Iori::Move()
{
	if (characterKey[(int)EMoveKey::KEYW] && characterKey[(int)EMoveKey::KEYD])
	{

	}
	else if (characterKey[(int)EMoveKey::KEYW] && characterKey[(int)EMoveKey::KEYA])
	{

	}
	else if (characterKey[(int)EMoveKey::KEYS])
	{

	}
	else if (characterKey[(int)EMoveKey::KEYA] && stepTime > 0.0001f && currentTime - stepTime < 0.2f)
	{
		pos.x -= moveSpeed * 2;

		stepTime = 0.f;
	}
	else if (characterKey[(int)EMoveKey::KEYD] && stepTime > 0.0001f && stepTime - currentTime < 0.2f)
	{
		pos.x += moveSpeed * 2;
		stepTime = 0.f;
	}
	else if (characterKey[(int)EMoveKey::KEYW])
	{

	}
	else if (characterKey[(int)EMoveKey::KEYA])
	{
		pos.x -= moveSpeed;
	}
	else if (characterKey[(int)EMoveKey::KEYS])
	{

	}
	else if (characterKey[(int)EMoveKey::KEYD])
	{
		pos.x += moveSpeed;
	}
}

void KOF_Iori::KeyUpdate(float TimeDelta)
{
	currentTime += TimeDelta;

	//characterKey[(int)EMoveKey::KEYW] = KeyManager::GetInstance()->IsStayKeyDown('W');
	//characterKey[(int)EMoveKey::KEYA] = KeyManager::GetInstance()->IsStayKeyDown('A');
	//characterKey[(int)EMoveKey::KEYS] = KeyManager::GetInstance()->IsStayKeyDown('S');
	//characterKey[(int)EMoveKey::KEYD] = KeyManager::GetInstance()->IsStayKeyDown('D');

	bool bA = KeyManager::GetInstance()->IsOnceKeyUp('A');
	bool bD = KeyManager::GetInstance()->IsOnceKeyUp('D');

	if (bA || bD)
		stepTime = currentTime;
}

void KOF_Iori::StateUpdate()
{
}

void KOF_Iori::Attack()
{
	if (!bAttack)
	{
		bAttack = true;
		currAnimaionFrame = 0;
		elapsedFrame = 0;
	}
}

KOF_Iori::KOF_Iori()
{
}

KOF_Iori::~KOF_Iori()
{
}
