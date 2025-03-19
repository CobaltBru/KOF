#include "Ryo.h"
#include "KOFKeyManager.h"

Ryo::Ryo()
{
	screenWay = false;
	currentTime = 0.f;
	dashTime = 0.f;
}

void Ryo::Update(float deltaTime)
{
	//currentTime += deltaTime;

	//currentCommand = KOFKeyManager::GetInstance()->GetPlayerCommand(player);

	//bool keyA = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_A);
	//bool keyS = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_S);
	//bool keyD = KOFKeyManager::GetInstance()->HasPlayerMoveKey(player, EKeyType::KEY_D);
	//if (keyA && dashTime > 0.0001f && currentTime - dashTime > 0.3f)
	//{
	//	dashTime = currentTime;
	//}
	//else if (keyA)
	//{
	//	if (screenWay == false) //뒷걸음질
	//	{
	//		moveWay = -1;
	//		speed = 0.7f;
	//		if (currentState == STATE::BACK) currentState = STATE::BACK;
	//		else currentState = STATE::BACK;
	//	}
	//	else //앞으로 
	//	{
	//		moveWay = 1;
	//		speed = 1.0f;
	//		if (currentState == STATE::WALK) currentState = STATE::DASH;
	//		else currentState = STATE::WALK;
	//	}
	//}
	//else if (keyD)
	//{
	//	if (screenWay == false) //앞으로
	//	{
	//		moveWay = 1;
	//		speed = 1.0f;
	//		if (currentState == STATE::WALK) currentState = STATE::DASH;
	//		else currentState = STATE::WALK;
	//	}
	//	else //뒷걸음질
	//	{
	//		moveWay = -1;
	//		speed = 0.7f;
	//		if (currentState == STATE::BACK) currentState = STATE::BACK;
	//		else currentState = STATE::BACK;
	//	}
	//}
	//else if (keyS) //숙이기
	//{
	//	speed = 0;
	//	currentState = STATE::DOWN;
	//}
	//else
	//{
	//	speed = 0;
	//	currentState = STATE::IDLE;
	//}



	__super::Update(deltaTime);
}
