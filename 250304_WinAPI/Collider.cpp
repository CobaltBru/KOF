#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject* Owner, FPOINT Pos, FPOINT Size, COLLIDER_TYPE Type)
	: Owner(Owner), Pos(Pos), Size(Size), bHit(false), PrevWorldPos({ 0.f,0.f })
	, ColliderType(Type)
{
}

Collider::~Collider()
{
}

GameObject* Collider::GetOwner()
{
	return Owner;
}

void Collider::DebugRender(bool bDuration, float Duration)
{
	this->DebugDuration = Duration;
	this->bDuration = bDuration;
	CurrentTime = 0.f;
	bDebugDraw = true;
}

void Collider::DebugRender(bool bDraw)
{
	bDebugDraw = bDraw;
}

bool Collider::Update(float TimeDelta)
{
	PrevWorldPos = WorldPos;

	//TODO 변경된 Owner의 위치로 콜라이더의 Pos를 업데이트
	WorldPos.x = Owner->GetPos().x + Pos.x;
	WorldPos.y = Owner->GetPos().y + Pos.y;

	if (!bDuration)
		return false;
	
	CurrentTime += TimeDelta;
	if (CurrentTime >= DebugDuration)
	{
		CurrentTime = 0.f;
		bDebugDraw = false;
		bDuration = false;
	}
	return true;
}

void Collider::Render(HDC hdc)
{
	FPOINT HalfSize = { Size.x / 2.f, Size.y / 2.f };

	HPEN hPen;

	if (!bHit)
	{
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); // RGB(0, 255, 0) -> 초록색
	}
	else
	{
		hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // RGB(0, 255, 0) -> 초록색
	}
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // 현재 DC에 펜을 설정

	switch (ColliderType)
	{
	case COLLIDER_TYPE::Sphere:
		Ellipse(hdc, (int)(WorldPos.x - HalfSize.x), (int)(WorldPos.y - HalfSize.y), (int)(WorldPos.x + HalfSize.x), (int)(WorldPos.y + HalfSize.y));
		break;
	case COLLIDER_TYPE::Rect:
		DrawRectLine(hdc, HalfSize);
		break;
	}

	// 사용한 펜을 원래대로 복원
	SelectObject(hdc, hOldPen);

	// 펜 메모리 해제
	DeleteObject(hPen);
}

void Collider::DrawRectLine(HDC hdc, FPOINT HalfSize)
{
	MoveToEx(hdc, WorldPos.x - HalfSize.x, WorldPos.y - HalfSize.y, NULL);
	LineTo(hdc, WorldPos.x + HalfSize.x, WorldPos.y - HalfSize.y);
	LineTo(hdc, WorldPos.x + HalfSize.x, WorldPos.y + HalfSize.y);
	LineTo(hdc, WorldPos.x - HalfSize.x, WorldPos.y + HalfSize.y);
	LineTo(hdc, WorldPos.x - HalfSize.x, WorldPos.y - HalfSize.y);
}
