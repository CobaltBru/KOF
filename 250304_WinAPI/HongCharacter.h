#pragma once
#include "Character.h"

class Image;
class Collider;

struct Animation
{
	float PlayTime;
	int MaxFrame;

	void PlayAnimation(float TimeDelta);

	void Render(HDC hdc);
	
	vector<Image*> Images;

	void Release();
};

class HongCharacter : public Character
{
private:
	float moveSpeed;
	float currentTime;

	Collider* collider;

	vector<Animation*> Animations;

public:
	//void Init();
	void InitCollider();
	void Release();
	virtual void Update(float TimeDelta) override;
	virtual void Render(HDC hdc) override;


	void CheckMaxFrame();
	//Hong Interface
	HongCharacter();
	~HongCharacter();

private:
	void Load();
};

