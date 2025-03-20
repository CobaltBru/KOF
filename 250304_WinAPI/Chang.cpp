#include "Chang.h"
#include "Image.h"
#include "KOFKeyManager.h"

Chang::Chang() {
	screenWay = false;
	currentTime = 0.f;
	dashTime = 0.f;

	vector<Image> tempImage;

	Image idle;
	idle.Init(L"Image/Chang/Chang_Idle.bmp",576,146, 6, 1, true, RGB(255, 0, 255));
	Image BackWalk;
	BackWalk.Init(L"Image/Chang/Chang_Walk.bmp", 910, 136, 10, 1, true, RGB(255, 0, 255));
	Image Walk;
	Walk.Init(L"Image/Chang/Chang_Walk.bmp", 910, 136, 10, 1, true, RGB(255, 0, 255));
	Image Attack1;
	Attack1.Init(L"Image/Chang/Chang_WeakAttack.bmp", 685, 146, 5, 1, true, RGB(255, 0, 255));
	Image Walk3;
	Walk3.Init(L"Image/Chang/Chang_Walk.bmp", 910, 136, 10, 1, true, RGB(255, 0, 255));
	Image Walk4;
	Walk4.Init(L"Image/Chang/Chang_Jump.bmp", 644, 163, 7, 1, true, RGB(255, 0, 255));

	
	tempImage.push_back(idle);
	tempImage.push_back(BackWalk);
	tempImage.push_back(Walk);
	tempImage.push_back(Attack1);
	tempImage.push_back(Walk3);
	tempImage.push_back(Walk4);

	this->Init(1, new Image(), { 250,250 }, 200.f, 100.f, tempImage);
	
};
void Chang::Update(float deltaTime)
{
	currentTime += deltaTime;

	currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);

	bool keyA = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
	bool keyS = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
	bool keyD = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);
	bool keyW = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_W);

	if (keyA && dashTime > 0.0001f && currentTime - dashTime > 0.3f)
	{
		dashTime = currentTime;
	}
	else if (keyA)
	{
		if (screenWay == false) //뒷걸음질
		{
			moveWay = -1;
			speed = 0.7f;
			if (currentState == STATE::BACK) currentState = STATE::BACK;
			else currentState = STATE::BACK;
		}
		else //앞으로 
		{
			moveWay = 1;
			speed = 1.0f;
			if (currentState == STATE::WALK) currentState = STATE::DASH;
			else currentState = STATE::WALK;
		}
	}
	else if (keyD)
	{
		if (screenWay == false) //앞으로
		{
			moveWay = 1;
			speed = 1.0f;
			if (currentState == STATE::WALK) currentState = STATE::DASH;
			else currentState = STATE::WALK;
		}
		else //뒷걸음질
		{
			moveWay = -1;
			speed = 0.7f;
			if (currentState == STATE::BACK) currentState = STATE::BACK;
			else currentState = STATE::BACK;
		}
	}
	else if (keyS) //숙이기
	{
		speed = 0;
		currentState = STATE::DOWN;
	}
	else if (keyW)
	{
		
		
		moveWay = 1;
		speed = 0.5f;

		Jump(deltaTime);
		currentState = STATE::BACKDASH;
		
		
	}
	else
	{
		speed = 0;
		currentState = STATE::IDLE;
	}

	useSkill(currentCommand);

	if (currentState != STATE::IDLE)
	{
		timecnt += deltaTime;
		framecnt = timecnt / (deltaTime * FRAMESPEED); //현재 프레임 계산
		if (currentState == STATE::PROCESS) //기술중
		{
			if (framecnt >= skillSet[currentSkill].maxFrame)//끝나면 IDLE로
			{
				endSkill();
			}
		}
	}
	else
	{
			timecnt += deltaTime;
			framecnt = timecnt / (deltaTime * FRAMESPEED); //현재 프레임 계산		
	}
	CheckMaxFrame();
	

	Move(deltaTime);
}

void Chang::Render(HDC hdc)
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

void Chang::Jump(float deltaTime)
{
	bool JumpCheck = false;
	if (pos.y >=0 && pos.y<=300)
	{
		JumpCheck = true;
	}
	int jumpFrame= timecnt /(deltaTime * FRAMESPEED);
	if (jumpFrame > 0 && jumpFrame < images[getIndex()].GetMaxFrame()/2&& JumpCheck)
	{
		pos.y -= 6.0f;
	}
	else if (jumpFrame >= images[getIndex()].GetMaxFrame() / 2 && jumpFrame < images[getIndex()].GetMaxFrame()-1&& JumpCheck)
	{
		if (pos.y >= 250.f)
		{
			pos.y = 250;
		}
		pos.y += 6.f;
		
	}
	else if (jumpFrame <= images[getIndex()].GetMaxFrame())
	{
		pos.y = 250.f;

	}

}

void Chang::CheckMaxFrame()
{
	if (framecnt >= images[getIndex()].GetMaxFrame())//루프처리
	{
		framecnt = 0;
		timecnt = 0;
	}

}
