#include "KOFKeyManager.h"
#include "KeyManager.h"

HRESULT KOFKeyManager::Init()
{
	currentUpdateTime1 = GetTickCount64();
	currentUpdateTime2 = GetTickCount64();

	return S_OK;
}

// 1p (움직임):WASD (공격):tygh //	2p (움직임):arrow , (공격): 5623
void KOFKeyManager::Update()
{
	// 여기서 키 인풋을 업데이트한다.   
	// GetTickCount로 인터벌 계산하면 되긴 할듯?    // 키 다운과 업으로 해결하면 될듯..
	// 키가 씹혀야 할 때도 있음.  그럼 커맨드가 몇갠지 알아야 함. 또한 커맨드에 인터벌도 필요할 듯
	// 인터벌에 들어온 애들만 따로 뺴서 커맨드를 만들면 됨. 그럼 같은 키를 계속 받아야 할 수 도 있다. 그럼 만약 W W를 누르는 걸 어떻게 판단할 것인가?
	// 키 매니저에서 W가 up을 한 후 다시 누른다를 알아야 하는데 그럼 인터벌 사이에 계속 넣어야 겠다.
	// 배열을 만들어서 해당 배열 키 의 불값을 인지 하고 그게 때지면 쌉 가능 ㅇㅇ

	// 일단 기본 이동부터 만들자.

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

	if (currentUpdateTime1 + KEYINTERVAL < GetTickCount64()) // 여기서 커맨드 조합
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
