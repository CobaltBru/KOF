#pragma once
#include "GameObject.h"

class Image;
class TimerManager;
class ObjectManager;
class UserInterface;
class CollisionManager;
class EffectManager;
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
	EffectManager* effectManager;

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

	MainGame();
	~MainGame();
};

