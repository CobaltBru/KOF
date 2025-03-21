#include "Hadogen.h"
#include "Image.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "Character.h"

Hadogen::Hadogen()
	:bDead(false), bRender(true), bUpperAttack(false), hadogenMaxFrame(0), collisionPivot({0,0})
{
}

void Hadogen::Init(FPOINT pos, FPOINT pivot,int damage, int type, bool bUpperAttack)
{
	HadogenImage = new Image();
	if (type)
	{
		HadogenImage->Init(L"Image/Ryo/6by.bmp", 100, 63, 1, 1, true, RGB(255, 0, 255));
		hadogenMaxFrame = 1;
		collisionPivot = { 100 * 0.5f,63 * 0.5f };
	}
	else
	{
		HadogenImage->Init(L"Image/Ryo/hadogen.bmp", 600, 200, 6, 1, true, RGB(255, 0, 255));
		hadogenMaxFrame = 6;
		collisionPivot = { 100 * 0.5f,200 * 0.5f };
	}

	DestroyImage = new Image();
	DestroyImage->Init(L"Image/Ryo/HadogenDead.bmp", 900, 200, 9, 1, true, RGB(255, 0, 255));

	this->pos.x = pos.x + pivot.x;
	this->pos.y = pos.y + pivot.y;
	this->damage = damage;
	this->bUpperAttack = bUpperAttack;
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
	{
		if(hadogenMaxFrame == 1)
			bDead ? DestroyImage->Render(hdc, pos.x, pos.y - (collisionPivot.y * 2), frameCnt) : HadogenImage->Render(hdc, pos.x, pos.y, frameCnt);
		else
			bDead ? DestroyImage->Render(hdc, pos.x, pos.y, frameCnt) : HadogenImage->Render(hdc, pos.x, pos.y, frameCnt);
	}
}

void Hadogen::CheckMaxFrame()
{
	const int maxFrame = bDead ? 9 : hadogenMaxFrame;
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
		FPOINT position = { pos.x + collisionPivot.x, pos.y + collisionPivot.y};
		if (CollisionManager::GetInstance()->LineTraceByObject(hit, OBJ_CHARACTER, position, position, this, true))
		{
			if (Character* OtherCharacter = dynamic_cast<Character*>(hit.Actors[0]))
			{
				OtherCharacter->hit(damage, bUpperAttack, position);				
				bDead = true;
			}
		}
	}
}

Hadogen::~Hadogen()
{
}
