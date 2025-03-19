#include "HongCharacter.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include "Collider.h"
#include "CollisionManager.h"

void HongCharacter::Init()
{
	pos = { 0.0f, 0.0f };
	moveSpeed = 5.0f;
	image = new Image();
	if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1,
		true, RGB(255, 0, 255))))
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

	collider = new Collider(this, pos, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);	

	collider->DebugRender(true);

}

void HongCharacter::Release()
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

void HongCharacter::Update(float TimeDelta)
{
	elapsedFrame++;
	//if (elapsedFrame >= 5)

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
	{
		currAnimaionFrame++;
		Move();

		if (currAnimaionFrame > 8)
		{
			currAnimaionFrame = 0;
		}
		elapsedFrame = 0;
		HitResult hit;
		if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, pos, { pos.x + 100.f, pos.y }, this, true))
		{
			int a = 10;

			//dynamic_cast<asdf>(hit.Actors[0]);
		}
	}



}

void HongCharacter::Render(HDC hdc)
{
	if (bAttack)
	{
		attackImage->Render(hdc, pos.x, pos.y, currAnimaionFrame);
	}
	else
	{
		if (image)
			image->Render(hdc, pos.x - 34, pos.y - 52, currAnimaionFrame);
	}
}

void HongCharacter::Move()
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

void HongCharacter::KeyUpdate(float TimeDelta)
{
	currentTime += TimeDelta;

	characterKey[(int)EMoveKey::KEYW] = KeyManager::GetInstance()->IsStayKeyDown('W');
	characterKey[(int)EMoveKey::KEYA] = KeyManager::GetInstance()->IsStayKeyDown('A');
	characterKey[(int)EMoveKey::KEYS] = KeyManager::GetInstance()->IsStayKeyDown('S');
	characterKey[(int)EMoveKey::KEYD] = KeyManager::GetInstance()->IsStayKeyDown('D');

	bool bA = KeyManager::GetInstance()->IsOnceKeyUp('A');
	bool bD = KeyManager::GetInstance()->IsOnceKeyUp('D');

	if (bA || bD)
		stepTime = currentTime;
}

void HongCharacter::StateUpdate()
{
}

void HongCharacter::Attack()
{
	if (!bAttack)
	{
		bAttack = true;
		currAnimaionFrame = 0;
		elapsedFrame = 0;
	}
}

HongCharacter::HongCharacter()
{
}

HongCharacter::~HongCharacter()
{
}
