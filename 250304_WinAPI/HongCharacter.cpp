#include "HongCharacter.h"
#include "Collider.h"
void HongCharacter::Init()
{
	collider = new Collider(this, Pos);
}

void HongCharacter::Release()
{
	collider = nullptr;
}

void HongCharacter::Update(float TimeDelta)
{

}

void HongCharacter::Render(HDC hdc)
{
}

HongCharacter::HongCharacter()
{
}

HongCharacter::~HongCharacter()
{

}
