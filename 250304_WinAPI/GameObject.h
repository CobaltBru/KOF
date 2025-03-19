#pragma once
#include "config.h"

class GameObject
{
public:
	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update(float TimeDelta);		// ������ ������ ���� ���� ����(������ ���)
	virtual void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	inline const FPOINT& GetPos() { return pos; }
	GameObject();
	virtual ~GameObject();
protected:

	FPOINT pos;
};

