#pragma once
#include "Singleton.h"
#include "config.h"
class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Init();
	void Update(float TimeDelta);
	void Render(HDC hdc);
	void Release();
private:

};

