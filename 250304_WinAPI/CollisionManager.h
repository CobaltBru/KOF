#pragma once
#include "Singleton.h"
#include "config.h"

class Collider;
class GameObject;

struct HitResult
{
	vector<GameObject*> Actors;


};

struct Line
{
	Line(FPOINT st, FPOINT ed)
		: start(st), end(ed)
	{

	}
	FPOINT start;
	FPOINT end;
};

class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Init();
	void AddObject(OBJID eID, Collider* collider);

	void Update(float TimeDelta);
	void Render(HDC hdc);
	void Release();

	//eObjID�׷����� ���̸� ���!
	bool LineTraceByObject(HitResult& hitResult, OBJID eObjID, FPOINT start, FPOINT end, GameObject* Owner, bool bIgnoreSelf = true);

private:
	// CCW �˰����� ����Ͽ� �� ���� ������ ���
	float CCW(const FPOINT& p, const FPOINT& q, const FPOINT& r) {
		return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
	}

	// �� ������ �����ϴ��� Ȯ��
	bool DoLinesIntersect(const FPOINT& p1, const FPOINT& p2, const FPOINT& q1, const FPOINT& q2) {
		float ccw1 = CCW(p1, p2, q1);
		float ccw2 = CCW(p1, p2, q2);
		float ccw3 = CCW(q1, q2, p1);
		float ccw4 = CCW(q1, q2, p2);

		// ���� ����
		return (ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0);
	}

	// �簢�� ���ο� ���� ���ԵǴ��� Ȯ��
	bool IsPointInsideRect(const FPOINT& p, const FPOINT& rectMin, const FPOINT& rectMax) {
		return p.x >= rectMin.x && p.x <= rectMax.x && p.y >= rectMin.y && p.y <= rectMax.y;
	}
private:
	list<Collider*>	CollisionList[OBJ_END];
	list<Line*> LineList;
};
