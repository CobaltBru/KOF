#pragma once
#include "GameObject.h"

class Image;
class Character;
class UserInterface : public Singleton<UserInterface>
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetPlayer(Character* p1, Character* p2)
	{
		characterP1 = p1;
		characterP2 = p2;
	}

	UserInterface();
	~UserInterface();
private:
	enum eBattle {
		P1Character, P2Character, HP_bar, HP_gage_p1, HP_gage_p2, Time_infinite, Stage, eBattleEnd
	};

	Image* battleImage[eBattle::eBattleEnd];

	float hpCalculate;
	int p1Health;
	int p2Health;
	Character* characterP1;
	Character* characterP2;
};
