#pragma once
#include "GameObject.h"
#include <vector>

#define FRAMESPEED 10.0f

class Image;
class Character : public GameObject
{
protected:
	enum class STATE { IDLE, BACK, WALK, DOWN, DASH, BACKDASH,SKILL, PROCESS };
	struct SKILL
	{
		string command;		//Ŀ�ǵ�
		Image* image;		//���� �̹���
		int maxFrame;		//�� ������
		int damage;			//������
		int reach;			//�����Ÿ�
		bool isUpperAttack;	//����ǰݿ���
		bool isLowerAttack;	//�ϴ��ǰݿ���

		//���� x�����θ� �̵� ����
		float startTime;	//�̵� ���� Ÿ�̹�
		float endTime;		//�̵� �� Ÿ�̹�
		int way;			//�̵�����
		int speed;			//�̵��ӵ�
	};
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
	
	bool basicKeys[4];

	vector<SKILL> skillSet;//��� ���
	int		currentSkill; //���� ������� ���

	int		framecnt;
	float	timecnt;
	float	dashTimer;
	float	dashTime;
	string	dashKey; // �뽬���� ��뽬���� �Ǵ�

	STATE	currentState; //����
	int		guardState; //0 �밡�� , 1��ܰ���, 2�ϴܰ���
public:
	Character();
	~Character();
	/*void Init(int player,Image* profile, FPOINT pos, float characterSpeed,
				float hp, vector<Image>images);*/

	void Init(int player, Image* profile, FPOINT pos, float characterSpeed,
		float hp, vector<Image>images);

	void Release();
	//idle, �ްȱ�, �հȱ�, ���̱�, �մ뽬, ��뽬 ������ �־��ּ���
	void pushCommon(Image* image, int maxFrame);

	void pushSkill(string command, Image* image, int maxFrame,
		int damage, int reach, bool isUpperAttack, bool isLowerAttack,
		float startTime, float endTime, int way, int speed);
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Move(float deltaTime);
	void getCommand();
	void updateCurrentScreenWay(Character* otherCharacter);
	void setPlayer(int p);
	
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
	int getIndex();

	float* getCurrentHp();
	float getMaxHp();
	Image getProfile();
	//0 �밡�� , 1��ܰ���, 2�ϴܰ���
	int getGuardState();
	STATE getState();
};


