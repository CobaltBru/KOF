#include "Character2.h"
#include "Animation.h"
#include "KOFKeyManager.h"
#include "Image.h"

Character2::Character2()
{
	
}

Character2::~Character2()
{
	
}

void Character2::Init(int player, Image* profile, FPOINT pos, float characterSpeed, int maxHp)
{
	animation = new Animation;
	this->player = player;
	this->profile = profile;
	screenWay = player == 1 ? false : true;
	this->moveDir = 1;
	this->characterSpeed = characterSpeed;
	this->currentSpeed = 0;
	SetPos(pos);
	this->maxHp = maxHp;
	memset(currentKeys, false, sizeof(currentKeys));
	memset(oldKeys, false, sizeof(oldKeys));
	oldState = STATE::IDLE;
	currentState = STATE::IDLE;
	flag = INTERRUPTFLAG::OPEN;
	blockState = BLOCK::NONE;

	doubleClickTimerA = 0;
	clickedKeyA = false;
	doubleClickTimerA = 0;
	clickedKeyA = false;
}

void Character2::Release()
{
	delete animation;
}

void Character2::Update(float deltaTime)
{
	
	currentKeys[EKeyType::KEY_W] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_W);
	currentKeys[EKeyType::KEY_A] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
	currentKeys[EKeyType::KEY_S] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
	currentKeys[EKeyType::KEY_D] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);
	//A키와 D키의 동작을 플레이어에 관계없이 통일
	if (player == 2) swap(currentKeys[EKeyType::KEY_A], currentKeys[EKeyType::KEY_D]);
	currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);
	
	if (clickedKeyA) doubleClickTimerA += deltaTime;
	if (clickedKeyD) doubleClickTimerD += deltaTime;
	
	if (flag == INTERRUPTFLAG::OPEN) //열려있을때만 동작
	{
		if (currentKeys[EKeyType::KEY_S]) //숙이기
		{
			currentState = STATE::DOWN;
			if (currentKeys[EKeyType::KEY_A]) blockState = BLOCK::LOWER;
			else blockState = BLOCK::NONE;
		}
		else if (currentKeys[EKeyType::KEY_A]) //뒤
		{
			blockState = BLOCK::UPPER;
			currentState = STATE::BACK;
		}
		else if (currentKeys[EKeyType::KEY_D]) //앞
		{
			if (currentState != STATE::DASH)
			{
				currentState = STATE::WALK;
			}
		}

		//각 키 해제한 순간
		if (isJustReleased(EKeyType::KEY_S)) 
		{
			currentState = STATE::IDLE;
		}
		if (isJustReleased(EKeyType::KEY_A)) 
		{
			if (!currentKeys[EKeyType::KEY_S]) currentState = STATE::IDLE;
			blockState = BLOCK::NONE;

		}
		if (isJustReleased(EKeyType::KEY_D))
		{
			currentState = STATE::IDLE;
		}

		//각 키 누른 순간
		if (isJustPressed(EKeyType::KEY_S))
		{

		}
		if (isJustPressed(EKeyType::KEY_A))
		{
			if (doubleClickCheck(EKeyType::KEY_A))
			{
				currentState = STATE::BACKDASH;
			}
		}
		if (isJustPressed(EKeyType::KEY_D))
		{
			if (doubleClickCheck(EKeyType::KEY_D))
			{
				currentState = STATE::DASH;
			}
		}

	}


	animation->Update(deltaTime);

	for (int i = 0; i < 4; i++)oldKeys[i] = currentKeys[i];
	StateProcess();
	Move(deltaTime);
}

void Character2::Render(HDC hdc)
{
	animation->Render(hdc, GetPos(), screenWay);
}
void Character2::Move(float deltaTime)
{
	pos.x += (screenWay ? -1 : 1) * moveDir * characterSpeed * currentSpeed * deltaTime;
}
void Character2::StateProcess()
{

	if (oldState != currentState)
	{
		switch (currentState)
		{
		case STATE::IDLE:
			currentSpeed = 0;
			timer = 0;
			currentFrame = 0;
			animation->Play("IDLE");
			break;
		case STATE::BACK:
			currentSpeed = 0.7;
			moveDir = -1;
			animation->Play("BACK");
			break;
		case STATE::WALK:
			currentSpeed = 1.0;
			moveDir = 1;
			animation->Play("WALK");
			break;
		case STATE::DOWN:
			currentSpeed = 0;
			animation->Play("DOWN");
			break;
		case STATE::DASH:
			currentSpeed = 3.0;
			moveDir = 1;
			animation->Play("DASH");
			break;
		case STATE::BACKDASH:
			currentSpeed = 3.0;
			moveDir = -1;
			animation->Play("BACKDASH");
			break;
		case STATE::BLOCKUPPER:
			break;
		case STATE::BLOCKLOWER:
			break;
		case STATE::SKILL:
			break;
		}
	}
	oldState = currentState;
}
bool Character2::isJustPressed(int key)
{
	return (!oldKeys[key] && currentKeys[key]);
}
bool Character2::isJustReleased(int key)
{
	return (oldKeys[key] && !currentKeys[key]);
}
bool Character2::isKeepPressed(int key)
{
	return (oldKeys[key] && currentKeys[key]);
}
bool Character2::isKeepReleased(int key)
{
	return (!oldKeys[key] && !currentKeys[key]);
}
bool Character2::doubleClickCheck(int key)
{
	if (key == EKeyType::KEY_A)
	{
		if (!clickedKeyA)
		{
			clickedKeyA = true;
			return false;
		}
		else
		{
			if (doubleClickTimerA < 0.2f)
			{
				doubleClickTimerA = 0;
				clickedKeyA = false;
				return true;
			}
			else
			{
				doubleClickTimerA = 0;
				return false;
			}
		}
	}
	else if (key == EKeyType::KEY_D)
	{
		if (!clickedKeyD)
		{
			clickedKeyD = true;
			return false;
		}
		else
		{
			if (doubleClickTimerD < 0.2f)
			{
				doubleClickTimerD = 0;
				clickedKeyD = false;
				return true;
			}
			else
			{
				doubleClickTimerD = 0;
				return false;
			}
		}
	}
}
void Character2::PushAnimation(string name,Image* image, float frameSpeed, int flag1, int flag2)
{
	//animation->PushTask(name, image, frameSpeed, flag1, flag2);
}

void Character2::PushAnimation(string name,Image* image, float frameSpeed, int flag1, int flag2, string next)
{
	//animation->PushTask(name, image, frameSpeed, flag1, flag2, next);
}



Image Character2::getProfile()
{
	return *profile;
}
