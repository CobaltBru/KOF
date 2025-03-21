#pragma once
#include "GameObject.h"
#include <map>
class Animation;
class Image;
class Character2:public GameObject
{
protected:
	enum STATE { IDLE, BACK, WALK, DOWN, DASH, BACKDASH,
		BLOCKUPPER, BLOCKLOWER, SKILL};
	enum INTERRUPTFLAG { OPEN, LOCK };
	enum BLOCK {NONE, UPPER, LOWER};
	enum PLAYFLAG { NORMAL, LOOP, NEXT };

	struct BEHAVE
	{
		STATE state;
		INTERRUPTFLAG interruptFlag;
		PLAYFLAG playFlag;

		int maxFrame;
		float frameSpeed;

		float damage;
		float reach;
		bool isUpperAttack;
		bool isLowerAttack;
		int attacFrame;

		string next;
	};
	map<string, BEHAVE> behaves;
	Animation* animation;
	Image* profile;

	int player;
	bool screenWay;

	float moveDir;
	float characterSpeed;
	float currentSpeed;

	float maxHp;
	float currentHp;

	bool currentKeys[4];
	bool oldKeys[4];
	string currentCommand;

	STATE oldState;
	STATE currentState;
	INTERRUPTFLAG flag;
	BLOCK blockState;

	float timer;
	int currentFrame;

	float doubleClickTimerA;
	bool clickedKeyA;
	float doubleClickTimerD;
	bool clickedKeyD;

public:
	Character2();
	~Character2();

	void Init(int player,Image* profile, FPOINT pos,float characterSpeed, int maxHp);
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Move(float deltaTime);
	void StateProcess();

	bool isJustPressed(int key);
	bool isJustReleased(int key);
	bool isKeepPressed(int key);
	bool isKeepReleased(int key);
	bool doubleClickCheck(int key);
	
	/*
	* flag1-> 0.NORMAEL / 1.LOOP / 2.STAY LAST FRAME / 3.PLAY NEXT
	* flag2-> 0.OPEN /1.LOCK
	*/
	void PushAnimation(string name,Image* image, float frameSpeed,
		int flag1, int flag2);
	/*
	* flag1-> 0.NORMAEL / 1.LOOP / 2.STAY LAST FRAME / 3.PLAY NEXT
	* flag2-> 0.OPEN /1.LOCK
	*/
	void PushAnimation(string name,Image* image, float frameSpeed,
		int flag1, int flag2, string next);

	inline float* getCurrentHp() { return &currentHp; }
	Image getProfile();
};

