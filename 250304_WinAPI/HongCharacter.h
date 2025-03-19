#pragma once
#include "GameObject.h"

class Collider;
class HongCharacter : public GameObject
{
public:
	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update(float TimeDelta);		// ������ ������ ���� ���� ����(������ ���)
	virtual void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	HongCharacter();
	virtual ~HongCharacter();

public:
	FPOINT Pos;
	Collider* collider;
};

