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
		int imageIdx;		//�̹��� �ε���
		int maxFrame;		//�� ������

		int damage;			//������
		int reach;			//�����Ÿ�
		bool isUpperAttack;	//����ǰݿ���
		bool isLowerAttack;	//�ϴ��ǰݿ���

		//���� x�����θ� �̵� ����
		//float startTime;	//�̵� ���� Ÿ�̹�
		//float endTime;		//�̵� �� Ÿ�̹�
		//int way;			//�̵�����
		//float speed;			//�̵��ӵ�

		string next;
	};
	map<string, SKILL> behaviorMap;

	Character2* other;
	int		player; //1, 2
	Image*	profile;
	FPOINT	pos;
	bool	screenWay; //ȭ�鿡�� �����ִ� ����
	int		moveWay; //�̵�����
	float	characterSpeed;
	float	speed; //�ӵ�
	float	hp;
	float	currentHp;
	float	damage;
	vector<Image> images;
	string	currentCommand; //���� Ŀ�ǵ�
	
	bool oldKeys[4];
	bool basicKeys[4];

	string		currentSkill; //���� ������� ���

	int		framecnt;
	float	timecnt;
	float	dashTimer;
	float	dashTime;
	string	dashKey; // �뽬���� ��뽬���� �Ǵ�

	STATE	currentState; //����
	BEHAVE	currentBehave; //����
	int		guardState; //0 �밡�� , 1��ܰ���, 2�ϴܰ���
public:
	Character2();
	~Character2();
	/*void Init(int player,Image* profile, FPOINT pos, float characterSpeed,
				float hp, vector<Image>images);*/

	void Init(int player, Image* profile, FPOINT pos, float characterSpeed,
		float hp);

	void Release();
	//IDLE, BACK, WALK, DOWN, DASH, BACKDASH ������ �־��ּ���
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
	//0 �밡�� , 1��ܰ���, 2�ϴܰ���
	int getGuardState();
	//BEHAVE getBehave();
	BEHAVE getBehave();
	void attack();
	void getDamage(float damage);
	void SetEnemy(Character2* other);
	FPOINT getPos();
};


