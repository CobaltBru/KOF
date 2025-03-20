#pragma once
#include "GameObject.h"

class Image;
class Hadogen : public GameObject
{
public:
	Hadogen();
	~Hadogen();

	void Init(FPOINT pos,FPOINT pivot, int damage, int type);		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update(float TimeDelta);		// ������ ������ ���� ���� ����(������ ���)
	virtual void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	void CheckMaxFrame();
	void CollisionUpdate();

private:
	bool bDead;
	bool bRender;
	float timeCnt;
	float frameCnt;
	FPOINT collisionPivot;
	int damage;
	int hadogenMaxFrame;
	Image* HadogenImage;
	Image* DestroyImage;
};

