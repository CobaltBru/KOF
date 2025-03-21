#include"Character.h"
#pragma once

class Image;
class Collider;
class Chang:public Character
{
	
public:
	Chang();
	~Chang() = default;
	void SetPixel(int pixel) { pixels.push_back(pixel); }
	void Jump(float deltaTime);
	void CheckMaxFrame();
	void InitCollider();

protected:

	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	
private:
	float dashTime;
	int sitFrame = 3;
	float currentTime;
	Collider* collider;
	vector<int> pixels;



};

