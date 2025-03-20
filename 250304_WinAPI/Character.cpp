#include "Character.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include "CollisionManager.h"
#include <math.h>

Character::Character()
{
	player = 0;
	profile = nullptr;
	pos = { 0,0 };
	screenWay = true;
	moveWay = 1;
	characterSpeed = 5.0f;
	speed = 0;
	hp = 100;
	currentHp = hp;
	damage = 0;
	//images
	currentCommand = "";

	memset(oldKeys, false, sizeof(oldKeys));
	memset(basicKeys, false, sizeof(basicKeys));

	//skillSet
	currentSkill = -1;

	framecnt = 0;
	timecnt = 0;
	dashTimer = 0.0f;
	dashTime = 0.0f;
	dashKey = "n";

	currentState = STATE::IDLE;
	guardState = 0;
	
}

Character::~Character()
{
	
}

void Character::setPlayer(int p)//1, 2
{
	this->player = p;
	screenWay = player == 1 ? false : true;
}
bool Character::isJustPressed(int key)
{
	return (!oldKeys[key] && basicKeys[key]);
}
bool Character::isJustReleased(int key)
{
	return (oldKeys[key] && !basicKeys[key]);
}
bool Character::isKeepPressed(int key)
{
	return (oldKeys[key] && basicKeys[key]);
}
bool Character::isKeepReleased(int key)
{
	return (!oldKeys[key] && !basicKeys[key]);
}
void Character::setIdle()
{
	timecnt = 0;
	speed = 0;
	guardState = 0;
	currentState = STATE::IDLE;
}
void Character::setWalk()
{
	moveWay = 1;
	speed = 1.0f;
	guardState = 0;
	currentState = STATE::WALK;
}
void Character::setBack()
{
	moveWay = -1;
	speed = 0.7f;
	guardState = 1;
	currentState = STATE::BACK;
}
void Character::startDashTimer()
{
	dashTime = dashTimer;
}
void Character::checkDash(string key)
{
	if (dashKey == key)
	{
		if (dashTimer - dashTime < 0.2f)
		{
			setDash();
		}
		dashTimer = 0.0f;
		dashTime = 0.0f;
		dashKey = "n";
	}
	else
	{
		dashTimer = 0.0f;
		dashTime = 0.0f;
		dashKey = "n";
	}
}
void Character::setDash()
{
	moveWay = 1;
	speed = 2.0f;
	guardState = 0;
	currentState = STATE::DASH;
}
void Character::checkBackDash(string key)
{
	if (dashKey == key)
	{
		if (dashTimer - dashTime < 0.2f)
		{
			setBackDash();
		}
		dashTimer = 0.0f;
		dashTime = 0.0f;
		dashKey = "n";
	}
	else
	{
		dashTimer = 0.0f;
		dashTime = 0.0f;
		dashKey = "n";
		setBack();
	}
}
void Character::setBackDash()
{
	moveWay = -1;
	speed = 3.0f;
	guardState = 0;
	currentState = STATE::BACKDASH;
}
void Character::setDown()
{
	speed = 0.0f;
	currentState = STATE::DOWN;
}
void Character::Init(int player, Image* profile, FPOINT pos, float characterSpeed,
	float hp, vector<Image>images)
/*Init(int player, Image* profile, FPOINT pos, float characterSpeed,
	float hp, vector<Image>images)*/
{
	this->player = player;
	this->profile = profile;
	this->pos = pos;
	this->screenWay = player == 1 ? false : true;
	this->moveWay = 1;
	this->characterSpeed = characterSpeed;
	this->speed = 0;
	this->hp = hp;
	this->currentHp = this->hp;
	this->damage = 0;
	this->images = images;
	this->currentCommand = "";
	//basicKeys
	//skillSet
	this->currentSkill = -1;
	this->framecnt = 0;
	this->timecnt = 0;
	this->dashTimer = 0.0f;
	this->dashTime = 0.0f;
	this->dashKey = "n";
	this->currentState = STATE::IDLE;
	this->guardState = 0;
}

void Character::Release()
{
	profile->Release();
	delete profile;

	for (auto skill : skillSet)
	{
		skill.image->Release();
		delete skill.image;
	}
	for (auto image : images)
	{
		image.Release();
	}
}

//IDLE, �ްȱ�, �հȱ�, ���̱�, �մ뽬, ��뽬 ������ �־��ּ���
void Character::pushCommon(Image* image, int maxFrame)
{
	images.push_back(*image);
}

