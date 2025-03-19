#pragma once
#include "Character.h"

class Ryo : public Character
{
public:
	Ryo();
	~Ryo() = default;

	virtual void Update(float deltaTime) override;
private:
	float dashTime;
	int sitFrame = 3;
	float currentTime;
};

