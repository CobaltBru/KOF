#include "Character.h"
#include "Image.h"

Character::Character()
{
	player = 0;
	way = 1;
	pos = { 0,0 };
	speed = 0;
	hp = 0;
	currentHp = 0;
	damage = 0;
	currentCommand = "";
	currentState = STATE::IDLE;
}

Character::~Character()
{
}

void Character::setPlayer(int p)//1, 2
{
	this->player = p;
}
void Character::Init(vector<Image> images, FPOINT pos, float hp, float damage)
{
	this->images = images;
	this->pos = pos;
	this->hp = hp;
	currentHp = hp;
	this->damage = damage;
	currentCommand = "";
}

void Character::Release()
{
}

void Character::Update()
{
	if (currentCommand == "N") //기본
	{
		currentState = STATE::IDLE;
	}
	else if (currentCommand == "N") //앞으로
	{
		currentState = STATE::WALK;
		pos.x += way * speed;
	}
	else if (currentCommand == "N") //뒤로
	{
		currentState = STATE::WALK;
	}
	else if (currentCommand == "N") //숙이기
	{
		currentState = STATE::DOWN;
	}
	else if (currentCommand == "N") //앞대쉬
	{
		currentState = STATE::DASH;
	}
	else if (currentCommand == "N") //뒤대쉬
	{
		currentState = STATE::DASH;
	}
}

void Character::Render(HDC hdc)
{
	images[(int)currentState].Render(hdc, pos.x,pos.y);
}

void Character::Move()
{
}

void Character::getCommand()
{
}

