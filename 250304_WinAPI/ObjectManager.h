#pragma once

#include "Singleton.h"
#include "config.h"
class GameObject;
class ObjectManager : public Singleton<ObjectManager>
{
public:
	void Init();
	void AddObject(OBJID eID, GameObject* pObj);
	void Update(float TimeDelta);
	void Render(HDC hDC);
	void Release();
private:
	list<GameObject*>	m_ObjList[OBJ_END];
};

