#include "KOFKeyManager.h"
#include "KeyManager.h"

HRESULT KOFKeyManager::Init()
{
	currentUpdateTime1 = GetTickCount64();
	currentUpdateTime2 = GetTickCount64();

	return S_OK;
}

// 1p (������):WASD (����):tygh //	2p (������):arrow , (����): 5623
void KOFKeyManager::Update()
{
	// ���⼭ Ű ��ǲ�� ������Ʈ�Ѵ�.   
	// GetTickCount�� ���͹� ����ϸ� �Ǳ� �ҵ�?    // Ű �ٿ�� ������ �ذ��ϸ� �ɵ�..
	// Ű�� ������ �� ���� ����.  �׷� Ŀ�ǵ尡 ��� �˾ƾ� ��. ���� Ŀ�ǵ忡 ���͹��� �ʿ��� ��
	// ���͹��� ���� �ֵ鸸 ���� ���� Ŀ�ǵ带 ����� ��. �׷� ���� Ű�� ��� �޾ƾ� �� �� �� �ִ�. �׷� ���� W W�� ������ �� ��� �Ǵ��� ���ΰ�?
	// Ű �Ŵ������� W�� up�� �� �� �ٽ� �����ٸ� �˾ƾ� �ϴµ� �׷� ���͹� ���̿� ��� �־�� �ڴ�.
	// �迭�� ���� �ش� �迭 Ű �� �Ұ��� ���� �ϰ� �װ� ������ �� ���� ����

	// �ϴ� �⺻ �̵����� ������.

	Player1Update();
	Player2Update();
}

void KOFKeyManager::Player1Update()
{
	currentUpdateTime1 = playerInput1.empty() ? 0 : playerInput1.front().second;

	if (KeyManager::GetInstance()->IsOnceKeyDown('W'))
	{
		playerInput1.push(pair<int, int>{'W', GetTickCount64()});
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown('A'))
	{
		playerInput1.push(pair<int, int>{'A', GetTickCount64()});
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown('S'))
	{
		playerInput1.push(pair<int, int>{'S', GetTickCount64()});
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown('D'))
	{
		playerInput1.push(pair<int, int>{'D', GetTickCount64()});
	}

	if (currentUpdateTime1 + KEYINTERVAL < GetTickCount64()) // ���⼭ Ŀ�ǵ� ����
		Player1CommandUpdate();
}

void KOFKeyManager::Player2Update()
{
	currentUpdateTime2 = playerInput2.empty() ? 0 : playerInput2.front().second;

	if (currentUpdateTime2 + KEYINTERVAL < GetTickCount64())
		Player2CommandUpdate();
}

void KOFKeyManager::Player1CommandUpdate()
{
}

void KOFKeyManager::Player2CommandUpdate()
{
}

void KOFKeyManager::Release()
{
	ReleaseInstance();
}
