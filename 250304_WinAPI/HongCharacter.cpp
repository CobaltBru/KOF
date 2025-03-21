#include "HongCharacter.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include "Collider.h"
#include "CollisionManager.h"

void HongCharacter::InitCollider()
{
	collider = new Collider(this, {40.f, 80.f}, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);
}

void HongCharacter::Update(float TimeDelta)
{
	__super::Update(TimeDelta);
}

void HongCharacter::Render(HDC hdc)
{
	wchar_t szText[255] = L"";
	switch (currentState)
	{
	case Character::STATE::IDLE:
		wsprintf(szText, TEXT("STATE::IDLE"));
		break;
	case Character::STATE::BACK:
		wsprintf(szText, TEXT("STATE::BACK"));
		break;
	case Character::STATE::WALK:
		wsprintf(szText, TEXT("STATE::WALK"));
		break;
	case Character::STATE::DOWN:
		wsprintf(szText, TEXT("STATE::DOWN"));
		break;
	case Character::STATE::DASH:
		wsprintf(szText, TEXT("STATE::DASH"));
		break;
	case Character::STATE::BACKDASH:
		wsprintf(szText, TEXT("STATE::BACKDASH"));
		break;
	case Character::STATE::SKILL:
		wsprintf(szText, TEXT("STATE::SKILL"));
		break;
	case Character::STATE::PROCESS:
		wsprintf(szText, TEXT("STATE::PROCESS"));
		break;
	}
	TextOut(hdc, pos.x, pos.y - 30.f, szText, wcslen(szText));

	if (currentState == STATE::PROCESS)
	{
		skillSet[currentSkill].image->Render(hdc, pos.x - 45, pos.y, framecnt, screenWay);
	}
	else
	{
		if (screenWay)
		{
			images[getIndex()].Render(hdc, pos.x, pos.y + 20.f, framecnt, screenWay);
		}
		else
		{
			//images[getIndex()].Render(hdc, pos.x - 35, pos.y - 55, framecnt, screenWay);
		}
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
	wstring folderPath = L"Image/converted/akuma-ts-stance.bmp/";
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

		/*Animation* animation = new Animation;

		Image* image = new Image;

		if (FAILED(image->Init(filePath.c_str())))
		{
			MessageBox(g_hWnd, filePath.c_str(), TEXT("���"), MB_OK);
		}

		animation->Images.push_back(image);
		Animations.push_back(animation);*/
	} while (FindNextFile(hFind, &findFileData) != 0);  // ���� ���� ã��

	FindClose(hFind);  // �ڵ� �ݱ�
}
