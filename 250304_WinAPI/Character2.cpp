#include "Character2.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include <math.h>

Character2::Character2()
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

	currentState = STATE::OPEN;
	currentBehave = BEHAVE::IDLE;
	guardState = 0;
	
}

Character2::~Character2()
{
}

void Character2::setPlayer(int p)//1, 2
{
	this->player = p;
	screenWay = player == 1 ? false : true;
}
bool Character2::isJustPressed(int key)
{
	return (!oldKeys[key] && basicKeys[key]);
}
bool Character2::isJustReleased(int key)
{
	return (oldKeys[key] && !basicKeys[key]);
}
bool Character2::isKeepPressed(int key)
{
	return (oldKeys[key] && basicKeys[key]);
}
bool Character2::isKeepReleased(int key)
{
	return (!oldKeys[key] && !basicKeys[key]);
}
void Character2::setIdle()
{
	timecnt = 0;
	speed = 0;
	guardState = 0;
	currentState = STATE::OPEN;
	currentSkill = "IDLE";
}
void Character2::setWalk()
{
	moveWay = 1;
	speed = 1.0f;
	guardState = 0;
	currentState = STATE::OPEN;
	currentBehave = BEHAVE::WALK;
	currentSkill = "WALK";
}
void Character2::setBack()
{
	moveWay = -1;
	speed = 0.7f;
	guardState = 1;
	currentState = STATE::OPEN;
	currentBehave = BEHAVE::BACK;
	currentSkill = "BACK";
}
void Character2::startDashTimer()
{
	dashTime = dashTimer;
}
void Character2::checkDash(string key)
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
void Character2::setDash()
{
	moveWay = 1;
	speed = 2.0f;
	guardState = 0;
	currentState = STATE::OPEN;
	currentBehave = BEHAVE::DASH;
	currentSkill = "DASH";
}
void Character2::checkBackDash(string key)
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
void Character2::setBackDash()
{
	moveWay = -1;
	speed = 3.0f;
	guardState = 0;
	currentState = STATE::LOCK;
	currentBehave = BEHAVE::BACKDASH;
	currentSkill = "BACKDASH";
}
void Character2::setDown()
{
	speed = 0.0f;
	currentState = STATE::OPEN;
	currentBehave = BEHAVE::DOWN;
	currentSkill = "DOWN";
}
void Character2::Init(int player, Image* profile, FPOINT pos, float characterSpeed,
	float hp)
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
	this->currentCommand = "";
	//basicKeys
	//skillSet
	this->currentSkill = -1;
	this->framecnt = 0;
	this->timecnt = 0;
	this->dashTimer = 0.0f;
	this->dashTime = 0.0f;
	this->dashKey = "n";
	this->currentState = STATE::OPEN;
	this->currentBehave = BEHAVE::IDLE;
	this->guardState = 0;
}

void Character2::Release()
{
	profile->Release();
	delete profile;

	for (auto image : images)
	{
		image.Release();
	}
}

//idle, BACK, WALK, DOWN, DASH, BACKDASH 순으로 넣어주세요
void Character2::pushCommon(string str, Image* image, string nextBehave)
{
	SKILL skill;
	skill.imageIdx = images.size();
	skill.maxFrame = image->GetMaxFrame();
	skill.damage = 0;
	skill.reach = 0;
	skill.isLowerAttack = false;
	skill.isUpperAttack = false;

	behaviorMap[str] = skill;
	images.push_back(*image);

	skill.next = nextBehave;
}

