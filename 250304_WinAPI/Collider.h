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
	inline bool IsHit() {
		return bHit;
	};
	inline bool IsDraw() {
		return bDebugDraw;
	}

private:
	void DrawRectLine(HDC hdc, FPOINT HalfSize);
	bool DebugUpdate(float TimeDelta);

private:
	FPOINT Pos; //�θ� ��ġ�κ��� ������� ��ġ
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

