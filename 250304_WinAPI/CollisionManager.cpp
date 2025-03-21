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

	//ĳ���Ϳ� ĳ���ͳ��� �浹...
	 
	RECT		rc{};

	for (auto& Dest : CollisionList[OBJ_CHARACTER])
	{
		for (auto& Sour : CollisionList[OBJ_CHARACTER])
		{
			if (Dest == Sour)
				continue;
			if (Dest->GetOwner()->IsActive() == false || Sour->GetOwner()->IsActive() == false)
				continue;

			FPOINT SourMin = { Sour->GetWorldPos().x - (Sour->GetSize().x / 2.f), Sour->GetWorldPos().y - (Sour->GetSize().y / 2.f) };
			FPOINT SourMax = { Sour->GetWorldPos().x + (Sour->GetSize().x / 2.f), Sour->GetWorldPos().y + (Sour->GetSize().y / 2.f) };
						
			FPOINT DestMin = { Dest->GetWorldPos().x - (Dest->GetSize().x / 2.f), Dest->GetWorldPos().y - (Dest->GetSize().y / 2.f) };
			FPOINT DestMax = { Dest->GetWorldPos().x + (Dest->GetSize().x / 2.f), Dest->GetWorldPos().y + (Dest->GetSize().y / 2.f) };
						
			bool bCollision = false;

			if (SourMax.x > DestMin.x
				&& SourMin.x < DestMax.x
				//TODO Y�� ���ð�� 
				/*&& SourMin.y > DestMax.y
				&& SourMax.y < DestMin.y*/)
			{
				bCollision = true;
			}

			if (bCollision)
			{
				//TODO �������ִٸ� �����ϱ�
			 
				//�󸶳� ���� ���Դ��� Ȯ�� /��������
				float overlapWidth = min(SourMax.x, DestMax.x) - max(SourMin.x, DestMin.x);
				float pushAmount = (overlapWidth / 2.0f) * (TimeDelta / FixedTimeStep);

				FPOINT newSourPos = Sour->GetOwner()->GetPos();
				FPOINT newDestPos = Dest->GetOwner()->GetPos();

				if (SourMin.x < DestMin.x) {
					// Sour�� Dest�� ���ʿ� �ִ� ���
					newSourPos.x -= pushAmount;
					newDestPos.x += pushAmount;
				}
				else {
					// Sour�� Dest�� �����ʿ� �ִ� ���
					newSourPos.x += pushAmount;
					newDestPos.x -= pushAmount;
				}

				Sour->GetOwner()->SetPos(newSourPos);
				Dest->GetOwner()->SetPos(newDestPos);
			}
		}
	}

	//Sour�� Dest�� ��ġ�� ������Ʈ ������ 

	UpdatePivot(TimeDelta); //���� ���� ������ �ʴ´�..

	DebugLineUpdate(TimeDelta);
}

void CollisionManager::Render(HDC hdc)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = CollisionList[i].begin();
			iter != CollisionList[i].end(); )
		{
			if ((*iter)->IsDraw() == true && (*iter)->GetOwner()->IsActive())
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

		// ���а� �簢���� �� ���� �����ϴ��� Ȯ��
		for (int i = 0; i < 4; ++i) {
			if (DoLinesIntersect(start, end, rect[i][0], rect[i][1]))
			{
				bCollision = true;
				break;
				//return true; // �����ϴ� ���
			}
		}

		// ������ �� ������ �簢�� ���ο� ���ԵǴ��� Ȯ��
		if (IsPointInsideRect(start, { pos.x - halfSize.x, pos.y - halfSize.y }, { pos.x + halfSize.x, pos.y + halfSize.y })
			|| IsPointInsideRect(end, { pos.x - halfSize.x, pos.y - halfSize.y }, { pos.x + halfSize.x, pos.y + halfSize.y }))
		{
			bCollision = true;

			//return true; // ������ �� ���� �簢�� �ȿ� �ִ� ���
		}

		//�浹�� �Ǿ��� �ڽ��� �������� �ʰų�
		if (bCollision)
		{
			if (Owner != (*iter)->GetOwner())
			{
				hitResult.Actors.push_back((*iter)->GetOwner());

				(*iter)->SetHit(true);
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
			HPEN hPen = CreatePen(PS_SOLID, 4, (*iter)->DebugColor); // RGB(0, 255, 0) -> �ʷϻ�
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen); // ���� DC�� ���� ����

			(*iter)->Render(hdc);

			// ����� ���� ������� ����
			SelectObject(hdc, hOldPen);

			// �� �޸� ����
			DeleteObject(hPen);
		}
		++iter;
	}
}

void CollisionManager::UpdatePivot(float TimeDelta)
{
	//�θ� ������Ʈ�� �������� Collider�� ��ġ ����
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
