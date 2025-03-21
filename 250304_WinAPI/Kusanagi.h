#pragma once
#include "Character.h"

class Collider;
class Kusanagi : public Character
{

private:
	Collider* collider;
public:
	Kusanagi();
	~Kusanagi();

	
	virtual void Update(float TimeDelta) override;
	virtual void Render(HDC hdc) override;
	void InitCollider();
};

