#pragma once
#include "Singleton.h"
#include "config.h"

class Collider;
class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Init();
	void AddObject(OBJID eID, Collider* collider);

	void Update(float TimeDelta);
	void Render(HDC hdc);
	void Release();

private:
	list<Collider*>	CollisionList[OBJ_END];

};
