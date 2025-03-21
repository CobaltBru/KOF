#pragma once
#include "GameObject.h"
#include <vector>

#define FRAMESPEED 0.05f

class Image;
class Character : public GameObject
{
protected:																		// BLOCKUPPER, BLOCKLOWER, HITUPPER, HITLOWER,DEAD  << 임의로 테스트하려고 김태경이 넣었어요 없애도 됩니당.
	enum class STATE { IDLE, BACK, WALK, DOWN, DASH, BACKDASH, BLOCKUPPER, BLOCKLOWER, HITUPPER, HITLOWER,DEAD, SKILL, PROCESS };			
	struct SKILL
	{
		string command;		//커맨드
		Image* image;		//실행 이미지
		int maxFrame;		//총 프레임
		int damage;			//데미지
		int reach;			//사정거리
		bool isUpperAttack;	//상단피격여부
		bool isLowerAttack;	//하단피격여부
		int attackFrame;
		
	};
	//Character* other;
	int		player; //1, 2
	Image*	profile;
	//FPOINT	pos;
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

	vector<SKILL> skillSet;//기술 목록
	int		currentSkill; //현재 재생중인 기술

	int		framecnt;
	float	timecnt;
	float	dashTimer;
	float	dashTime;
	string	dashKey; // 대쉬인지 백대쉬인지 판단

	STATE	currentState; //상태
	int		guardState; //0 노가드 , 1상단가드, 2하단가드
public:
	Character();
	~Character();
	/*void Init(int player,Image* profile, FPOINT pos, float characterSpeed,
				float hp, vector<Image>images);*/

	void Init(int player, Image* profile, FPOINT pos, float characterSpeed,
		float hp, vector<Image>images);

	void Release();
	//idle, 뒷걷기, 앞걷기, 숙이기, 앞대쉬, 백대쉬,윗방어,아랫방어 순으로 넣어주세요
	void pushCommon(Image* image, int maxFrame);

	void pushSkill(string command, Image* image, int maxFrame,
		float damage, float reach, bool isUpperAttack, bool isLowerAttack, int attackFrame);
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Move(float deltaTime);
	void getCommand();
	void updateCurrentScreenWay(Character* otherCharacter);
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
	void setBlock();

	void useSkill(string str);
	void endSkill();
	int getIndex();

	//FPOINT getPos();
	float* getCurrentHp();
	float getMaxHp();
	Image getProfile();
	//0 노가드 , 1상단가드, 2하단가드
	int getGuardState();
	STATE getState();

	void attack(Character* other);
	void getDamage(float damage);
	//void SetEnemy(Character* other);



	//  임의로 테스트하려고 김태경이 넣었어요
	void SetCurrentState(STATE InCurrentState) { 
		currentState = InCurrentState; 
		framecnt = 0;
		timecnt = 0;
		speed = 0.f;
		bBlockHit = true;
	}
	bool bBlockHit = false;
};


