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
	// ���� ƽ  �÷��̾�� �ؾ���
	ULONGLONG currentUpdateTime1 = 0;
	ULONGLONG currentUpdateTime2 = 0;

	//Ű�� �޴� ���� 1p, 2p
	queue<pair<int,int>> playerInput1;
	queue<pair<int, int>> playerInput2;

	//������ Ű 1p, 2p

};

