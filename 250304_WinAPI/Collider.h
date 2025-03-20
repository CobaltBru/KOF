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
	Collider(GameObject* Owner, FPOINT Pos, FPOINT Size, COLLIDER_TYPE Type);
	~Collider();

public:
	GameObject* GetOwner();
	void DebugRender(bool bDuration, float Duration);
	void DebugRender(bool bDraw);
	bool Update(float TimeDelta);
	void Render(HDC hdc);
	
public:
	//void OnComponentBeginOverlap();

public:
	inline FPOINT GetPrevWorldPos() { return PrevWorldPos; }
	inline FPOINT GetSize() { return Size; }
	inline FPOINT GetWorldPos() { return WorldPos; }
	inline FPOINT GetPivot() const { return Pivot; }
	inline bool IsHit() {
		return bHit;
	}
	inline bool IsDraw() {
		return bDebugDraw;
	}
	inline void SetHit(bool bHit) {
		this->bHit = bHit;
	}

private:
	void DrawRectLine(HDC hdc, FPOINT HalfSize);
	bool DebugUpdate(float TimeDelta);

private:
	FPOINT Pivot; //�θ� ��ġ�κ��� ������� ��ġ
	FPOINT WorldPos; //���� ������

	FPOINT PrevWorldPos; //���� �������� ���� ������
	FPOINT Size;

	GameObject* Owner;
	COLLIDER_TYPE ColliderType;

	//Debug
	float CurrentTime;
	float DebugDuration;
	bool bDebugDraw;
	bool bDuration;
	bool bHit;
};

