#include "HongCharacter.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include "Collider.h"
#include "CollisionManager.h"

//void HongCharacter::Init()
//{
//	pos = { 0.0f, 0.0f };
//	moveSpeed = 5.0f;
//	image = new Image();
//	/*if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1,
//		true, RGB(255, 0, 255))))
//	{
//		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
//	}*/
//
//	elapsedFrame = 0;
//	currAnimaionFrame = 0;
//
//	attackImage = new Image();
//	if (FAILED(attackImage->Init(TEXT("Image/iori_kick.bmp"), 1170, 106, 10, 1,
//		true, RGB(255, 0, 255))))
//	{
//		MessageBox(g_hWnd, TEXT("Image/iori_kick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
//	}
//
//	bAttack = false;
//
//	collider = new Collider(this, pos, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
//	CollisionManager* manager = CollisionManager::GetInstance();
//
//	manager->AddObject(OBJID::OBJ_CHARACTER, collider);	
//
//	collider->DebugRender(true);
//
//	Load();
//}

void HongCharacter::InitCollider()
{
	collider = new Collider(this, {0.f, 0.f}, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);

	//Load();
}

void HongCharacter::Update(float TimeDelta)
{
	//currentTime += TimeDelta;

	//currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);

	//bool keyA = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
	//bool keyS = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
	//bool keyD = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);

	//if (keyA && dashTime > 0.0001f && currentTime - dashTime > 0.3f)
	//{
	//	dashTime = currentTime;
	//}
	//else if (keyA)
	//{
	//	if (screenWay == false) //�ް�����
	//	{
	//		moveWay = -1;
	//		speed = 0.7f;
	//		if (currentState == STATE::BACK) currentState = STATE::BACK;
	//		else currentState = STATE::BACK;
	//	}
	//	else //������ 
	//	{
	//		moveWay = 1;
	//		speed = 1.0f;
	//		if (currentState == STATE::WALK) currentState = STATE::DASH;
	//		else currentState = STATE::WALK;
	//	}
	//}
	//else if (keyD)
	//{
	//	if (screenWay == false) //������
	//	{
	//		moveWay = 1;
	//		speed = 1.0f;
	//		if (currentState == STATE::WALK) currentState = STATE::DASH;
	//		else currentState = STATE::WALK;
	//	}
	//	else //�ް�����
	//	{
	//		moveWay = -1;
	//		speed = 0.7f;
	//		if (currentState == STATE::BACK) currentState = STATE::BACK;
	//		else currentState = STATE::BACK;
	//	}
	//}
	//else if (keyS) //���̱�
	//{
	//	speed = 0;
	//	currentState = STATE::DOWN;
	//}
	//else if (currentState == STATE::PROCESS) //�����
	//{
	//	timecnt += TimeDelta;
	//	framecnt = timecnt / (TimeDelta * 4.0f); //���� ������ ���

	//	// TODO ���������ؾ��ϴ� �������̶��

	//	if (framecnt == skillSet[currentSkill].attackFrame)
	//	{
	//		HitResult hit;
	//		if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, pos, { pos.x - 100.f, pos.y }, this, true))
	//		{
	//			if (Character* OtherCharacter = dynamic_cast<Character*>(hit.Actors[0]))
	//			{
	//				attack(OtherCharacter);

	//				//skillSet[currentSkill].damage;
	//			}
	//		}
	//	}

	//	if (framecnt >= skillSet[currentSkill].maxFrame)//������ IDLE��
	//	{
	//		endSkill();
	//	}

	//}
	//else
	//{
	//	speed = 0;
	//	currentState = STATE::IDLE;
	//}

	//if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD7) && currentState == STATE::IDLE)
	//{
	//	framecnt = 0;
	//	timecnt = 0;
	//	useSkill("Y");
	//}



	//if (currentState != STATE::PROCESS)
	//{
	//	timecnt += TimeDelta;
	//	framecnt = timecnt / (TimeDelta * FrameSpeed); //���� ������ ���

	//	CheckMaxFrame();
	//}

	//Move(TimeDelta);
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
	TextOut(hdc, pos.x - 75, pos.y - 60, szText, wcslen(szText));

	if (currentState == STATE::PROCESS)
	{
		skillSet[currentSkill].image->Render(hdc, pos.x - 75, pos.y - 60, framecnt, screenWay);
	}
	else
	{
		if (screenWay)
		{
			images[getIndex()].Render(hdc, pos.x - 40, pos.y - 60, framecnt, screenWay);
		}
		else
		{
			images[getIndex()].Render(hdc, pos.x - 35, pos.y - 55, framecnt, screenWay);
		}
	}
}

void HongCharacter::CheckMaxFrame()
{
	if (framecnt >= images[getIndex()].GetMaxFrame())//����ó��
	{
		framecnt = 0;
		timecnt = 0;
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

void Animation::Release()
{
	for (auto& iter : Images)
	{
		delete iter;
	}
	Images.clear();
}
