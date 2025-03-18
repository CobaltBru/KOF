#include "Character.h"
#include "Image.h"

Character::Character()
{
	player = 0;
	moveWay = 1;
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
	screenWay = player == 1 ? 1 : -1;
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

void Character::Update(float deltaTime)
{
	if (currentCommand == "A")
	{
		if (screenWay == 1)
		{
			currentState = STATE::BACK;
		}
		else
		{
			currentState = STATE::WALK;
		}
	}
	else if (currentCommand == "D")
	{
		if (screenWay == 1)
		{
			currentState = STATE::WALK;
		}
		else
		{
			currentState = STATE::BACK;
		}
	}
	else if (currentCommand == "S")
	{
		currentState = STATE::DOWN;
	}
	else if (currentCommand == "AA")
	{
		if (screenWay == 1)
		{
			currentState = STATE::BACKDASH;
		}
		else
		{
			currentState = STATE::DASH;
		}
	}
	else if (currentCommand == "DD")
	{
		if (screenWay == 1)
		{
			currentState = STATE::DASH;
		}
		else
		{
			currentState = STATE::BACKDASH;
		}
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

void Character::updateCurrentScreenWay(Character* otherCharacter)
{
	if (pos.x - otherCharacter->pos.x < 0) screenWay = -1;
	else if (pos.x - otherCharacter->pos.x > 0) screenWay = 1;
}

