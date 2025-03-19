#include "CollisionManager.h"
#include "Collider.h"
void CollisionManager::Init()
{

}

void CollisionManager::AddObject(OBJID eID, Collider* collider)
{
	if ((eID >= OBJ_END) || (nullptr == collider))
		return;

	CollisionList[eID].push_back(collider);
}

void CollisionManager::Update(float TimeDelta)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = CollisionList[i].begin();
			iter != CollisionList[i].end(); )
		{
			if ((*iter)->IsDraw() == false)
				continue;

			(*iter)->Update(TimeDelta);
			++iter;
		}
	}
}

void CollisionManager::Render(HDC hdc)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = CollisionList[i].begin();
			iter != CollisionList[i].end(); )
		{
			if ((*iter)->IsDraw() == false)
				continue;

			(*iter)->Render(hdc);
			++iter;
		}
	}
}

void CollisionManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : CollisionList[i])
		{
			if (iter == nullptr)
				continue;

			delete iter;
		}

		CollisionList[i].clear();
	}
	ReleaseInstance();
}
