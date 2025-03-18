#pragma once
#include "GameObject.h"

class Image;
class KOF_Iori;
class TimerManager;
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
	TimerManager* timerManager;
	
public:
	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();	
	void Update();	
	void Render();

	float GetTimeDelta(const wchar_t* pTimerTag);
	void AddTimer(const wchar_t* pTimerTag);
	void UpdateTimer(const wchar_t* pTimerTag);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