void Character2::pushSkill(string command, Image* image, int maxFrame,
			int damage, int reach, bool isUpperAttack, bool isLowerAttack)
{
	SKILL skill;
	skill.imageIdx = images.size();
	images.push_back(*image);
	skill.maxFrame = maxFrame;
	skill.damage = damage;
	skill.reach = reach;
	skill.isUpperAttack = isUpperAttack;
	skill.isLowerAttack = isLowerAttack;
	
	behaviorMap[command] = skill;
	skill.next = "IDLE";
}
//조작 커맨드 asd
void Character2::Update(float deltaTime)
{
	basicKeys[EKeyType::KEY_W] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_W);
	basicKeys[EKeyType::KEY_A] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
	basicKeys[EKeyType::KEY_S] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
	basicKeys[EKeyType::KEY_D] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);

	dashTimer += deltaTime;
	if (currentState == STATE::OPEN)
	{
		currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);
		
		if (isJustPressed(EKeyType::KEY_A)) //방금 눌렸는가?
		{
			if (screenWay == false) //뒷걸음질
			{
				if (currentBehave == BEHAVE::DOWN)//숙이고 있었으면 하단방어
				{
					guardState = 2;
				}
				else
				{
					setBack();
					checkBackDash("a");
				}

			}
			else //앞으로 
			{
				setWalk();
				checkDash("a");
			}
		}
		if (isKeepPressed(EKeyType::KEY_A)) //계속 누르고 있는가
		{
			if (screenWay == false) //뒷걸음질
			{
				if (currentBehave == BEHAVE::DOWN)//숙이고 있었으면 하단방어
				{
					guardState = 2;
				}
				else
				{
					setBack();
				}

			}
			else //앞으로 
			{
				if (currentBehave == BEHAVE::DASH) {}
				else setWalk();
				checkDash("a");
			}
		}
		
		if (isJustReleased(EKeyType::KEY_A)) //방금 뗐나?
		{
			if (currentBehave == BEHAVE::DOWN)
			{
				guardState = 0;
			}
			else
			{
				setIdle(); //걷기 종료
			}
			startDashTimer();
			dashKey = "a";
		}
		if (isJustPressed(EKeyType::KEY_D)) //방금 눌렸는가?
		{
			if (screenWay == false) //앞으로
			{
					
				setWalk();
				checkDash("d");
			}
			else //뒷걸음질 
			{
				if (currentBehave == BEHAVE::DOWN)//숙이고 있었으면 하단방어
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
			if (screenWay == false) //앞으로
			{

				if (currentBehave == BEHAVE::DASH) {}
				else setWalk();
			}
			else //뒷걸음질 
			{
				if (currentBehave == BEHAVE::DOWN)//숙이고 있었으면 하단방어
				{
					guardState = 2;
				}
				else
				{
					setBack();
				}
			}
		}
		
		if (isJustReleased(EKeyType::KEY_D)) //방금 뗐나?
		{
			if (currentBehave == BEHAVE::DOWN)
			{
				guardState = 0;
			}
			else
			{
				setIdle(); //걷기 종료
			}
			startDashTimer();
			dashKey = "d";
		}

		
		if (isJustPressed(EKeyType::KEY_S)) //숙이기
		{
			setDown();
			guardState = 0;
		}
		if (isKeepPressed(EKeyType::KEY_S)) //숙이기
		{
			setDown();
		}
		if (isJustReleased(EKeyType::KEY_S))
		{
			setIdle();
			guardState = 0;
		}


		

	}
	for (int i = 0; i < 4; i++)oldKeys[i] = basicKeys[i];

	useSkill(currentCommand); // 스킬 커맨드 판독

	timecnt += deltaTime;
	if (timecnt >= FRAMESPEED)
	{
		framecnt += (timecnt / FRAMESPEED);
		timecnt = fmodf(timecnt, FRAMESPEED);
	}


	//if (currentSkill != -1) //기술중
	//{
	//	if (framecnt >= skillSet[currentSkill].maxFrame)//끝나면 IDLE로
	//	{
	//		endSkill();
	//	}
	//}
	//else if (currentBehave == BEHAVE::BACKDASH) //백대쉬는 끝나면 BACK으로
	//{
	//	if (framecnt >= images[getCurrentIndex()].GetMaxFrame())
	//	{
	//		//int tmp = images[getIndex()].GetMaxFrame();
	//		framecnt = 0;
	//		timecnt = 0;
	//		setBack();
	//	}
	//}
	//if (currentState == STATE::LOCK)
	//{
	//	if (framecnt >= skillSet[currentSkill].maxFrame)//끝나면 IDLE로
	//	{
	//		endSkill();
	//	}
	//}
	//else //일반동작
	//{
	//	if (framecnt >= images[getCurrentIndex()].GetMaxFrame())//루프처리
	//	{
	//		framecnt = 0;
	//		timecnt = 0;
	//	}
	//}
	if (framecnt >= images[behaviorMap[currentSkill].imageIdx].GetMaxFrame())//루프처리
	{
		framecnt = 0;
		timecnt = 0;
		currentSkill = behaviorMap[currentSkill].next;
	}
	
	Move(deltaTime);
	
}

