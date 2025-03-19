#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject* Owner, FPOINT Pos, FPOINT Size)
	: Owner(Owner), Pos(Pos), Size(Size), bHit(false)
{
}

Collider::~Collider()
{
}

GameObject* Collider::GetOwner()
{
	return Owner;
}

void Collider::DebugRender(COLLIDER_TYPE DrawType, bool bDuration, float Duration)
{
	this->DrawType = DrawType;
	this->DebugDuration = Duration;
	this->bDuration = bDuration;
	CurrentTime = 0.f;
	bDebugDraw = true;
}

bool Collider::Update(float TimeDelta)
{
	if (!bDuration)
		return false;
	
	CurrentTime += TimeDelta;
	if (CurrentTime >= DebugDuration)
	{
		CurrentTime = 0.f;
		bDuration = false;
	}
	return true;
}

void Collider::Render(HDC hdc)
{
	FPOINT HalfSize = { Size.x / 2.f, Size.y / 2.f };

	switch (DrawType)
	{
	case COLLIDER_TYPE::Sphere:
		Ellipse(hdc, (int)(Pos.x - HalfSize.x), (int)(Pos.y - HalfSize.y), (int)(Pos.x + HalfSize.x), (int)(Pos.y + HalfSize.y));
		break;
	case COLLIDER_TYPE::Rect:
		Rectangle(hdc, (int)(Pos.x - HalfSize.x), (int)(Pos.y - HalfSize.y), (int)(Pos.x + HalfSize.x), (int)(Pos.y + HalfSize.y));
		break;
	}
}
