#pragma once
#include "Singleton.h"
#include "config.h"

class Character;
class UserInterface;
enum PLAYER_TYPE
{
	P1,
	P2,
	PLAYER_END
};
class GameManager : public Singleton<GameManager>
{
public:
	void Init();
	void Update(float TimeDelta);
	void Release();

	void Render(HDC hdc);
	void UpdateCharacterPosition(Character* newPlayer, float Time, const FPOINT& P0, const FPOINT& P1, const FPOINT& P2);

private:
	float P1TagTime = 0.f;
	float P2TagTime = 0.f;
	float TagSpeed = 3.f;

	vector<FPOINT> P1TagPath;
	vector<FPOINT> P2TagPath;

	vector<Character*> P1Players;
	int NextP1Player = 0;

	vector<Character*> P2Players;
	int NextP2Player = 0;

	Character* CurrentPlayer[PLAYER_END];

	bool P1Tag = false;
	bool P2Tag = false;

	UserInterface* UI;

};

