#include "Mai.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Image.h"

void Mai::InitCollider()
{
	collider = new Collider(this, { 55.f, 80.f }, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);
}

void Mai::Render(HDC hdc)
{
	if (currentState == STATE::PROCESS)
	{
		skillSet[currentSkill].image->Render(hdc, pos.x - 45, pos.y, framecnt, screenWay);
	}
	else
	{
		if (screenWay)
		{
			images[getIndex()].Render(hdc, pos.x, pos.y + 30.f, framecnt, screenWay);
		}
		else
		{
			//images[getIndex()].Render(hdc, pos.x - 35, pos.y - 55, framecnt, screenWay);
		}
	}
}
