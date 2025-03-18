#pragma once
#include "Singleton.h"
#include "config.h"
#include <queue>

#define KEYINTERVAL 1000

class KOFKeyManager : public Singleton<KOFKeyManager>
{
public:
	HRESULT Init();
	void Update();
	void Release();

	void Player1Update();
	void Player2Update();

	void Player1CommandUpdate();
	void Player2CommandUpdate();
	
private:
	// 현재 틱  플레이어마다 해야함
	ULONGLONG currentUpdateTime1 = 0;
	ULONGLONG currentUpdateTime2 = 0;

	//키를 받는 변수 1p, 2p
	queue<pair<int,int>> playerInput1;
	queue<pair<int, int>> playerInput2;

	//결정된 키 1p, 2p

};

