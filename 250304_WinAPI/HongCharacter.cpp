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
//		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
//	}*/
//
//	elapsedFrame = 0;
//	currAnimaionFrame = 0;
//
//	attackImage = new Image();
//	if (FAILED(attackImage->Init(TEXT("Image/iori_kick.bmp"), 1170, 106, 10, 1,
//		true, RGB(255, 0, 255))))
//	{
//		MessageBox(g_hWnd, TEXT("Image/iori_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
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
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
	{
		HitResult hit;
		if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, pos, { pos.x - 100.f, pos.y }, this, true))
		{
			int a = 10;			
			//dynamic_cast<asdf>(hit.Actors[0]);
		}
	}

	currentTime += TimeDelta;

	currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);

	bool keyA = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
	bool keyS = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
	bool keyD = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);

	if (keyA && dashTime > 0.0001f && currentTime - dashTime > 0.3f)
	{
		dashTime = currentTime;
	}
	else if (keyA)
	{
		if (screenWay == false) //뒷걸음질
		{
			moveWay = -1;
			speed = 0.7f;
			if (currentState == STATE::BACK) currentState = STATE::BACK;
			else currentState = STATE::BACK;
		}
		else //앞으로 
		{
			moveWay = 1;
			speed = 1.0f;
			if (currentState == STATE::WALK) currentState = STATE::DASH;
			else currentState = STATE::WALK;
		}
	}
	else if (keyD)
	{
		if (screenWay == false) //앞으로
		{
			moveWay = 1;
			speed = 1.0f;
			if (currentState == STATE::WALK) currentState = STATE::DASH;
			else currentState = STATE::WALK;
		}
		else //뒷걸음질
		{
			moveWay = -1;
			speed = 0.7f;
			if (currentState == STATE::BACK) currentState = STATE::BACK;
			else currentState = STATE::BACK;
		}
	}
	else if (keyS) //숙이기
	{
		speed = 0;
		currentState = STATE::DOWN;
	}
	else
	{
		speed = 0;
		currentState = STATE::IDLE;
	}

	useSkill(currentCommand);

	if (currentState != STATE::IDLE)
	{
		timecnt += TimeDelta;
		framecnt = timecnt / (TimeDelta * FRAMESPEED); //현재 프레임 계산
		if (currentState == STATE::PROCESS) //기술중
		{
			if (framecnt >= skillSet[currentSkill].maxFrame)//끝나면 IDLE로
			{
				endSkill();
			}
		}
	}
	else
	{
		timecnt += TimeDelta * FRAMESPEED;//TimeDelta * FRAMESPEED;
		framecnt = timecnt;// / (TimeDelta * FRAMESPEED); //현재 프레임 계산
	}

	CheckMaxFrame();

	Move(TimeDelta);
}

void HongCharacter::Render(HDC hdc)
{
	if (currentState == STATE::PROCESS)
	{
		skillSet[currentSkill].image->Render(hdc, pos.x, pos.y, framecnt, screenWay);
	}
	else
	{
		if (screenWay)
		{
			//images[getIndex()].Render(hdc, pos.x - 90, pos.y - 55, framecnt, screenWay);
			images[getIndex()].Render(hdc, pos.x - 40, pos.y - 60, framecnt, screenWay);
		}
		else
		{
			//images[getIndex()].Render(hdc, pos.x - 35, pos.y - 55, framecnt, screenWay);
			images[getIndex()].Render(hdc, pos.x - 35, pos.y - 55, framecnt, screenWay);
		}
	}
}

void HongCharacter::CheckMaxFrame()
{
	if (framecnt >= images[getIndex()].GetMaxFrame())//루프처리
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

	// 폴더 내 모든 파일을 찾기 위한 패턴 설정 (여기서는 *.bmp 파일을 찾음)
	wstring folderPath = L"Image/converted/akuma-ts-stance.bmp/";
	wstring searchPattern = folderPath + L"*.bmp";

	// 첫 번째 파일을 찾기
	hFind = FindFirstFile(searchPattern.c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::wcerr << L"폴더를 찾을 수 없습니다: " << folderPath << std::endl;
		return;
	}

	do {
		// 숨김 파일은 무시
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			continue;
		}

		// 찾은 파일 경로 생성
		std::wstring filePath = folderPath + findFileData.cFileName;

		/*Animation* animation = new Animation;

		Image* image = new Image;

		if (FAILED(image->Init(filePath.c_str())))
		{
			MessageBox(g_hWnd, filePath.c_str(), TEXT("경고"), MB_OK);
		}

		animation->Images.push_back(image);
		Animations.push_back(animation);*/
	} while (FindNextFile(hFind, &findFileData) != 0);  // 다음 파일 찾기

	FindClose(hFind);  // 핸들 닫기
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
