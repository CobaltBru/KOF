#pragma once
#include "Character.h"

class Collider;

class Mai : public Character
{
public:
	void InitCollider();
	void Render(HDC hdc);
private:
	Collider* collider;


};

