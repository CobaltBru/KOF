#pragma once
#include "GameObject.h"
#include <vector>
class Image;
class Character : public GameObject
{
private:
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
	int		player;

	FPOINT	pos;
	bool	screenWay; //ȭ�鿡�� �����ִ� ����
	int		moveWay; //�̵�����
	float	characterSpeed;
	float	speed; //�ӵ�
	float	hp;
	float	currentHp;
	float	damage;
	vector<Image> images;
	vector<int> maxFrames;
	string	currentCommand; //���� Ŀ�ǵ�
	
	vector<SKILL> skillSet;//��� ���
	int		currentSkill; //���� ������� ���

	int		framecnt;
	float	timecnt;

	STATE	currentState; //����

public:
	Character();
	~Character();
	void Init(int player, FPOINT pos, float characterSpeed,
				float hp, vector<Image>images, vector<int> maxFrames);
	void Release();
	//�ްȱ�, �հȱ�, ���̱�, �մ뽬, ��뽬 ������ �־��ּ���
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
	
	void useSkill(string str);
	void endSkill();
	int getIndex();
};


