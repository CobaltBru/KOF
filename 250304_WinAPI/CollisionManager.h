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
		: start(st), end(ed), bDebugDraw(false), CurrentTime(0.f), DebugDuration(0.f), DebugColor(RGB(0, 255, 0))
	{

	}

	void Render(HDC hdc)
	{
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);
	}
	void Update(float TimeDelta)
	{
		CurrentTime += TimeDelta;
		if (CurrentTime >= DebugDuration)
		{
			CurrentTime = 0.f;
			bDebugDraw = false;
		}
	}
	FPOINT start;
	FPOINT end;

	float CurrentTime;
	float DebugDuration;
	bool bDebugDraw;
	COLORREF DebugColor;
};

class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Init();
	void AddObject(OBJID eID, Collider* collider);

	void Update(float TimeDelta);
	void Render(HDC hdc);
	void Release();

	//eObjID그룹으로 레이를 쏜다!
	bool LineTraceByObject(
		HitResult& hitResult, 
		OBJID eObjID, 
		FPOINT start, 
		FPOINT end, 
		GameObject* Owner, 
		bool bIgnoreSelf = true,
		bool bDebugDraw = true,
		float DebugDuration = 3.f,
		COLORREF DebugColor = RGB(0, 255, 0));

private:
	void UpdatePivot(float TimeDelta);

	void DebugLineUpdate(float TimeDelta);
	void DebugLineRender(HDC hdc);
	// CCW 알고리즘을 사용하여 세 점의 방향을 계산
	float CCW(const FPOINT& p, const FPOINT& q, const FPOINT& r) {
		return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
	}

	// 두 선분이 교차하는지 확인
	bool DoLinesIntersect(const FPOINT& p1, const FPOINT& p2, const FPOINT& q1, const FPOINT& q2) {
		float ccw1 = CCW(p1, p2, q1);
		float ccw2 = CCW(p1, p2, q2);
		float ccw3 = CCW(q1, q2, p1);
		float ccw4 = CCW(q1, q2, p2);

		// 교차 조건
		return (ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0);
	}

	// 사각형 내부에 점이 포함되는지 확인
	bool IsPointInsideRect(const FPOINT& p, const FPOINT& rectMin, const FPOINT& rectMax) {
		return p.x >= rectMin.x && p.x <= rectMax.x && p.y >= rectMin.y && p.y <= rectMax.y;
	}
private:
	list<Collider*>	CollisionList[OBJ_END];
	list<Line*> LineList;
};
