#pragma once
#include "GameObject.h"

class Image;
class TimerManager;
class ObjectManager;
class UserInterface;
class CollisionManager;
class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	
	Image* backBuffer;
	TimerManager* timerManager;
	ObjectManager* objectManager;
	CollisionManager* collisionManager;

	UserInterface* UI;

public:
	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();	
	void Update();	
	void Render();

	float GetTimeDelta(const wchar_t* pTimerTag);
	void AddTimer(const wchar_t* pTimerTag);
	void UpdateTimer(const wchar_t* pTimerTag);

	void DrawQuadraticBezier(HDC hdc, FPOINT p0, FPOINT p1, FPOINT p2) {
		MoveToEx(hdc, p0.x, p0.y, NULL);  // 시작점 설정

		for (double t = 0; t <= 1; t += 0.01) {  // t 값을 0에서 1까지 변화시키면서 점을 그림
			double u = 1 - t;
			int x = (int)(u * u * p0.x + 2 * u * t * p1.x + t * t * p2.x);
			int y = (int)(u * u * p0.y + 2 * u * t * p1.y + t * t * p2.y);
			LineTo(hdc, x, y);
		}
	}
	void UpdateCharacterPosition(float TimeDelta, FPOINT P0, FPOINT P1, FPOINT P2);
	class Character* test;
	float CurrentTime = 0.f;
	MainGame();
	~MainGame();
};