void Character::pushSkill(string command, Image* image, int maxFrame,
			int damage, int reach, bool isUpperAttack, bool isLowerAttack, int attackFrame)
{
	SKILL skill;
	skill.command = command;
	skill.image = image;
	skill.maxFrame = maxFrame;
	skill.damage = damage;
	skill.reach = reach;
	skill.isUpperAttack = isUpperAttack;
	skill.isLowerAttack = isLowerAttack;
	skill.attackFrame = attackFrame;
	skillSet.push_back(skill);
}
//���� Ŀ�ǵ� asd
void Character::Update(float deltaTime)
{
	
	if ((currentState != STATE::PROCESS) && (currentState != STATE::BACKDASH))
	{
		currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);
		basicKeys[EKeyType::KEY_W] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_W);
		basicKeys[EKeyType::KEY_A] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
		basicKeys[EKeyType::KEY_S] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
		basicKeys[EKeyType::KEY_D] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);

		dashTimer += deltaTime;
		if (isJustPressed(EKeyType::KEY_A)) //��� ���ȴ°�?
		{
			if (screenWay == false) //�ް�����
			{
				if (currentState == STATE::DOWN)//���̰� �־����� �ϴܹ��
				{
					guardState = 2;
				}
				else
				{
					setBack();
					checkBackDash("a");
				}

			}
			else //������ 
			{
				setWalk();
				checkDash("a");
			}
		}
		if (isKeepPressed(EKeyType::KEY_A)) //��� ������ �ִ°�
		{
			if (screenWay == false) //�ް�����
			{
				if (currentState == STATE::DOWN)//���̰� �־����� �ϴܹ��
				{
					guardState = 2;
				}
				else
				{
					setBack();
				}

			}
			else //������ 
			{
				if (currentState == STATE::DASH) {}
				else setWalk();
				checkDash("a");
			}
		}
		
		if (isJustReleased(EKeyType::KEY_A)) //��� �ó�?
		{
			if (currentState == STATE::DOWN)
			{
				guardState = 0;
			}
			else
			{
				setIdle(); //�ȱ� ����
			}
			startDashTimer();
			dashKey = "a";
		}
		if (isJustPressed(EKeyType::KEY_D)) //��� ���ȴ°�?
		{
			if (screenWay == false) //������
			{
					
				setWalk();
				checkDash("d");
			}
			else //�ް����� 
			{
				if (currentState == STATE::DOWN)//���̰� �־����� �ϴܹ��
				{
					guardState = 2;
				}
				else
				{
					setBack();
					checkBackDash("d");
				}
			}
		}
		if (isKeepPressed(EKeyType::KEY_D))
		{
			if (screenWay == false) //������
			{

				if (currentState == STATE::DASH) {}
				else setWalk();
			}
			else //�ް����� 
			{
				if (currentState == STATE::DOWN)//���̰� �־����� �ϴܹ��
				{
					guardState = 2;
				}
				else
				{
					setBack();
				}
			}
		}
		
		if (isJustReleased(EKeyType::KEY_D)) //��� �ó�?
		{
			if (currentState == STATE::DOWN)
			{
				guardState = 0;
			}
			else
			{
				setIdle(); //�ȱ� ����
			}
			startDashTimer();
			dashKey = "d";
		}

		
		if (isJustPressed(EKeyType::KEY_S)) //���̱�
		{
			setDown();
			guardState = 0;
		}
		if (isKeepPressed(EKeyType::KEY_S)) //���̱�
		{
			setDown();
		}
		if (isJustReleased(EKeyType::KEY_S))
		{
			setIdle();
			guardState = 0;
		}


		for (int i = 0; i < 4; i++)oldKeys[i] = basicKeys[i];

	}


	useSkill(currentCommand); // ��ų Ŀ�ǵ� �ǵ�

	timecnt += deltaTime;
	if (timecnt >= FRAMESPEED)
	{
		/*framecnt += (timecnt / FRAMESPEED);
		timecnt = fmodf(timecnt, FRAMESPEED);*/
		framecnt++;
		timecnt = 0;
	}


	if (currentState == STATE::PROCESS) //�����
	{
		if (currentSkill != -1)
		{
			if (framecnt == skillSet[currentSkill].attackFrame)
			{
				HitResult hit;
				//(skill.reach > (player == 1 ? 1 : -1) * (other->GetPos().x - pos.x))
				if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, pos, { pos.x+(float)((player == 1 ? 1 : -1) * skillSet[currentSkill].reach), pos.y }, this, true))
				{
					if (Character* OtherCharacter = dynamic_cast<Character*>(hit.Actors[0]))
					{
						attack(OtherCharacter);

						//skillSet[currentSkill].damage;
					}
				}
				//attack();
			}
		}
		if (framecnt >= skillSet[currentSkill].maxFrame)//������ IDLE��
		{
			framecnt = 0;
			endSkill();
		}
	}
	else if (currentState == STATE::BACKDASH) //��뽬�� ������ BACK����
	{
		if (framecnt >= images[getIndex()].GetMaxFrame())
		{
			//int tmp = images[getIndex()].GetMaxFrame();
			framecnt = 0;
			timecnt = 0;
			setBack();
		}
	}
	else //�Ϲݵ���
	{
		if (framecnt >= images[getIndex()].GetMaxFrame())//����ó��
		{
			STATE tmp = currentState;
			framecnt = 0;
			timecnt = 0;
		}
	}
	
	if (currentState == STATE::IDLE)
	{
		currentState;
	}
	
	Move(deltaTime);
	
}

