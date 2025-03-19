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
	screenWay = player == 1 ? true : false;
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
	//Ű�Է��� ���� �� �ִ� ����
	if (currentState != STATE::PROCESS)
	{
		if (currentCommand == "A")
		{
			if (screenWay == true) //�ް�����
			{
				moveWay = -1;
				speed = 0.7f;
				if(currentState == STATE::DOWN)currentState = STATE::DOWNBACK;
				else currentState = STATE::BACK;
			}
			else //������ 
			{
				moveWay = 1;
				speed = 1.0f;
				if (currentState == STATE::DOWN)currentState = STATE::DOWNWALK;
				else currentState = STATE::WALK;
			}
		}
		else if (currentCommand == "D")
		{
			if (screenWay == true) //������
			{
				moveWay = 1; 
				speed = 1.0f;
				if (currentState == STATE::DOWN)currentState = STATE::DOWNWALK;
				else currentState = STATE::WALK;
			}
			else //�ް�����
			{
				moveWay = -1;
				speed = 0.7f;
				if (currentState == STATE::DOWN)currentState = STATE::DOWNBACK;
				else currentState = STATE::BACK;
			}
		}
		else if (currentCommand == "S") //���̱�
		{
			speed = 0;
			currentState = STATE::DOWN;
		}
		else if (currentCommand == "AA") 
		{
			if (screenWay == true) //��뽬
			{
				speed = 3.0f;
				moveWay = -1;
				currentState = STATE::BACKDASH;
			}
			else //�մ뽬
			{
				speed = 3.0f;
				moveWay = 1;
				currentState = STATE::DASH;
			}
		}
		else if (currentCommand == "DD")
		{
			if (screenWay == true) //�մ뽬
			{
				speed = 3.0f;
				moveWay = 1;
				currentState = STATE::DASH;
			}
			else //��뽬
			{
				speed = 3.0f;
				moveWay = -1;
				currentState = STATE::BACKDASH;
			}
		}
		else
		{
			useSkill(currentCommand);
		}

	}

	//������
	if (currentState != STATE::IDLE)
	{
		timecnt += deltaTime;
		framecnt = timecnt / (deltaTime); //���� ������ ���
		if (currentState == STATE::PROCESS) //�����
		{
			if (framecnt >= skillSet[currentSkill].maxFrame)//������ IDLE��
			{
				endSkill();
			}
		}
		else //�Ϲݵ���
		{
			if (framecnt >= maxFrames[getIndex()])//����ó��
			{
				framecnt = 0;
				timecnt = 0;
			}
		}
	}
	
	
	//�⺻�����Ͻ� �ʱ�ȭ
	if (currentState == STATE::IDLE) 
	{
		timecnt == 0;
		framecnt = 0;
	}
	
	
	Move(deltaTime);
	
}

void Character::Render(HDC hdc)
{
	if (currentState != STATE::IDLE)
	{
		if (currentState == STATE::PROCESS)
		{
			skillSet[currentSkill].image->Render(hdc, pos.x, pos.y, framecnt, screenWay);
		}
		else
		{
			images[getIndex()].Render(hdc, pos.x, pos.y, framecnt, screenWay);
		}
	}
}

void Character::Move(float deltaTime)
{
	if ((currentState == STATE::BACK) || (currentState == STATE::WALK))
	{
		pos.x += ((screenWay ? 1 : -1) * moveWay) * speed * deltaTime;
	}
	if ((currentState == STATE::DOWNBACK) || (currentState == STATE::DOWNWALK))
	{
		pos.x += ((screenWay ? 1 : -1) * moveWay) * speed * deltaTime * 0.5f;
	}
	if ((currentState == STATE::BACKDASH) || (currentState == STATE::DASH))
	{
		pos.x += ((screenWay ? 1 : -1) * moveWay) * speed * deltaTime * 3;
	}
}

void Character::getCommand()
{
}

void Character::updateCurrentScreenWay(Character* otherCharacter)
{
	if (pos.x - otherCharacter->pos.x < 0) screenWay = false;
	else if (pos.x - otherCharacter->pos.x > 0) screenWay = true;
}

void Character::useSkill(string str)
{
	for (int i = 0;i<skillSet.size();i++)
	{
		if (str.find(skillSet[i].command) != string::npos)
		{
			currentSkill = i;
			currentState = STATE::PROCESS;

			SKILL& skill = skillSet[currentSkill];
			this->damage = skill.damage;
			this->moveWay = skill.way;
			this->speed = skill.speed;
		}
		else
		{
			currentState = STATE::IDLE;
			return;
		}
	}
	
	
}

void Character::endSkill()
{
	currentState = STATE::IDLE;
	this->damage = 0;
	this->currentSpeed = 0;
}


int Character::getIndex()
{
	int idx = 0;
	switch (currentState)
	{
	case STATE::IDLE:
		idx = -1;
		break;
	case STATE::BACK:
		idx = 0;
		break;
	case STATE::WALK:
		idx = 1;
		break;
	case STATE::DOWN:
		idx = 2;
		break;
	case STATE::DOWNBACK:
		idx = 3;
		break;
	case STATE::DOWNWALK:
		idx = 4;
		break;
	case STATE::DASH:
		idx = 5;
		break;
	case STATE::BACKDASH:
		idx = 6;
		break;
	case STATE::SKILL:
		idx = -1;
		break;
	case STATE::PROCESS:
		idx = -1;
		break;
	}
	return idx;
}
