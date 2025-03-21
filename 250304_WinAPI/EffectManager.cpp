#include "EffectManager.h"
#include "Effect.h"

void EffectManager::Init()
{
}

void EffectManager::Update(float TimeDelta)
{
	for (auto iter = effectList.begin(); iter != effectList.end();)
	{
		(*iter)->Update(TimeDelta);

		if ((*iter)->IsDead())
		{
			(*iter)->Release();
			delete (*iter);
			iter = effectList.erase(iter);
		}			
		else
			++iter;
	}
}

void EffectManager::Render(HDC hDC)
{
	for (auto& iter : effectList)
		iter->Render(hDC);
}

void EffectManager::Release()
{
	for (auto& iter : effectList)
	{
		iter->Release();
		delete iter;
	}
	effectList.clear();

	ReleaseInstance();
}
