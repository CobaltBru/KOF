#include "Ryo.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include "Collider.h"
#include "CollisionManager.h"

Ryo::Ryo()
{
	screenWay = false;
	currentTime = 0.f;
	dashTime = 0.f;
	dy = -20;
}

void Ryo::InitCollider()
{
	collider = new Collider(this, { 30.f, 80.f }, { 50.f, 100.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);
}

void Ryo::Update(float deltaTime)
{
	currentTime += deltaTime;

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
	{
		HitResult hit;
		FPOINT position = { pos.x + collider->GetPivot().x, pos.y + collider->GetPivot().y };
		if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, position, { position.x + 100.f, position.y }, this, true))
		{
			int a = 10;
			//dynamic_cast<asdf>(hit.Actors[0]);
		}
	}

	if ((currentState != STATE::PROCESS || bSkip) && !bBackDash)
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

		currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);

		basicKeys[EKeyType::KEY_W] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_W);
		basicKeys[EKeyType::KEY_A] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
		basicKeys[EKeyType::KEY_S] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
		basicKeys[EKeyType::KEY_D] = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);

		if (basicKeys[EKeyType::KEY_W] && basicKeys[EKeyType::KEY_D])		//대각
		{

		}
		else if (basicKeys[EKeyType::KEY_W] && basicKeys[EKeyType::KEY_A])
		{

		}
		else if (basicKeys[EKeyType::KEY_S] && basicKeys[EKeyType::KEY_A])
		{

		}
		else if (basicKeys[EKeyType::KEY_S] && basicKeys[EKeyType::KEY_D])
		{

		}
		else if (basicKeys[EKeyType::KEY_A] && aDashTime > 0.0001f && currentTime - aDashTime < 0.2f)		// 대쉬
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
		else if (basicKeys[EKeyType::KEY_A] && currentState != STATE::BACKDASH && currentState != STATE::DASH)
		{
			screenWay ? setWalk() : setBack();
		}
		else if (basicKeys[EKeyType::KEY_S])
		{
			setDown();
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

		useSkill(currentCommand);
	}

	timecnt += deltaTime;
	framecnt = timecnt / (deltaTime * 5); //현재 프레임 계산

	SkipSkillFrame();
	CheckMaxFrame();

	Move(deltaTime);

	//__super::Update(deltaTime);
}

void Ryo::Render(HDC hdc)
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

void Ryo::Move(float deltaTime)
{
	if (bBackDash)
	{
		dy += gravity;

		pos.x += ((screenWay ? -1 : 1) * moveWay) * speed * characterSpeed * deltaTime;
		pos.y += dy;

		if (pos.y >= 250)
		{
			bBackDash = false;
			dy = -20;
			pos.y = 250.f;
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
			//if (skill.startTime <= 0.0f) this->speed = skill.speed;
			KOFKeyManager::GetInstance()->ClearPlayerBuffer(player);
			return;
		}
	}
}

void Ryo::SkipSkillFrame()
{
	if (currentState == STATE::PROCESS)
	{
		if (framecnt >= skipFrames[currentSkill])
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
		if (framecnt >= images[getIndex()].GetMaxFrame())//루프처리
		{
			framecnt = 0;
			timecnt = 0;
		}
	}
}
