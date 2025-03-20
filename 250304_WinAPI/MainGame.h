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
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();	
	void Update();	
	void Render();

	float GetTimeDelta(const wchar_t* pTimerTag);
	void AddTimer(const wchar_t* pTimerTag);
	void UpdateTimer(const wchar_t* pTimerTag);

	void DrawQuadraticBezier(HDC hdc, FPOINT p0, FPOINT p1, FPOINT p2) {
		MoveToEx(hdc, p0.x, p0.y, NULL);  // ������ ����

		for (double t = 0; t <= 1; t += 0.01) {  // t ���� 0���� 1���� ��ȭ��Ű�鼭 ���� �׸�
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

