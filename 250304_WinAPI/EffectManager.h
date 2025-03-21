#pragma once
#include "Singleton.h"
#include "config.h"

enum EFFECTTYPE
{
	BLOCK,
	HIT,
	END
};

class Effect;
class EffectManager : public Singleton<EffectManager>
{
public:
	void Init();
	void AddEffect(Effect* effect) {
		if (effect == nullptr)
			return;
		effectList.push_back(effect);
	};
	void Update(float TimeDelta);
	void Render(HDC hDC);
	void Release();

private:
	list<Effect*> effectList;
};

