#pragma once
#include "GameObject.h"

class Image;

class UserInterface
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);


	
	UserInterface();
	~UserInterface();
private:
	FPOINT p1Pos;
	int p1Health;
	Image* p1Image;
	
	FPOINT p2Pos;
	int p2Health;
	Image* p2Image;
	
};
