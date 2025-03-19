#pragma once
#include "GameObject.h"

class Image;

class UserInterface
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	UserInterface();
	~UserInterface();
private:
	enum eBattle {
		P1Character, P2Character, HP_bar, HP_gage_p1, HP_gage_p2, eBattleEnd
	};

	Image* battleImage[eBattle::eBattleEnd];

	float hpCalculate;
	int p1Health;
	int p2Health;
	
};
