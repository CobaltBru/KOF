#pragma once
#include "config.h"
#include <map>

class Image;
class Animation
{
private:
	//일반 재생, 루프, 마지막 프레임 유지, 다음동작
	enum PLAYFLAG{NORMAL, LOOP, STOP, NEXT};
	//끊겨도 되는지 안되는지
	enum INTERRUPTFLAG{OPEN, LOCK};

	struct TASK
	{
		Image* image;
		int maxFrame;

		float frameSpeed;
		PLAYFLAG playflag;
		INTERRUPTFLAG interruptFlag;
		string next;
	};
	map<string, TASK> tasks;
	float timer = 0;
	int currentFrame = 0;
	string currentTask;
public:
	Animation();
	~Animation();
	void Update(float deltaTime);
	void Render(HDC hdc, FPOINT pos, bool screenWay);
	void PushTask(string name, Image* image, float frameSpeed,
		int flag1, int flag2);
	void PushTask(string name, Image* image, float frameSpeed, 
		int flag1, int flag2, string next);
	void Play(string name);
	int mod(int from, int to, int current);

};

