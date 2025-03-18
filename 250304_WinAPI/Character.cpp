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
	if (currentCommand == "N") //�⺻
	{
		currentState = STATE::IDLE;
	}
	else if (currentCommand == "N") //������
	{
		currentState = STATE::WALK;
		pos.x += way * speed;
	}
	else if (currentCommand == "N") //�ڷ�
	{
		currentState = STATE::WALK;
	}
	else if (currentCommand == "N") //���̱�
	{
		currentState = STATE::DOWN;
	}
	else if (currentCommand == "N") //�մ뽬
	{
		currentState = STATE::DASH;
	}
	else if (currentCommand == "N") //�ڴ뽬
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

