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
	/*if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1,
		true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}*/

	elapsedFrame = 0;
	currAnimaionFrame = 0;

	attackImage = new Image();
	if (FAILED(attackImage->Init(TEXT("Image/iori_kick.bmp"), 1170, 106, 10, 1,
		true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_kick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	bAttack = false;

	collider = new Collider(this, pos, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);	

	collider->DebugRender(true);

	Load();
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
		{
			/*image->Render(hdc, pos.x - 34, pos.y - 52, currAnimaionFrame);*/
			image->Render(hdc, pos.x - 34, pos.y - 52);
			//Animations[0]->Render(hdc);
		}

		
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

void HongCharacter::Load()
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	// ���� �� ��� ������ ã�� ���� ���� ���� (���⼭�� *.bmp ������ ã��)
	wstring folderPath = L"Image/converted/";
	wstring searchPattern = folderPath + L"*.bmp";

	// ù ��° ������ ã��
	hFind = FindFirstFile(searchPattern.c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::wcerr << L"������ ã�� �� �����ϴ�: " << folderPath << std::endl;
		return;
	}

	do {
		// ���� ������ ����
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue;
		}

		// ã�� ���� ��� ����
		std::wstring filePath = folderPath + findFileData.cFileName;

		if (FAILED(image->Init(filePath.c_str())))
		{
			MessageBox(g_hWnd, filePath.c_str(), TEXT("���"), MB_OK);
		}

	} while (FindNextFile(hFind, &findFileData) != 0);  // ���� ���� ã��

	FindClose(hFind);  // �ڵ� �ݱ�
}

void Animation::PlayAnimation(float TimeDelta)
{
	PlayTime += TimeDelta;

	if (PlayTime >= (float)MaxFrame)
	{
		PlayTime = (float)MaxFrame;
	}
}

void Animation::Render(HDC hdc)
{
	Images[(int)PlayTime]->Render(hdc, 0, 0);
}
