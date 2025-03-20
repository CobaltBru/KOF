#pragma once
#include "Character.h"

class Ryo : public Character
{
public:
	Ryo();
	~Ryo() = default;

	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
	void Move(float deltaTime);

	void SetPixel(int pixel) { pixels.push_back(pixel); }

	void CheckMaxFrame();
private:
	float currentTime;

	float aDashTime;
	float bDashTime;

	bool bCheckPreBackDash = false;
	bool bBackDash = false;

	int gravity = 3;
	int dy = 0;
	
	vector<int> pixels;
};

