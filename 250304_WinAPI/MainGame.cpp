#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "KOFKeyManager.h"
/*
	�ǽ�1. �̿��� ���� ������
	�ǽ�2. ��� �ٲٱ� (ŷ���� �ִϸ��̼� ���)
*/

void MainGame::Init()
{
	// ���κ��尡 ���� �ִ� ���ػ� Ÿ�̸��� �������� ������ �Լ�
	QueryPerformanceCounter(&m_CurrentTime);		// 1000
	QueryPerformanceCounter(&m_OldTime);			// 1020	
	QueryPerformanceCounter(&m_OriginTime);			// 1030	

	// ���ػ� Ÿ�̸��� ���ļ��� ������ �Լ�, ���ļ��� cpu �ʴ� Ŭ���� �ֱ⸦ ����
	QueryPerformanceFrequency(&m_CpuTick);			// 1,600,000

	m_bRunning = true;

	hdc = GetDC(g_hWnd);
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);
	}

	iori = new KOF_Iori();
	iori->Init();
}

void MainGame::Release()
{
	if (iori)
	{
		iori->Release();
		delete iori;
		iori = nullptr;
	}

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::UpdateTimer()
{
	QueryPerformanceCounter(&m_CurrentTime);
	// 2000	//	3000 // 4000 // 5000

	if (m_CurrentTime.QuadPart - m_OriginTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_OriginTime = m_CurrentTime;
	}

	m_fTimeDelta = float(m_CurrentTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;

	if (!m_bRunning)
		m_fTimeDelta = 0.f;

	m_OldTime = m_CurrentTime;
}

void MainGame::Update()
{
	float fTimeDelta = GetTimeDelta();

	m_fTimeAcc += fTimeDelta;

	if (iori)
		iori->Update();

	KOFKeyManager::GetInstance()->Update();

}

void MainGame::Render()
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);
	iori->Render(hBackBufferDC);

	++m_iNumDraw;

	// ����ۿ� �ִ� ������ ���� hdc�� ����
	HDC tempDC = GetDC(g_hWnd);
	backBuffer->Render(tempDC);

	
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
	: m_fTimeDelta(0.f)
	, m_bRunning(false)
	, m_fTimeScale(1.f)
{
	ZeroMemory(&m_CurrentTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OriginTime, sizeof(LARGE_INTEGER));
}

MainGame::~MainGame()
{
}
