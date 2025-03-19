#include "KOF_Iori.h"
#include "Image.h"
#include "KOFKeyManager.h"

void KOF_Iori::Init()
{
	pos = { 0.0f, 0.0f };
	moveSpeed = 5.0f;
	image = new Image();
	if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1, 
		true, RGB(255,0,255))))
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

		if (currAnimaionFrame > 8)
		{
			currAnimaionFrame = 0;
		}
		elapsedFrame = 0;
	}
	currAnimaionFrame = elapsedFrame / 5;
	if (currAnimaionFrame > 8)
	{
		currAnimaionFrame = 0;
		elapsedFrame = 0;
		
		if (bAttack)
			bAttack = false;		
	}

	// TODO : 김태경이 테스트하려고 만듦
#pragma once region TaeKyung
	KeyUpdate(TimeDelta);
	if(characterKey[(int)EMoveKey::KEYT] || characterKey[(int)EMoveKey::KEYY] || characterKey[(int)EMoveKey::KEYG] || characterKey[(int)EMoveKey::KEYH])
		Attack();
	Move();

	if (KOFKeyManager::GetInstance()->GetPlayer1Command() != "")
	{
		string command = KOFKeyManager::GetInstance()->GetPlayer1Command();
		if (command.size() >= 3)
		{
			
		}
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
	 if (KeyManager::GetInstance()->IsOnceKeyUp('A'))
	{
		if (stepTime > 0.0001f && currentTime - stepTime < 0.2f)
		{
			int a = 0;
		}
		else
		{
			pos.x -= moveSpeed;
		}
		stepTime = currentTime;
	} 
	else if (KeyManager::GetInstance()->IsOnceKeyUp('D'))
	{
		if (stepTime > 0.0001f && stepTime - currentTime < 0.2f)
		{
			int a = 0;
		}
		else
		{
			pos.x += moveSpeed;
		}
		stepTime = currentTime;
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

	if (KeyManager::GetInstance()->IsOnceKeyDown('W'))
		keyBuffer.push({ 'W',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('A'))
		keyBuffer.push({ 'A',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('S'))
		keyBuffer.push({ 'S',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('D'))
		keyBuffer.push({ 'D',currentTime });
	if (!keyBuffer.empty())
	{
		float b = currentTime - keyBuffer.front().second;
	}
	
	while (!keyBuffer.empty() && currentTime - keyBuffer.front().second > 0.3f)
		keyBuffer.pop();

	characterKey[(int)EMoveKey::KEYW] = KeyManager::GetInstance()->IsStayKeyDown('W');
	characterKey[(int)EMoveKey::KEYA] = KeyManager::GetInstance()->IsStayKeyDown('A');
	characterKey[(int)EMoveKey::KEYS] = KeyManager::GetInstance()->IsStayKeyDown('S');
	characterKey[(int)EMoveKey::KEYD] = KeyManager::GetInstance()->IsStayKeyDown('D');

	characterKey[(int)EMoveKey::KEYT] = KeyManager::GetInstance()->IsOnceKeyDown('T');
	characterKey[(int)EMoveKey::KEYY] = KeyManager::GetInstance()->IsOnceKeyDown('Y');
	characterKey[(int)EMoveKey::KEYG] = KeyManager::GetInstance()->IsOnceKeyDown('G');
	characterKey[(int)EMoveKey::KEYH] = KeyManager::GetInstance()->IsOnceKeyDown('H');
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
