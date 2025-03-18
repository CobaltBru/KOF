#pragma once
#include "GameObject.h"

class Image;
class KOF_Iori;
class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	FPOINT mousePos;
	wchar_t szText[128];

	Image* backBuffer;
	Image* backGround;
	KOF_Iori* iori;


	TCHAR		m_szFPS[64];	// 멀티 바이트 기반에서는 CHAR로 유니 코드 기반에서는 유니코드로 처리해주는 매크로
	//int			m_iFPS;
	//DWORD		m_dwTime;

	
	LARGE_INTEGER m_CurrentTime;
	LARGE_INTEGER m_OldTime;
	LARGE_INTEGER m_OriginTime;
	LARGE_INTEGER m_CpuTick;
	float m_fTimeDelta;
	float m_fTimeScale;
	bool m_bRunning;

	unsigned int m_iFPS = 0;
	float m_fTimeAcc = 0.f;
	unsigned int m_iNumDraw = 0;
public:
	float GetTimeDelta(void) { return m_fTimeDelta * m_fTimeScale; }

	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();	
	void UpdateTimer();
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

