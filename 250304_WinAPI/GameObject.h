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

	void SetPos(FPOINT newPos) { pos = newPos; }
	GameObject();
	virtual ~GameObject();

	inline void SetActive(bool bActive)
	{
		this->bActive = bActive;
	}
	inline bool IsActive() 
	{ 
		return bActive; 
	}

protected:
	FPOINT pos;
	bool bActive = true;
};