void Character2::Render(HDC hdc)
{
	int maxindex = images[behaviorMap[currentSkill].imageIdx].GetMaxFrame();
	images[behaviorMap[currentSkill].imageIdx].Render(hdc, pos.x, pos.y, framecnt, screenWay);
}

void Character2::Move(float deltaTime)
{
	pos.x += ((screenWay ? -1 : 1) * moveWay) * speed * characterSpeed * deltaTime;
}


void Character2::updateCurrentScreenWay(Character2* otherCharacter)
{
	if (pos.x - otherCharacter->pos.x < 0) screenWay = false;
	else if (pos.x - otherCharacter->pos.x > 0) screenWay = true;
}

void Character2::useSkill(string str)
{
	if (str == "")
	{
		return;
	}
	for (auto token : behaviorMap)
	{
		if (str.find(token.first) != string::npos)
		{
			setIdle();
			currentSkill = token.first;
			currentState = STATE::LOCK;

			SKILL& skill = behaviorMap[currentSkill];
			this->damage = skill.damage;
			return;
		}
	}
	
	
}

void Character2::endSkill()
{
	currentSkill = -1;
	setIdle();
}


int Character2::getCurrentIndex()
{
	return behaviorMap[currentSkill].imageIdx;
}
int Character2::getIndex(BEHAVE behave)
{
	int idx = 0;
	switch (behave)
	{
	case BEHAVE::IDLE:
		idx = 0;
		break;
	case BEHAVE::BACK:
		idx = 1;
		break;
	case BEHAVE::WALK:
		idx = 2;
		break;
	case BEHAVE::DOWN:
		idx = 3;
		break;
	case BEHAVE::DASH:
		idx = 4;
		break;
	case BEHAVE::BACKDASH:
		idx = 5;
		break;
	}
	return idx;
}

float* Character2::getCurrentHp()
{
	return &currentHp;
}

float Character2::getMaxHp()
{
	return hp;
}

Image Character2::getProfile()
{
	return *profile;
}

int Character2::getGuardState()
{
	return guardState;
}

//Character::BEHAVE Character::getBehave()
//{
//	return currentState;
//}

Character2::BEHAVE Character2::getBehave()
{
	return currentBehave;
}

void Character2::attack()
{
	SKILL& skill = behaviorMap[currentSkill];
	int d = damage;
	if (skill.reach > (player == 1 ? 1 : -1) * (other->getPos().x - pos.x))
	{
		if (skill.isLowerAttack) //하단 공격일때
		{
			if (other->getGuardState() == 2) //하단 방어일때
			{
				d *= 0.1f;
			}
		}
		else if (skill.isUpperAttack) //상단 공격일때
		{
			if (other->getBehave() == BEHAVE::DOWN) //상대가 숙였을때
			{
				d = 0;
			}
			else if (other->getGuardState() == 1) //상단 방어일때
			{
				d *= 0.1f;
			}
		}
		other->getDamage(d);
	}

}

void Character2::getDamage(float damage)
{
	hp -= damage;
}

void Character2::SetEnemy(Character2* other)
{
	this->other = other;
}

FPOINT Character2::getPos()
{
	return pos;
}
