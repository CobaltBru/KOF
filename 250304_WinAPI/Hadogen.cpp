#include "Hadogen.h"
#include "Image.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Character.h"

Hadogen::Hadogen()
	:bDead(false), bRender(true)
{
}

void Hadogen::Init(FPOINT pos, FPOINT pivot,int damage)
{
	HadogenImage = new Image();
	HadogenImage->Init(L"Image/Ryo/hadogen.bmp", 600, 200, 6, 1, true, RGB(255, 0, 255));

	DestroyImage = new Image();
	DestroyImage->Init(L"Image/Ryo/HadogenDead.bmp", 900, 200, 9, 1, true, RGB(255, 0, 255));

	this->pos.x = pos.x + pivot.x;
	this->pos.y = pos.y + pivot.y;
	this->damage = damage;
}

void Hadogen::Release()
{
	if (HadogenImage != nullptr)
	{
		HadogenImage->Release();
		delete HadogenImage;
		HadogenImage = nullptr;
	}
	if (DestroyImage != nullptr)
	{
		DestroyImage->Release();
		delete DestroyImage;
		DestroyImage = nullptr;
	}
}

void Hadogen::Update(float TimeDelta)
{
	timeCnt += TimeDelta;
	frameCnt = timeCnt / (TimeDelta * 5);

	if(!bDead)
		pos.x += 10.f;

	if(bRender)
	{
		CheckMaxFrame();
		CollisionUpdate();
	}
}

void Hadogen::Render(HDC hdc)
{
	if (bRender)
		bDead ? DestroyImage->Render(hdc, pos.x, pos.y, frameCnt) : HadogenImage->Render(hdc, pos.x, pos.y, frameCnt);
}

void Hadogen::CheckMaxFrame()
{
	const int maxFrame = bDead ? 9 : 6;
	if (frameCnt >= maxFrame)//루프처리
	{
		timeCnt = 0;
		frameCnt = 0;

		if (bDead)
			bRender = false;
	}
}

void Hadogen::CollisionUpdate()
{
	if (!bDead)
	{
		HitResult hit;
		FPOINT position = { pos.x + 50.f, pos.y + 100.f };
		if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, position, position, this, true))
		{
			if (Character* OtherCharacter = dynamic_cast<Character*>(hit.Actors[0]))
			{
				OtherCharacter->getDamage(damage);
				//attack(OtherCharacter);
				bDead = true;
			}
		}
	}
}

Hadogen::~Hadogen()
{
}
