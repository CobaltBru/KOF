#pragma once
#include "config.h"

class GameObject
{
public:
	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update(float TimeDelta);		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	GameObject();
	~GameObject();
};

