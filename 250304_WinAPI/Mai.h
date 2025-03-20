#pragma once
#include "Character.h"

class Collider;

class Mai : public Character
{
public:
	void InitCollider();

private:
	Collider* collider;


};

