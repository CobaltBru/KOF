#include "Chang.h"
#include "Image.h"
#include "KOFKeyManager.h"
#include "Collider.h"
#include "CollisionManager.h"


Chang::Chang() {
	screenWay = false;
	currentTime = 0.f;
	dashTime = 0.f;

	vector<Image> tempImage;

	Image* maiProfile = new Image();
	maiProfile->Init(TEXT("Image/UI/yuri.bmp"), 85 * 1.4, 82 * 1.4, true, RGB(255, 0, 255));

	Image idle;
	idle.Init(L"Image/Chang/Chang_Idle.bmp",576,146, 6, 1, true, RGB(255, 0, 255));
	Image BackWalk;
	BackWalk.Init(L"Image/Chang/Chang_Walk.bmp", 910, 136, 10, 1, true, RGB(255, 0, 255));
	Image Walk;
	Walk.Init(L"Image/Chang/Chang_Walk.bmp", 910, 136, 10, 1, true, RGB(255, 0, 255));
	Image Attack1;
	Attack1.Init(L"Image/Chang/Chang_MiddleAttack.bmp", 685, 146, 5, 1, true, RGB(255, 0, 255));
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

	Image* MiddlePunch = new Image();
	MiddlePunch->Init(L"Image/Chang/Chang_MiddleAttack.bmp", 685, 146, 5, 1, true, RGB(255, 0, 255));
	Image* PowerPunch = new Image();
	PowerPunch->Init(L"Image/Chang/Chang_StrongAttack.bmp", 1830, 164, 10, 1, true, RGB(255, 0, 255));
	Image* BottomKick = new Image();
	BottomKick->Init(L"Image/Chang/Chang_ButtomKick.bmp", 625, 144, 5, 1, true, RGB(255, 0, 255));
	Image* PowerKick = new Image();
	PowerKick->Init(L"Image/Chang/Chang_StrongKick.bmp", 959, 132, 7, 1, true, RGB(255, 0, 255));

	pushSkill("H", MiddlePunch, 5, 5, 50, false, true, 0);
	pushSkill("Y", PowerPunch, 10, 10, 100, true, false, 0);
	pushSkill("G", BottomKick, 5, 7, 60, false, true, 0);
	pushSkill("T", PowerKick, 7, 10, 70, true, false, 0);

	this->Init(1, maiProfile, { 250,250 }, 100.f, 100.f, tempImage);

	
};
void Chang::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void Chang::Render(HDC hdc)
{
	if (currentState == STATE::PROCESS)
	{
		skillSet[currentSkill].image->Render(hdc, pos.x - 75, pos.y - 60, framecnt, screenWay);
	}
	else
	{
		if (screenWay)
		{
			images[getIndex()].Render(hdc, pos.x - 40, pos.y - 60, framecnt, screenWay);
		}
		else
		{
			images[getIndex()].Render(hdc, pos.x - 35, pos.y - 55, framecnt, screenWay);
		}
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
void Chang::InitCollider() {
	collider = new Collider(this, { 15.f, 20.f }, { 100.f, 150.f }, COLLIDER_TYPE::Rect);
	CollisionManager* manager = CollisionManager::GetInstance();

	manager->AddObject(OBJID::OBJ_CHARACTER, collider);

	collider->DebugRender(true);
}
