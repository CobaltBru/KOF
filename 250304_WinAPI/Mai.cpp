#include "Mai.h"
#include "Collider.h"
#include "CollisionManager.h"

void Mai::InitCollider()
{
	collider = new Collider(this, { 55.f, 50.f }, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);
}
