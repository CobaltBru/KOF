// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <map>
#include <list>
#include "KeyManager.h"

using namespace std;

/*
	�����Ϸ����� �ش� �ڵ带 �ڿ� ���ǵ� �ڵ�� �����Ѵ�. 
*/
#define WINSIZE_X	1080
#define WINSIZE_Y	500
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)
#define MAX_KEY_COUNT	256

enum class EKeyType : uint8_t			// Ű ����
{
	KEYUP,
	KEYDOWN,
	KEYLEFT,
	KEYRIGHT,
	KEYUPDOWN,
	KEYUPLEFT,
	KEYUPRIGHT,
	KEYDOWNLEFT,
	KEYDOWNRIGHT,
	END
};

enum OBJID 
{
	OBJ_CHARACTER,
	OBJ_PROJECTILE,
	OBJ_END
};

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

/*
	extern Ű���� : ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִ� ���
	����� �˸��� Ű����.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
