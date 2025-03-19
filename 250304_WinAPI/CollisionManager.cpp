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
	UpdatePivot(TimeDelta);

	//캐릭터와 캐릭터끼리 충돌...

	RECT		rc{};

	for (auto& Dest : CollisionList[OBJ_CHARACTER])
	{
		for (auto& Sour : CollisionList[OBJ_CHARACTER])
		{
			if (Dest == Sour)
				continue;

			FPOINT SourMin = { Sour->GetWorldPos().x - (Sour->GetSize().x / 2.f), Sour->GetWorldPos().y - (Sour->GetSize().y / 2.f) };
			FPOINT SourMax = { Sour->GetWorldPos().x + (Sour->GetSize().x / 2.f), Sour->GetWorldPos().y + (Sour->GetSize().y / 2.f) };
						
			FPOINT DestMin = { Dest->GetWorldPos().x - (Dest->GetSize().x / 2.f), Dest->GetWorldPos().y - (Dest->GetSize().y / 2.f) };
			FPOINT DestMax = { Dest->GetWorldPos().x + (Dest->GetSize().x / 2.f), Dest->GetWorldPos().y + (Dest->GetSize().y / 2.f) };
						
			bool bCollision = false;

			if (SourMax.x > DestMin.x
				&& SourMin.x < DestMax.x
				&& SourMin.y > DestMax.y
				&& SourMax.y < DestMin.y)
			{
				bCollision = true;
			}

			if (bCollision)
			{
				//TODO 점프가있다면 수정하기
			 
				//얼마나 깊이 들어왔는지 확인 /점프제외
				float overlapWidth = min(SourMax.x, DestMax.x) - max(SourMin.x, DestMin.x);
				float pushAmount = overlapWidth / 2.0f;

				FPOINT newSourPos = Sour->GetWorldPos();
				FPOINT newDestPos = Dest->GetWorldPos();

				if (SourMin.x < DestMin.x) {
					// Sour가 Dest의 왼쪽에 있는 경우
					newSourPos.x -= pushAmount;
					newDestPos.x += pushAmount;
				}
				else {
					// Sour가 Dest의 오른쪽에 있는 경우
					newSourPos.x += pushAmount;
					newDestPos.x -= pushAmount;
				}

				Sour->GetOwner()->SetPos(newSourPos);
				Dest->GetOwner()->SetPos(newDestPos);
			}
		}
	}

	//Sour와 Dest의 위치를 업데이트 했으니 

	UpdatePivot(TimeDelta); //별로 맘에 들지는 않는다..

	DebugLineUpdate(TimeDelta);
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
	DebugLineRender(hdc);
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

bool CollisionManager::LineTraceByObject(HitResult& hitResult, OBJID eObjID, FPOINT start, FPOINT end, GameObject* Owner, bool bIgnoreSelf, bool bDebugDraw, float DebugDuration, COLORREF DebugColor)
{
	if (bDebugDraw)
	{
		Line* line = new Line(start, end);
		line->bDebugDraw = bDebugDraw;
		line->DebugDuration = DebugDuration;
		line->DebugColor = DebugColor;
		LineList.push_back(line);
	}

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

void CollisionManager::DebugLineRender(HDC hdc)
{
	for (auto iter = LineList.begin();
		iter != LineList.end(); )
	{
		if ((*iter)->bDebugDraw)
		{
			HPEN hPen = CreatePen(PS_SOLID, 4, (*iter)->DebugColor); // RGB(0, 255, 0) -> 초록색
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // 현재 DC에 펜을 설정

			(*iter)->Render(hdc);

			// 사용한 펜을 원래대로 복원
			SelectObject(hdc, hOldPen);

			// 펜 메모리 해제
			DeleteObject(hPen);
		}
		++iter;
	}
}

void CollisionManager::UpdatePivot(float TimeDelta)
{
	//부모 오브젝트를 기준으로 Collider의 위치 갱신
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

void CollisionManager::DebugLineUpdate(float TimeDelta)
{
	for (auto iter = LineList.begin();
		iter != LineList.end(); )
	{
		if ((*iter)->bDebugDraw)
		{
			(*iter)->Update(TimeDelta);

			++iter;
		}
		else
		{
			delete* iter;
			iter = LineList.erase(iter);
		}
	}
}
