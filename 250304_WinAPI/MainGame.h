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

	MainGame();
	~MainGame();
};

