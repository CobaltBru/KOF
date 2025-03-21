#include "Ryo.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Hadogen.h"
#include "ObjectManager.h"
Ryo::Ryo()
	:currentTime(0.f), aDashTime(0.f), bDashTime(0.f), KeyBufferTime(0.f), dy(-20), gravity(4), bCheckPreBackDash(false), bBackDash(false), bSkip(false), bFirstAttack(false)
{
}

void Ryo::InitCollider()
{
	collider = new Collider(this, { 30.f, 80.f }, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);
}

void Ryo::pushSkill(string command, Image* image, int maxFrame, int damage, int reach, bool isUpperAttack, bool isLowerAttack, int attackFrame, int skipFrame, FPOINT collisionPivot)
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

	otherSkillInfo.push_back({ skipFrame ,collisionPivot });
}

void Ryo::Update(float deltaTime)
{
	currentTime += deltaTime;

	if (!bDead && currentHp <= 0)
	{
		bDead = true;
		currentState = STATE::DEAD;
		framecnt = 0;
		timecnt = 0.f;
	}

	if (!bDead && (currentState != STATE::PROCESS || bSkip) && !bBackDash && !bBlockHit)
	{
		bool bA = KeyManager::GetInstance()->IsOnceKeyUp('A');
		bool bD = KeyManager::GetInstance()->IsOnceKeyUp('D');
		bool bS = KeyManager::GetInstance()->IsOnceKeyUp('S');

		if (bA || bD)
		{
			if (currentState == STATE::DASH)
			{
				aDashTime = 0.f;
				bDashTime = 0.f;
				setIdle();
			}
			else if (currentState == STATE::BACKDASH)
			{
				aDashTime = 0.f;
				bDashTime = 0.f;
			}
			else if (bCheckPreBackDash)
				bCheckPreBackDash = false;
			else
				bA ? aDashTime = currentTime : bDashTime = currentTime;
		}

		StateUpdate(deltaTime);
	}

	timecnt += deltaTime;
	framecnt = timecnt / (deltaTime * 5); //현재 프레임 계산

	CollisionUpdate();
	SkipSkillFrame();
	CheckMaxFrame();

	Move(deltaTime);

	//__super::Update(deltaTime);
}

void Ryo::Render(HDC hdc)
{
	if (currentState == STATE::PROCESS)
		skillSet[currentSkill].image->Render(hdc, pos.x, pos.y, framecnt, screenWay);
	else
	{
		const int idx = bDead ? (int)STATE::DEAD : GetIndex();
		images[idx].Render(hdc, pos.x, pos.y, framecnt, screenWay);
	}
}

void Ryo::StateUpdate(float deltaTime)
{
	currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);

	basicKeys[EKeyType::KEY_W] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_W);
	basicKeys[EKeyType::KEY_A] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
	basicKeys[EKeyType::KEY_S] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
	basicKeys[EKeyType::KEY_D] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);

	//if (basicKeys[EKeyType::KEY_W] && basicKeys[EKeyType::KEY_D])		//대각
	//{

	//}
	//else if (basicKeys[EKeyType::KEY_W] && basicKeys[EKeyType::KEY_A])
	//{

	//}
	//else if (basicKeys[EKeyType::KEY_S] && basicKeys[EKeyType::KEY_A])
	//{

	//}
	//else if (basicKeys[EKeyType::KEY_S] && basicKeys[EKeyType::KEY_D])
	//{
	//}
	if (basicKeys[EKeyType::KEY_A] && aDashTime > 0.0001f && currentTime - aDashTime < 0.2f)		// 대쉬
	{
		screenWay ? setDash() : setBackDash();
		aDashTime = 0.f;
	}
	else if (basicKeys[EKeyType::KEY_D] && bDashTime > 0.0001f && currentTime - bDashTime < 0.2f)
	{
		screenWay ? setBackDash() : setDash();
		bDashTime = 0.f;
	}
	else if (basicKeys[EKeyType::KEY_W])	//일반 키입력
	{

	}
	else if (basicKeys[EKeyType::KEY_S])
	{
		setDown();
		if (!screenWay)
			guardState = basicKeys[EKeyType::KEY_A] ? 2 : 0;
		else
			guardState = basicKeys[EKeyType::KEY_D] ? 2 : 0;
	}
	else if (basicKeys[EKeyType::KEY_A] && currentState != STATE::BACKDASH && currentState != STATE::DASH)
	{
		screenWay ? setWalk() : setBack();
	}
	else if (basicKeys[EKeyType::KEY_D] && currentState != STATE::BACKDASH && currentState != STATE::DASH)
	{
		screenWay ? setBack() : setWalk();
	}
	else if (currentState != STATE::IDLE && currentState != STATE::BACKDASH && currentState != STATE::DASH && !bSkip)
	{
		setIdle();
	}

	if (currentState == STATE::BACKDASH)
	{
		bCheckPreBackDash = true;
		bBackDash = true;
	}
	if (bBlockHit)
		speed = 0.f;
	if (currentTime - KeyBufferTime > 0.2f)
	{
		useSkill(currentCommand);
		KeyBufferTime = currentTime;
	}
}

