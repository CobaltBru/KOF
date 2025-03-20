#include "Kusanagi.h"
#include "Collider.h"
#include "CollisionManager.h"

Kusanagi::Kusanagi()
{

}

Kusanagi::~Kusanagi()
{
}



void Kusanagi::Update(float TimeDelta)
{
	__super::Update(TimeDelta);
}

void Kusanagi::Render(HDC hdc)
{
	wchar_t szText[255] = L"";
	switch (currentState)
	{
	case Character::STATE::IDLE:
		wsprintf(szText, TEXT("STATE::IDLE"));
		break;
	case Character::STATE::BACK:
		wsprintf(szText, TEXT("STATE::BACK"));
		break;
	case Character::STATE::WALK:
		wsprintf(szText, TEXT("STATE::WALK"));
		break;
	case Character::STATE::DOWN:
		wsprintf(szText, TEXT("STATE::DOWN"));
		break;
	case Character::STATE::DASH:
		wsprintf(szText, TEXT("STATE::DASH"));
		break;
	case Character::STATE::BACKDASH:
		wsprintf(szText, TEXT("STATE::BACKDASH"));
		break;
	case Character::STATE::SKILL:
		wsprintf(szText, TEXT("STATE::SKILL"));
		break;
	case Character::STATE::PROCESS:
		wsprintf(szText, TEXT("STATE::PROCESS"));
		break;
	case Character::STATE::BLOCKUPPER:
		wsprintf(szText, TEXT("STATE::BLOCKUPPER"));
		break;
	case Character::STATE::BLOCKLOWER:
		wsprintf(szText, TEXT("STATE::BLOCKLOWER"));
		break;
	}
	TextOut(hdc, pos.x - 75, pos.y - 60, szText, wcslen(szText));

	__super::Render(hdc);
}

void Kusanagi::InitCollider()
{
	collider = new Collider(this, { 30.f, 80.f }, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);
}
