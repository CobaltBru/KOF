#include "Ryo.h"
#include "Image.h"
#include "KOFKeyManager.h"

Ryo::Ryo()
{
	screenWay = false;
	currentTime = 0.f;
	dashTime = 0.f;
	dy = -20;
}

void Ryo::Update(float deltaTime)
{
	currentTime += deltaTime;

	if (currentState != STATE::PROCESS && !bBackDash)
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
		else if (currentState != STATE::IDLE && currentState != STATE::BACKDASH && currentState != STATE::DASH)
		{
			setIdle();
		}

		if (currentState == STATE::BACKDASH)
		{
			bCheckPreBackDash = true;
			bBackDash = true;
		}
	}

	timecnt += deltaTime;
	framecnt = timecnt / (deltaTime * FRAMESPEED); //현재 프레임 계산

	CheckMaxFrame();

	Move(deltaTime);

	
	//useSkill(currentCommand);

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
		int pixel = pixels.empty() ? 0 : pixels[getIndex()];
		images[getIndex()].Render(hdc, pos.x - pixel, pos.y, framecnt, screenWay);
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

void Ryo::CheckMaxFrame()
{
	if (framecnt >= images[getIndex()].GetMaxFrame())//루프처리
	{
		framecnt = 0;
		timecnt = 0;
	}
}
