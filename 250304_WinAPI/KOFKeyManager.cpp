#include "KOFKeyManager.h"

HRESULT KOFKeyManager::Init()
{
	currentTime = 0;
	return S_OK;
}

void KOFKeyManager::Update(float TimeDelta)
{
	currentTime += TimeDelta;

	if (KeyManager::GetInstance()->IsOnceKeyDown('W'))
		player1KeyBuffer.push_back({ 'W',currentTime });		
	if (KeyManager::GetInstance()->IsOnceKeyDown('A'))
		player1KeyBuffer.push_back({ 'A',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('S'))
		player1KeyBuffer.push_back({ 'S',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('D'))
		player1KeyBuffer.push_back({ 'D',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('T'))
		player1KeyBuffer.push_back({ 'T',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('Y'))
		player1KeyBuffer.push_back({ 'Y',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('G'))
		player1KeyBuffer.push_back({ 'G',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown('H'))
		player1KeyBuffer.push_back({ 'H',currentTime });

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_UP))
		player2KeyBuffer.push_back({ 'W',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LEFT))
		player2KeyBuffer.push_back({ 'A',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_DOWN))
		player2KeyBuffer.push_back({ 'S',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RIGHT))
		player2KeyBuffer.push_back({ 'D',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD5))
		player2KeyBuffer.push_back({ 'T',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD6))
		player2KeyBuffer.push_back({ 'Y',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD2))
		player2KeyBuffer.push_back({ 'G',currentTime });
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD3))
		player2KeyBuffer.push_back({ 'H',currentTime });

	player1MoveKey[KEY_W] = KeyManager::GetInstance()->IsStayKeyDown('W');
	player1MoveKey[KEY_A] = KeyManager::GetInstance()->IsStayKeyDown('A');
	player1MoveKey[KEY_S] = KeyManager::GetInstance()->IsStayKeyDown('S');
	player1MoveKey[KEY_D] = KeyManager::GetInstance()->IsStayKeyDown('D');

	player2MoveKey[KEY_W] = KeyManager::GetInstance()->IsStayKeyDown(VK_UP);
	player2MoveKey[KEY_A] = KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT);
	player2MoveKey[KEY_S] = KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN);
	player2MoveKey[KEY_D] = KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT);

	while (!player1KeyBuffer.empty() && currentTime - player1KeyBuffer.front().second > 1.f)
		player1KeyBuffer.pop_front();

	while (!player2KeyBuffer.empty() && currentTime - player2KeyBuffer.front().second > 1.f)
		player2KeyBuffer.pop_front();
}

void KOFKeyManager::Release()
{
	ReleaseInstance();
}
