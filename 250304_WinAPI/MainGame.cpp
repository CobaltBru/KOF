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
#include "Chang.h"
#include "GameManager.h"
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

	UI = UserInterface::GetInstance();
	UI->Init();

	timerManager = TimerManager::GetInstance();
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
}

void MainGame::Render()
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backBuffer->Render(hdc);

	GameManager::GetInstance()->Render(hBackBufferDC);

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
