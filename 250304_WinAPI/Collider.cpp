#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject* Owner, FPOINT Pivot, FPOINT Size, COLLIDER_TYPE Type)
	: Owner(Owner), Pivot(Pivot), Size(Size), bHit(false), PrevWorldPos({ 0.f,0.f })
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
	this->bDuration = bDebugDraw;
	CurrentTime = 0.f;
	this->bDebugDraw = true;
}

void Collider::DebugRender(bool bDraw)
{
	bDebugDraw = bDraw;
}

bool Collider::Update(float TimeDelta)
{
	PrevWorldPos = WorldPos;

	//TODO ����� Owner�� ��ġ�� �ݶ��̴��� Pos�� ������Ʈ
	WorldPos.x = Owner->GetPos().x + Pivot.x;
	WorldPos.y = Owner->GetPos().y + Pivot.y;

	bool bDraw = DebugUpdate(TimeDelta);
	return bDraw;
}

void Collider::Render(HDC hdc)
{
	FPOINT HalfSize = { Size.x / 2.f, Size.y / 2.f };

	HPEN hPen;

	if (!bHit)
	{
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); // RGB(0, 255, 0) -> �ʷϻ�
	}
	else
	{
		hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // RGB(0, 255, 0) -> �ʷϻ�
	}
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // ���� DC�� ���� ����

	switch (ColliderType)
	{
	case COLLIDER_TYPE::Sphere:
		Ellipse(hdc, (int)(WorldPos.x - HalfSize.x), (int)(WorldPos.y - HalfSize.y), (int)(WorldPos.x + HalfSize.x), (int)(WorldPos.y + HalfSize.y));
		break;
	case COLLIDER_TYPE::Rect:
		DrawRectLine(hdc, HalfSize);
		break;
	}

	// ����� ���� ������� ����
	SelectObject(hdc, hOldPen);

	// �� �޸� ����
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

bool Collider::DebugUpdate(float TimeDelta)
{
	if (!bDebugDraw)
		return false;

	if (bDuration)
	{
		CurrentTime += TimeDelta;
		if (CurrentTime >= DebugDuration)
		{
			CurrentTime = 0.f;
			bDebugDraw = false;
		}
	}
	return true;
}