void Character::Render(HDC hdc)
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

void Character::Move(float deltaTime)
{
	/*if (currentState == STATE::PROCESS)
	{
		int tmp = framecnt;
		int maxFrame = skillSet[currentSkill].maxFrame;
		if (skillSet[currentSkill].startTime >= ((float)framecnt / (float)maxFrame))
		{
			speed = skillSet[currentSkill].speed;
		}
		if (skillSet[currentSkill].endTime <= ((float)framecnt / (float)maxFrame))
		{
			speed = 0;
		}
	}*/
	pos.x += ((screenWay ? -1 : 1) * moveWay) * speed * characterSpeed * deltaTime;
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
	if (str == "")
	{
		return;
	}
	KOFKeyManager::GetInstance()->GetPlayerCommand(player);
	for (int i = 0;i<skillSet.size();i++)
	{
		if (str.find(skillSet[i].command) != string::npos)
		{
			setIdle();
			currentSkill = i;
			currentState = STATE::PROCESS;

			SKILL& skill = skillSet[currentSkill];
			this->damage = skill.damage;
			//if(skill.startTime <= 0.0f) this->speed = skill.speed;
			framecnt = 0;
			KOFKeyManager::GetInstance()->ClearPlayerBuffer(player);
			currentCommand = "";
			return;
		}
	}
	
}

void Character::endSkill()
{
	currentSkill = -1;
	setIdle();
}


int Character::getIndex()
{
	int idx = 0;
	switch (currentState)
	{
	case STATE::IDLE:
		idx = 0;
		break;
	case STATE::BACK:
		idx = 1;
		break;
	case STATE::WALK:
		idx = 2;
		break;
	case STATE::DOWN:
		idx = 3;
		break;
	case STATE::DASH:
		idx = 4;
		break;
	case STATE::BACKDASH:
		idx = 5;
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



float* Character::getCurrentHp()
{
	return &currentHp;
}

float Character::getMaxHp()
{
	return hp;
}

Image Character::getProfile()
{
	return *profile;
}

int Character::getGuardState()
{
	return guardState;
}

Character::STATE Character::getState()
{
	return currentState;
}

void Character::attack(Character* other)
{
	SKILL& skill = skillSet[currentSkill];
	int d = damage;
	//if (skill.reach > (player == 1 ? 1 : -1) * (other->GetPos().x - pos.x))
	//{
	//	if (skill.isLowerAttack) //�ϴ� �����϶�
	//	{
	//		if (other->getGuardState() == 2) //�ϴ� ����϶�
	//		{
	//			d *= 0.1f;
	//		}
	//	}
	//	else if (skill.isUpperAttack) //��� �����϶�
	//	{
	//		if (other->getState() == STATE::DOWN) //��밡 ��������
	//		{
	//			d = 0;
	//		}
	//		else if (other->getGuardState() == 1) //��� ����϶�
	//		{
	//			d *= 0.1f;
	//		}
	//	}
	//	other->getDamage(d);
	//}

	if (skill.isLowerAttack) //�ϴ� �����϶�
	{
		if (other->getGuardState() == 2) //�ϴ� ����϶�
		{
			d *= 0.1f;
			other->SetCurrentState(STATE::BLOCKLOWER);
		}
		else
			other->SetCurrentState(STATE::HITLOWER);
	}
	else if (skill.isUpperAttack) //��� �����϶�
	{
		if (other->getState() == STATE::DOWN) //��밡 ��������
		{
			d = 0;
		}
		else if (other->getGuardState() == 1) //��� ����϶�%
		{
			d *= 0.1f;
			other->SetCurrentState(STATE::BLOCKUPPER);
		}
		else
			other->SetCurrentState(STATE::HITUPPER);
	}
	other->getDamage(d);
}

void Character::getDamage(float damage)
{
	currentHp -= damage;
	//
}


