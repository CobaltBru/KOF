#include "Effect.h"
#include "Image.h"

Effect::Effect()
	:bDead(false), bFilp(false),currentTime(0.f),currentFrame(0.f),pos({0.f,0.f})
{
}
Effect::~Effect()
{
}

void Effect::Init(Image* image, FPOINT position, bool bFilp)
{
	this->image = image;
	this->pos = { position.x - ((image->GetWidth() / image->GetMaxFrame()) * 0.5f), position.y - (image->GetHeight() * 0.5f)};
	this->bFilp = bFilp;
}

void Effect::Update(float deltaTime)
{
	if (!bDead)
	{
		currentTime += deltaTime;
		currentFrame = currentTime / (deltaTime * 5.f);

		if (image && currentFrame >= image->GetMaxFrame())
			bDead = true;
	}
}

void Effect::Render(HDC hdc)
{
	image->Render(hdc, pos.x, pos.y, currentFrame, bFilp);
}

void Effect::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}
