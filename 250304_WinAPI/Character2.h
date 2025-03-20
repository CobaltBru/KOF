#pragma once
#include "GameObject.h"
#include <vector>
#include <MAP>

#define FRAMESPEED 0.05f

class Image;
class Character2 : public GameObject
{
protected:
	enum class STATE { OPEN, LOCK };
	enum class BEHAVE { IDLE, BACK, WALK, DOWN, DASH, BACKDASH,SKILL, PROCESS };
	
	struct SKILL
	{
		int imageIdx;		//이미지 인덱스
		int maxFrame;		//총 프레임

		int damage;			//데미지
		int reach;			//사정거리
		bool isUpperAttack;	//상단피격여부
		bool isLowerAttack;	//하단피격여부

		//현재 x축으로만 이동 가능
		//float startTime;	//이동 시작 타이밍
		//float endTime;		//이동 끝 타이밍
		//int way;			//이동방향
		//float speed;			//이동속도

		string next;
	};
	map<string, SKILL> behaviorMap;

	Character2* other;
	int		player; //1, 2
	Image*	profile;
	FPOINT	pos;
	bool	screenWay; //화면에서 보고있는 방향
	int		moveWay; //이동방향
	float	characterSpeed;
	float	speed; //속도
	float	hp;
	float	currentHp;
	float	damage;
	vector<Image> images;
	string	currentCommand; //들어온 커맨드
	
	bool oldKeys[4];
	bool basicKeys[4];

	string		currentSkill; //현재 재생중인 기술

	int		framecnt;
	float	timecnt;
	float	dashTimer;
	float	dashTime;
	string	dashKey; // 대쉬인지 백대쉬인지 판단

	STATE	currentState; //상태
	BEHAVE	currentBehave; //상태
	int		guardState; //0 노가드 , 1상단가드, 2하단가드
public:
	Character2();
	~Character2();
	/*void Init(int player,Image* profile, FPOINT pos, float characterSpeed,
				float hp, vector<Image>images);*/

	void Init(int player, Image* profile, FPOINT pos, float characterSpeed,
		float hp);

	void Release();
	//IDLE, BACK, WALK, DOWN, DASH, BACKDASH 순으로 넣어주세요
	void pushCommon(string str, Image* image, string nextBehave);

	void pushSkill(string command, Image* image, int maxFrame,
		int damage, int reach, bool isUpperAttack, bool isLowerAttack);
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Move(float deltaTime);
	void updateCurrentScreenWay(Character2* otherCharacter);
	void setPlayer(int p);

	bool isJustPressed(int key);
	bool isJustReleased(int key);
	bool isKeepPressed(int key);
	bool isKeepReleased(int key);

	void setIdle();
	void setWalk();
	void setBack();
	void startDashTimer();
	void checkDash(string key);
	void setDash();
	void checkBackDash(string key);
	void setBackDash();
	void setDown();

	void useSkill(string str);
	void endSkill();
	int getCurrentIndex();
	int getIndex(BEHAVE behave);
	float* getCurrentHp();
	float getMaxHp();
	Image getProfile();
	//0 노가드 , 1상단가드, 2하단가드
	int getGuardState();
	//BEHAVE getBehave();
	BEHAVE getBehave();
	void attack();
	void getDamage(float damage);
	void SetEnemy(Character2* other);
	FPOINT getPos();
};


