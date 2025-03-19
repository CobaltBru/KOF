#include "Character.h"
#include "Image.h"

Character::Character()
{
	player = 0;

	pos = { 0,0 };
	screenWay = true;
	moveWay = 1;
	characterSpeed = 5.0f;
	speed = 0;
	hp = 100;
	currentHp = hp;
	damage = 0;
	//images
	//maxFrames
	currentCommand = "";

	//skillSet
	currentSkill = -1;

	framecnt = 0;
	timecnt = 0;

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
void Character::Init(int player, FPOINT pos, float characterSpeed,
	float hp, vector<Image>images, vector<int> maxFrames)
{
	this->player = player;
	this->pos = pos;
	this->screenWay = player == 1 ? true : false;
	this->moveWay = 1;
	this->characterSpeed = characterSpeed;
	this->speed = 0;
	this->hp = hp;
	this->currentHp = this->hp;
	this->damage = 0;
	this->images = images;
	this->maxFrames = maxFrames;
	this->currentCommand = "";
	this->currentSkill = -1;
	this->framecnt = 0;
	this->timecnt = 0;
	this->currentState = STATE::IDLE;
}

void Character::Release()
{
}

//뒷걷기, 앞걷기, 숙이기, 숙이고뒷걷기,숙이고앞걷기, 앞대쉬, 백대쉬 순으로 넣어주세요
void Character::pushCommon(Image* image, int maxFrame)
{
	images.push_back(*image);
	maxFrames.push_back(maxFrame);
}

void Character::pushSkill(string command, Image* image, int maxFrame,
			int damage, int reach, bool isUpperAttack, bool isLowerAttack,
			float startTime, float moveTime, int way, int speed)
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
	skill.moveTime = moveTime;
	skill.way = way;
	skill.speed = speed;
	
	skillSet.push_back(skill);
}

void Character::Update(float deltaTime)
{
	//키입력을 받을 수 있는 상태
	if (currentState != STATE::PROCESS)
	{
		if (currentCommand == "A")
		{
			if (screenWay == true) //뒷걸음질
			{
				moveWay = -1;
				speed = 0.7f;
				if(currentState == STATE::DOWN)currentState = STATE::DOWNBACK;
				else currentState = STATE::BACK;
			}
			else //앞으로 
			{
				moveWay = 1;
				speed = 1.0f;
				if (currentState == STATE::DOWN)currentState = STATE::DOWNWALK;
				else currentState = STATE::WALK;
			}
		}
		else if (currentCommand == "D")
		{
			if (screenWay == true) //앞으로
			{
				moveWay = 1; 
				speed = 1.0f;
				if (currentState == STATE::DOWN)currentState = STATE::DOWNWALK;
				else currentState = STATE::WALK;
			}
			else //뒷걸음질
			{
				moveWay = -1;
				speed = 0.7f;
				if (currentState == STATE::DOWN)currentState = STATE::DOWNBACK;
				else currentState = STATE::BACK;
			}
		}
		else if (currentCommand == "S") //숙이기
		{
			speed = 0;
			currentState = STATE::DOWN;
		}
		else if (currentCommand == "AA") 
		{
			if (screenWay == true) //백대쉬
			{
				speed = 3.0f;
				moveWay = -1;
				currentState = STATE::BACKDASH;
			}
			else //앞대쉬
			{
				speed = 3.0f;
				moveWay = 1;
				currentState = STATE::DASH;
			}
		}
		else if (currentCommand == "DD")
		{
			if (screenWay == true) //앞대쉬
			{
				speed = 3.0f;
				moveWay = 1;
				currentState = STATE::DASH;
			}
			else //백대쉬
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

	//동작중
	if (currentState != STATE::IDLE)
	{
		timecnt += deltaTime;
		framecnt = timecnt / (deltaTime); //현재 프레임 계산
		if (currentState == STATE::PROCESS) //기술중
		{
			if (framecnt >= skillSet[currentSkill].maxFrame)//끝나면 IDLE로
			{
				endSkill();
			}
		}
		else //일반동작
		{
			if (framecnt >= maxFrames[getIndex()])//루프처리
			{
				framecnt = 0;
				timecnt = 0;
			}
		}
	}
	
	
	//기본상태일시 초기화
	if (currentState == STATE::IDLE) 
	{
		timecnt == 0;
		framecnt = 0;
		speed = 0;
	}
	
	
	Move(deltaTime);
	
}

void Character::Render(HDC hdc)
{
	/*if (currentState != STATE::IDLE)
	{*/
		if (currentState == STATE::PROCESS)
		{
			skillSet[currentSkill].image->Render(hdc, pos.x, pos.y, framecnt, screenWay);
		}
		else
		{
			images[getIndex() + 1].Render(hdc, pos.x, pos.y, framecnt, screenWay);
		}
	//}
}

void Character::Move(float deltaTime)
{
	pos.x += ((screenWay ? 1 : -1) * moveWay) * speed * deltaTime;
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
	this->speed = 0;
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
