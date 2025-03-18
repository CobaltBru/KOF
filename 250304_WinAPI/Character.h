#pragma once
#include "config.h"
#include <vector>
class Image;
class Character
{
private:
	enum class STATE { IDLE, BACK, WALK, DOWN, DOWNBACK, DOWNWALK, DASH, BACKDASH, PROCESS };
	int player;

	FPOINT pos;
	int screenWay;
	int moveWay;
	float speed;
	float hp;
	float currentHp;
	float damage;
	
	string currentCommand;
	vector<Image> images;
	STATE currentState;
public:
	Character();
	~Character();
	void Init(vector<Image> images, FPOINT pos, float hp, float damage);
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Move();
	void getCommand();
	void updateCurrentScreenWay(Character* otherCharacter);
	void setPlayer(int p);
};


