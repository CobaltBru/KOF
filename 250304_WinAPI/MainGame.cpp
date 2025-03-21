#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TimerManager.h"
#include "KOFKeyManager.h"
#include "UserInterface.h"
#include "ObjectManager.h"
#include "HongCharacter.h"
#include "Kusanagi.h"
#include "CollisionManager.h"
#include "Ryo.h"
#include "Mai.h"
#include "EffectManager.h"
#include "Chang.h"
#include "GameManager.h"
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

	UI = UserInterface::GetInstance();
	UI->Init();

	timerManager = TimerManager::GetInstance();
	effectManager = EffectManager::GetInstance();
	effectManager->Init();
	if (objectManager = ObjectManager::GetInstance())
	{
		objectManager->Init();
	}


	//Chang Character Test//
	/*Chang* tempChang = new Chang();
	tempChang->InitCollider();
	objectManager->AddObject(OBJID::OBJ_CHARACTER, tempChang);*/
	//Ryo* tempRyo2 = new Ryo();
	//tempRyo->pushSkill("TY", Down, 5, 10, 10, false, true, 3);

	//tempRyo2->Init(2, new Image(), { 550,250 }, 200.f, 100.f, tempImage);
	//objectManager->AddObject(OBJID::OBJ_CHARACTER, tempRyo2);

	//tempRyo->SetEnemy(tempRyo2);
	//tempRyo2->SetEnemy(tempRyo);





	//Chang Character Test//
	/*Chang* tempChang = new Chang();
	tempChang->InitCollider();
	objectManager->AddObject(OBJID::OBJ_CHARACTER, tempChang);*/
	//Ryo* tempRyo2 = new Ryo();
	//tempRyo->pushSkill("TY", Down, 5, 10, 10, false, true, 3);

	//tempRyo2->Init(2, new Image(), { 550,250 }, 200.f, 100.f, tempImage);
	//objectManager->AddObject(OBJID::OBJ_CHARACTER, tempRyo2);

	//tempRyo->SetEnemy(tempRyo2);
	//tempRyo2->SetEnemy(tempRyo);






	//Chang Character Test//
	// Chang* tempChang = new Chang();
	// tempChang->InitCollider();
	// objectManager->AddObject(OBJID::OBJ_CHARACTER, tempChang);
	//Ryo* tempRyo2 = new Ryo();
	//tempRyo->pushSkill("TY", Down, 5, 10, 10, false, true, 3);

	//tempRyo2->Init(2, new Image(), { 550,250 }, 200.f, 100.f, tempImage);
	//objectManager->AddObject(OBJID::OBJ_CHARACTER, tempRyo2);

	//tempRyo->SetEnemy(tempRyo2);
	//tempRyo2->SetEnemy(tempRyo);




	if (collisionManager = CollisionManager::GetInstance())
	{
		collisionManager->Init();
	}

	GameManager::GetInstance()->Init();
}

void MainGame::Release()
{
	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	if (UI)
		UI->Release();

	GameManager::GetInstance()->Release();


	if (timerManager)
		timerManager->Release();

	ReleaseDC(g_hWnd, hdc);

	if (KOFKeyManager* kofKeyMgr = KOFKeyManager::GetInstance())
		kofKeyMgr->Release();

	if (KeyManager* keyMgr = KeyManager::GetInstance())
		keyMgr->Release();

	if (objectManager)
		objectManager->Release();

	if (collisionManager)
		collisionManager->Release();

	if (effectManager)
		effectManager->Release();
}

void MainGame::Update()
{
	float TimeDelta = timerManager->GetTimeDelta(TEXT("Timer60"));

	if (KOFKeyManager* kofKeyMgr = KOFKeyManager::GetInstance())
		kofKeyMgr->Update(TimeDelta);

	if (objectManager)
		objectManager->Update(TimeDelta);

	GameManager::GetInstance()->Update(TimeDelta);


	if (collisionManager)
		collisionManager->Update(TimeDelta);

	if (effectManager)
		effectManager->Update(TimeDelta);
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backBuffer->Render(hdc);

	GameManager::GetInstance()->Render(hBackBufferDC);

	if (objectManager)
		objectManager->Render(hBackBufferDC);

#ifdef _DEBUG
	if (collisionManager)
		collisionManager->Render(hBackBufferDC);
#endif

	if (effectManager)
		effectManager->Render(hBackBufferDC);
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
