#pragma once
#include "config.h"
#include <deque>
#include <string>

class KOFKeyManager : public Singleton<KOFKeyManager>
{
public:
	HRESULT Init();
	void Update(float TimeDelta);
	void Release();

	string GetPlayer1Command() const {
		string temp = "";

		for (int i = 0; i < player1KeyBuffer.size(); ++i)
			temp += player1KeyBuffer[i].first;

		return temp;
	}
	string GetPlayer2Command() const {
		string temp = "";

		for (int i = 0; i < player2KeyBuffer.size(); ++i)
			temp += player2KeyBuffer[i].first;

		return temp;
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
	// 1p, 2p ¹öÆÛ
	deque<pair<char, float>> player1KeyBuffer;
	deque<pair<char, float>> player2KeyBuffer;
	
};

