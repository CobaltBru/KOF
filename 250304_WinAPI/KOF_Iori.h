#pragma once
#include "GameObject.h"
#include <queue>

enum  EMoveKey : uint8_t
{
	KEYW,
	KEYA,
	KEYS,
	KEYD,
	KEYT,
	KEYY,
	KEYG,
	KEYH,
	END
};

class Image;
class KOF_Iori : public GameObject
{
private:
	FPOINT pos;
	float moveSpeed;
	Image* image;
	int elapsedFrame;
	int currAnimaionFrame;	// 0 ~ 8

	queue<pair<int,float>> keyBuffer;
	bool characterKey[(int)EMoveKey::END] = { 0, };

	float stepTime = 0.f;
	float currentTime;

	Image* attackImage;

	bool bAttack = false;
public:
	void Init();
	void Release();
	void Update(float TimeDelta);
	void Render(HDC hdc);


	void Move();
	
	void KeyUpdate(float TimeDelta);
	void StateUpdate();
	void Attack();

	KOF_Iori();
	~KOF_Iori();
};

