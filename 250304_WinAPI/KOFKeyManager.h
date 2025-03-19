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

private:
	float currentTime = 0.f;
	// 1p, 2p ¹öÆÛ
	deque<pair<char, float>> player1KeyBuffer;
	deque<pair<char, float>> player2KeyBuffer;
	// 1p , 2p 
	string player1Command;
	string player2Command;
	
};

