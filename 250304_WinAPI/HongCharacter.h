#pragma once
#include "GameObject.h"
#include "KOF_Iori.h"

class Image;
class Collider;

struct Animation
{
	float PlayTime;
	int MaxFrame;

	void PlayAnimation(float TimeDelta);


	void Render(HDC hdc);
	
	vector<Image*> Images;
};

class HongCharacter : public GameObject
{
private:
	float moveSpeed;
	Image* image;
	int elapsedFrame;
	int currAnimaionFrame;	// 0 ~ 8

	bool characterKey[(int)EMoveKey::END] = { 0, };

	float stepTime = 0.f;
	float currentTime;

	Image* attackImage;

	bool bAttack = false;

	Collider* collider;

	vector<Animation*> Animations;
public:
	void Init();
	void Release();
	void Update(float TimeDelta);
	void Render(HDC hdc);


	void Move();

	void KeyUpdate(float TimeDelta);
	void StateUpdate();
	void Attack();

	//Hong Interface
	void SetPos(FPOINT pos) { this->pos = pos; }
	HongCharacter();
	~HongCharacter();

private:
	void Load();
};