void Ryo::Move(float deltaTime)
{
	if (bBackDash)
	{
		dy += gravity;

		pos.x += ((screenWay ? -1 : 1) * moveWay) * speed * characterSpeed * deltaTime;
		pos.y += dy;

		if (pos.y >= 320.f)
		{
			bBackDash = false;
			dy = -20;
			pos.y = 320.f;
			setIdle();
		}
	}
	else
		pos.x += ((screenWay ? -1 : 1) * moveWay) * speed * characterSpeed * deltaTime;
}

void Ryo::useSkill(string str)
{
	for (int i = 0; i < skillSet.size(); i++)
	{
		if (str.find(skillSet[i].command) != string::npos)
		{
			currentSkill = i;
			currentState = STATE::PROCESS;
			framecnt = 0;
			timecnt = 0;
			SKILL& skill = skillSet[currentSkill];
			this->damage = skill.damage;
			//this->moveWay = skill.way;
			speed = 0;
			bFirstAttack = true;
			KOFKeyManager::GetInstance()->ClearPlayerBuffer(player);
			return;
		}
	}
}

void Ryo::CollisionUpdate()
{
	if (currentState != STATE::PROCESS)
		return;

	if (bFirstAttack && framecnt == skillSet[currentSkill].attackFrame)
	{
		FPOINT position = { pos.x + collider->GetPivot().x + otherSkillInfo[currentSkill].collisionPivot.x,
			pos.y + collider->GetPivot().y + otherSkillInfo[currentSkill].collisionPivot.y };

		if (currentSkill == 0 || currentSkill == 1)
		{
			Hadogen* hadogen = new Hadogen();
			hadogen->Init(position, otherSkillInfo[currentSkill].collisionPivot, skillSet[currentSkill].damage, currentSkill, skillSet[currentSkill].isUpperAttack);

			if (ObjectManager* ObjMgr = ObjectManager::GetInstance())
				ObjMgr->AddObject(OBJID::OBJ_CHARACTER, hadogen);
		}
		else
		{
			HitResult hit;
			FPOINT endPoint = { position.x + (skillSet[currentSkill].reach * (screenWay ? -1 : 1)), position.y };
			if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, position, endPoint, this, true))
			{
				if (Character* OtherCharacter = dynamic_cast<Character*>(hit.Actors[0]))
				{
					attack(OtherCharacter, endPoint);
				}
			}
		}

		bFirstAttack = false;
	}
}

void Ryo::SkipSkillFrame()
{
	if (currentState == STATE::PROCESS)
	{
		if (framecnt >= otherSkillInfo[currentSkill].skipFrame)
			bSkip = true;
		else
			bSkip = false;
	}
	else
		bSkip = false;
}

void Ryo::CheckMaxFrame()
{
	if (currentState == STATE::PROCESS)
	{
		if (framecnt >= skillSet[currentSkill].maxFrame)
		{
			framecnt = 0;
			timecnt = 0;
			endSkill();
		}
	}
	else
	{
		const int idx = bDead ? (int)STATE::DEAD : GetIndex();
		if (framecnt >= images[idx].GetMaxFrame())//루프처리
		{
			if (!bDead)
			{
				framecnt = 0;
				timecnt = 0;
				bBlockHit = false;
			}
			else
				framecnt = images[idx].GetMaxFrame() - 1;
		}
	}
}
