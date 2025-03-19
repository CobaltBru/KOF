#include "ObjectManager.h"
#include "GameObject.h"
void ObjectManager::Init()
{
}

void ObjectManager::AddObject(OBJID eID, GameObject* pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

void ObjectManager::Update(float TimeDelta)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			(*iter)->Update(TimeDelta);

			/*if (OBJ_DEAD == iResult)
			{
				delete *iter;
				iter = m_ObjList[i].erase(iter);
			}
			else*/

			++iter;
		}
	}
}

void ObjectManager::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			(*iter)->Render(hDC);

			++iter;
		}
	}
}

void ObjectManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Release();
			delete iter;
		}

		m_ObjList[i].clear();
	}
	ReleaseInstance();
}
