#pragma once
#include "Character.h"
#include <vector>

class Collider;
class Ryo : public Character
{
public:
	Ryo();
	~Ryo() = default;

	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
	void InitCollider();

	void PushSkipFrame(int frame) { skipFrames.push_back(frame); }

	void Move(float deltaTime);
	void useSkill(string str);
	void SkipSkillFrame();
	void CheckMaxFrame();
private:
	float currentTime;

	float aDashTime;
	float bDashTime;

	bool bCheckPreBackDash = false;
	bool bBackDash = false;

	bool bSkip = false;

	int gravity = 3;
	int dy = 0;
	
	int skipFrame = 4;
	vector<int> skipFrames;
	Collider* collider;
};

