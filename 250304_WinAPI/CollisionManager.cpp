#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"
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
			if (*iter == nullptr)
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
			if ((*iter)->IsDraw() == true)
				(*iter)->Render(hdc);
			++iter;
		}
	}

	for (auto iter = LineList.begin();
		iter != LineList.end(); )
	{
		MoveToEx(hdc, (*iter)->start.x, (*iter)->start.y, NULL);
		LineTo(hdc, (*iter)->end.x, (*iter)->end.y);

		++iter;
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

	for (auto& iter : LineList)
	{
		if (iter == nullptr)
			continue;

		delete iter;
	}
	LineList.clear();

	ReleaseInstance();
}

bool CollisionManager::LineTraceByObject(HitResult& hitResult, OBJID eObjID, FPOINT start, FPOINT end, GameObject* Owner, bool bIgnoreSelf)
{
	Line* line = new Line(start, end);
	LineList.push_back(line);

	for (auto iter = CollisionList[eObjID].begin();
		iter != CollisionList[eObjID].end(); )
	{
		bool bCollision = false;

		FPOINT pos = (*iter)->GetWorldPos();
		FPOINT halfSize = { (*iter)->GetSize().x / 2.f, (*iter)->GetSize().y / 2.f };

		FPOINT rect[4][2] = {
			// top (lt rt)
			{FPOINT{pos.x - halfSize.x, pos.y - halfSize.y }, FPOINT{pos.x + halfSize.x, pos.y - halfSize.y}},
			// right (rt rb)
			{FPOINT{pos.x + halfSize.x, pos.y + halfSize.y}, FPOINT{pos.x + halfSize.x, pos.y + halfSize.y}},
			// bottom (rb lb)
			{FPOINT{pos.x + halfSize.x, pos.y + halfSize.y}, FPOINT{pos.x - halfSize.x, pos.y + halfSize.y}},
			// left (lb lt)
			{FPOINT{pos.x - halfSize.x, pos.y + halfSize.y}, FPOINT{pos.x - halfSize.x, pos.y - halfSize.y}}
		};

		// 선분과 사각형의 각 변이 교차하는지 확인
		for (int i = 0; i < 4; ++i) {
			if (DoLinesIntersect(start, end, rect[i][0], rect[i][1]))
			{
				bCollision = true;
				break;
				//return true; // 교차하는 경우
			}
		}

		// 선분의 두 끝점이 사각형 내부에 포함되는지 확인
		if (IsPointInsideRect(start, { pos.x - halfSize.x, pos.y - halfSize.y }, { pos.x + halfSize.x, pos.y + halfSize.y })
			|| IsPointInsideRect(end, { pos.x - halfSize.x, pos.y - halfSize.y }, { pos.x + halfSize.x, pos.y + halfSize.y }))
		{
			bCollision = true;

			//return true; // 선분의 한 점이 사각형 안에 있는 경우
		}

		//충돌이 되었고 자신을 무시하지 않거나
		if (bCollision)
		{
			if (Owner != (*iter)->GetOwner())
			{
				hitResult.Actors.push_back((*iter)->GetOwner());
			}
			else
			{
				if (!bIgnoreSelf)
				{
					hitResult.Actors.push_back((*iter)->GetOwner());
				}
			}
		}
		++iter;
	}

	if (!hitResult.Actors.empty())
		return true;

	return false;
}
