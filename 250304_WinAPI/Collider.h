#pragma once
#include "config.h"
enum class COLLIDER_TYPE
{
	Sphere,
	Rect,
	ColliderEnd
};

class GameObject;

class Collider
{
public:
	Collider(GameObject* Owner, FPOINT Pos, FPOINT Size);
	~Collider();

public:
	GameObject* GetOwner();
	void DebugRender(COLLIDER_TYPE DrawType, bool bDuration = false, float Duration = 3.f);
	bool Update(float TimeDelta);
	void Render(HDC hdc);

	inline bool IsHit() {
		return bHit;
	};
	inline bool IsDraw() {
		return bDebugDraw;
	}
	//void OnComponentBeginOverlap();
private:
	FPOINT Pos; //부모 위치로부터 상대적인 위치
	FPOINT Size;

	GameObject* Owner;

	//Debug
	COLLIDER_TYPE DrawType;
	float CurrentTime;
	float DebugDuration;
	bool bDebugDraw;
	bool bDuration;

	bool bHit;
};

