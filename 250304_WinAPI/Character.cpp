#include "Character.h"
#include "Image.h"
#include "KOFKeyManager.h"


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
void Character::setIdle()
{
	timecnt = 0;
	framecnt = 0;
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
		setWalk();
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
	guardState = 0;
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
	delete profile;
	for (auto skill : skillSet)
	{
		delete skill.image;
	}
}

//IDLE, 뒷걷기, 앞걷기, 숙이기, 앞대쉬, 백대쉬 순으로 넣어주세요
void Character::pushCommon(Image* image, int maxFrame)
{
	images.push_back(*image);
}

void Character::pushSkill(string command, Image* image, int maxFrame,
			int damage, int reach, bool isUpperAttack, bool isLowerAttack,
			float startTime, float endTime, int way, int speed)
{
	SKILL skill;
	skill.command = command;
	skill.image = image;
	skill.maxFrame = maxFrame;
	skill.damage = damage;
	skill.reach = reach;
	skill.isUpperAttack = isUpperAttack;
	skill.isLowerAttack = isLowerAttack;
	skill.startTime = startTime;
	skill.endTime = endTime;
	skill.way = way;
	skill.speed = speed;
	
	skillSet.push_back(skill);
}
//조작 커맨드 asd
void Character::Update(float deltaTime)
{
	
	if (currentState != STATE::PROCESS)
	{
		currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);;
		basicKeys[EKeyType::KEY_W] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_W);
		basicKeys[EKeyType::KEY_A] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
		basicKeys[EKeyType::KEY_S] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
		basicKeys[EKeyType::KEY_D] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);
		
		if (currentState == STATE::DOWN && basicKeys[EKeyType::KEY_S] ||
			currentState == STATE::BACK && basicKeys[EKeyType::KEY_A] ||
			currentState == STATE::WALK && basicKeys[EKeyType::KEY_D])
		{
			currentState == STATE::IDLE;
		}
		dashTimer += deltaTime;
		if (basicKeys[EKeyType::KEY_A])
		{
			if (dashKey == "a1_1") dashKey = "a2";
			if (screenWay == false) //뒷걸음질
			{
				if (currentState == STATE::DOWN)//숙이고 있었으면 하단방어
				{
					guardState = 2;
				}
				else
				{
					setBack();
					checkBackDash("a2");
				}
				
			}
			else //앞으로 
			{
				setWalk();
				checkDash("a2");
			}
			dashKey = "a1";
		}
		else
		{
			if (dashKey == "a1")
			{
				startDashTimer();
				dashKey = "a1_1";
			}
		}

		if (basicKeys[EKeyType::KEY_D])
		{
			if (dashKey == "d1_1") dashKey = "d2";
			if (screenWay == false) //앞으로
			{
				setWalk();
				checkDash("d2");
			}
			else //뒷걸음질
			{
				if (currentState == STATE::DOWN)//숙이고 있었으면 하단방어
				{
					guardState = 2;
				}
				else
				{
					setBack();
					checkBackDash("d2");
				}
			}
			dashKey = "d1";
		}
		else
		{
			if (dashKey == "d1")
			{
				startDashTimer();
				dashKey = "d1_1";
			}
		}
		if (basicKeys[EKeyType::KEY_S]) //숙이기
		{
			setDown();
		}
		else
		{
			setIdle();
		}

		if (!basicKeys[EKeyType::KEY_W] && !basicKeys[EKeyType::KEY_A] &&
			!basicKeys[EKeyType::KEY_S] && !basicKeys[EKeyType::KEY_D])
		{
			setIdle();
		}

	}
	useSkill(currentCommand);
	//동작중
	if (currentState != STATE::IDLE)
	{
		timecnt += deltaTime;
		framecnt = timecnt / (deltaTime / FRAMESPEED); //현재 프레임 계산
		if (currentState == STATE::PROCESS) //기술중
		{
			if (framecnt >= skillSet[currentSkill].maxFrame)//끝나면 IDLE로
			{
				endSkill();
			}
		}
		else if (currentState == STATE::BACKDASH) //백대쉬는 끝나면 BACK으로
		{
			if (framecnt >= images[getIndex()].GetMaxFrame())
			{
				framecnt = 0;
				timecnt = 0;
				setIdle();
			}
		}
		else //일반동작
		{
			if (framecnt >= images[getIndex()].GetMaxFrame())//루프처리
			{
				framecnt = 0;
				timecnt = 0;
			}
		}
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
	if (currentState == STATE::PROCESS)
	{
		int maxFrame = skillSet[currentSkill].maxFrame;
		if (skillSet[currentSkill].startTime >= ((float)framecnt / (float)maxFrame))
		{
			speed = skillSet[currentSkill].speed;
		}
		if (skillSet[currentSkill].endTime <= ((float)framecnt / (float)maxFrame))
		{
			speed = 0;
		}
	}
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
	for (int i = 0;i<skillSet.size();i++)
	{
		if (str.find(skillSet[i].command) != string::npos)
		{
			currentSkill = i;
			currentState = STATE::PROCESS;

			SKILL& skill = skillSet[currentSkill];
			this->damage = skill.damage;
			this->moveWay = skill.way;
			if(skill.startTime <= 0.0f) this->speed = skill.speed;
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
	this->speed = 0;
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

