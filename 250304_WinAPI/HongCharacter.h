#pragma once
#include "Character.h"

class Collider;

class HongCharacter : public Character
{
private:
	Collider* collider;

public:
	void InitCollider();
	virtual void Update(float TimeDelta) override;
	virtual void Render(HDC hdc) override;

	//Hong Interface
	HongCharacter();
	~HongCharacter();

private:
	void Load();
};

