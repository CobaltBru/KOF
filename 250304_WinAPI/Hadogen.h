#pragma once
#include "GameObject.h"

class Image;
class Hadogen : public GameObject
{
public:
	Hadogen();
	~Hadogen();

	void Init(FPOINT pos,FPOINT pivot, int damage, int type,bool bUpperAttack);		// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update(float TimeDelta);		// 프레임 단위로 게임 로직 실행(데이터 계산)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력(이미지, 텍스트 등)

	void CheckMaxFrame();
	void CollisionUpdate();

private:
	bool bDead;
	bool bRender;
	bool bUpperAttack;
	float timeCnt;
	float frameCnt;
	FPOINT collisionPivot;
	int damage;
	int hadogenMaxFrame;
	Image* HadogenImage;
	Image* DestroyImage;
};

