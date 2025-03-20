#pragma once
#include "Character.h"
#include <vector>

class Collider;
class Ryo : public Character
{
private:
	struct OTHERSKILLINFO
	{
		int skipFrame;
		FPOINT collisionPivot;
	};

public:
	Ryo();
	~Ryo() = default;

	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
	void InitCollider();

	int GetIndex() const {
		return ((currentState == STATE::SKILL || currentState == STATE::PROCESS) ? -1 : static_cast<int>(currentState));
	};

	void StateUpdate(float deltaTime);
	void Move(float deltaTime);
	void useSkill(string str);
	void pushSkill(string command, Image* image, int maxFrame,
		int damage, int reach, bool isUpperAttack, bool isLowerAttack, int attackFrame, int skipFrame = 0, FPOINT collisionPivot = { 0.f,0.f });
	void CollisionUpdate();
	void SkipSkillFrame();
	void CheckMaxFrame();
private:
	bool bCheckPreBackDash;
	bool bBackDash;
	bool bSkip;
	bool bDead;
	bool bFirstAttack;
	float currentTime;
	float KeyBufferTime;
	float aDashTime;
	float bDashTime;
	const int gravity;
	int dy;
	vector<OTHERSKILLINFO> otherSkillInfo;
	Collider* collider;
};


//�ڵ��� 
//if (skill.isLowerAttack) //�ϴ� �����϶�
//{
//	if (other->getGuardState() == 2) //�ϴ� ����϶�
//	{
//		d *= 0.1f;
//		other->SetCurrentState(STATE::BLOCKLOWER);
//	}
//	else
//		other->SetCurrentState(STATE::HITLOWER);
//}
//else if (skill.isUpperAttack) //��� �����϶�
//{
//	if (other->getState() == STATE::DOWN) //��밡 ��������
//	{
//		d = 0;
//	}
//	else if (other->getGuardState() == 1) //��� ����϶�%
//	{
//		d *= 0.1f;
//		other->SetCurrentState(STATE::BLOCKUPPER);
//	}
//	else
//		other->SetCurrentState(STATE::HITUPPER);
//}
//other->getDamage(d);