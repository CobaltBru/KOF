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


	TCHAR		m_szFPS[64];	// ��Ƽ ����Ʈ ��ݿ����� CHAR�� ���� �ڵ� ��ݿ����� �����ڵ�� ó�����ִ� ��ũ��
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

	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();	
	void UpdateTimer();
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

