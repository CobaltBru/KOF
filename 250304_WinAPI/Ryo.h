#pragma once
#include "Character.h"

class Ryo : public Character
{
public:
	Ryo();
	~Ryo() = default;

	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	void SetPixel(int pixel) { pixels.push_back(pixel); }

	void CheckMaxFrame();
private:
	float dashTime;
	int sitFrame = 3;
	float currentTime;
	
	vector<int> pixels;
};

