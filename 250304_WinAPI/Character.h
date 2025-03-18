#pragma once
#include "config.h"
#include <vector>
class Image;
class Character
{
private:
	enum class STATE{ IDLE, WALK, DOWN, DASH };
	int player;

	FPOINT pos;
	int way;
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
	void Update();
	void Render(HDC hdc);
	void Move();
	void getCommand();

	void setPlayer(int p);
};

