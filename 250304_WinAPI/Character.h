#pragma once
#include "GameObject.h"
#include <vector>
class Image;
class Character : public GameObject
{
private:
	enum class STATE { IDLE, BACK, WALK, DOWN, DOWNBACK, DOWNWALK, DASH, BACKDASH,SKILL, PROCESS };
	struct SKILL
	{
		string command;		//커맨드
		Image* image;		//실행 이미지
		int maxFrame;		//총 프레임
		int damage;			//데미지
		int reach;			//사정거리
		bool isUpperAttack;	//상단피격여부
		bool isLowerAttack;	//하단피격여부

		//현재 x축으로만 이동 가능
		float startTime;	//이동 시작 타이밍
		float moveTime;		//이동
		int way;			//이동방향
		int speed;			//이동속도
	};
	int		player;

	FPOINT	pos;
	bool	screenWay; //화면에서 보고있는 방향
	int		moveWay; //이동방향
	float	characterSpeed;
	float	speed; //속도
	float	hp;
	float	currentHp;
	float	damage;
	vector<Image> images;
	vector<int> maxFrames;
	string	currentCommand; //들어온 커맨드
	
	vector<SKILL> skillSet;//기술 목록
	int		currentSkill; //현재 재생중인 기술

	int		framecnt;
	float	timecnt;

	STATE	currentState; //상태

public:
	Character();
	~Character();
	void Init(int player, FPOINT pos, float characterSpeed,
				float hp, vector<Image>images, vector<int> maxFrames);
	void Release();
	//뒷걷기, 앞걷기, 숙이기, 숙이고뒷걷기,숙이고앞걷기, 앞대쉬, 백대쉬 순으로 넣어주세요
	void pushCommon(Image* image, int maxFrame);
	void pushSkill(string command, Image* image, int maxFrame,
		int damage, int reach, bool isUpperAttack, bool isLowerAttack,
		float startTime, float moveTime, int way, int speed);
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Move(float deltaTime);
	void getCommand();
	void updateCurrentScreenWay(Character* otherCharacter);
	void setPlayer(int p);
	
	void useSkill(string str);
	void endSkill();
	int getIndex();
};


