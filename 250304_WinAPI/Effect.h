#pragma once
#include "config.h"

class Image;
class Effect
{
public:
	Effect();
	~Effect();

	void Init(Image* image, FPOINT position,bool bFilp);
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Release();

	bool IsDead() const { return bDead; }
private:
	bool bDead;
	bool bFilp;
	float currentTime;
	float currentFrame;
	FPOINT pos;
	Image* image;
};

