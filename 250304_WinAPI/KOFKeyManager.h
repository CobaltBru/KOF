#pragma once
#include "config.h"
#include <deque>
#include <string>

enum EKeyType {
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_END
};

class KOFKeyManager : public Singleton<KOFKeyManager>
{
public:
	HRESULT Init();
	void Update(float TimeDelta);
	void Release();

	string GetPlayerCommand(int p) const {
		string temp = "";

		if (p == 1)
			for (int i = 0; i < player1KeyBuffer.size(); ++i)
				temp += player1KeyBuffer[i].first;
		else
			for (int i = 0; i < player2KeyBuffer.size(); ++i)
				temp += player2KeyBuffer[i].first;
		
		return temp;
	}

	bool HasPlayerMoveKey(int p, EKeyType keyType) const {
		return (p == 1 ? player1MoveKey[keyType] : player2MoveKey[keyType]);
	}

	void ClearPlayer1Buffer() { player1KeyBuffer.clear(); }
	void ClearPlayer2Buffer() { player2KeyBuffer.clear(); }
	
	void Reset() {
		currentTime = 0.f;
		player1KeyBuffer.clear();
		player2KeyBuffer.clear();
	}
private:
	float currentTime = 0.f;
	// 1p, 2p 버퍼
	deque<pair<char, float>> player1KeyBuffer;
	deque<pair<char, float>> player2KeyBuffer;

	// 1p, 2p 움직임 press
	bool player1MoveKey[KEY_END] = { 0, };
	bool player2MoveKey[KEY_END] = { 0, };

};

