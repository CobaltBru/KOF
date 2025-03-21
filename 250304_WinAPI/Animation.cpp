#include "Animation.h"
#include "Image.h"
#include "math.h"

Animation::Animation()
{
	/*timer = 0;
	currentFrame = 0;
	currentTask = "IDLE";*/
}

Animation::~Animation()
{
	for (auto task : tasks)
	{
		if (task.second.image != nullptr)
		{
			task.second.image->Release();
			delete task.second.image;
		}
	}
}

void Animation::Update(float deltaTime)
{
	
	//TASK& task = tasks[currentTask];
	//timer += deltaTime;
	//if (timer >= task.frameSpeed)
	//{
	//	currentFrame += timer / task.frameSpeed;
	//	timer = fmodf(timer, task.frameSpeed);
	//}
	//if (currentFrame >= task.maxFrame)
	//{
	//	if (task.playflag == PLAYFLAG::NORMAL) //IDLE로 복귀
	//	{
	//		Play("IDLE");
	//	}
	//	else if (task.playflag == PLAYFLAG::LOOP) //현재 애니메이션 다시재생
	//	{
	//		Play(currentTask);
	//	}
	//	else if (task.playflag == PLAYFLAG::STOP) //마지막 프레임 고정
	//	{
	//		currentFrame = task.maxFrame - 1;
	//	}
	//	else if (task.playflag == PLAYFLAG::NEXT)
	//	{
	//		Play(task.next);
	//	}
	//}
	//
	
	
}

void Animation::Render(HDC hdc, FPOINT pos, bool screenWay)
{
	for (auto task : tasks)
	{
		if (task.second.valid == true)
		{
			task.second.image->Render(hdc, pos.x, pos.y, task.second.currentFrame, screenWay);
		}
	}
	
}

void Animation::PushTask(string name, Image* image, FPOINT offset, float frameSpeed,
						int flag1, int flag2)
{
	tasks[name] = {false, image,offset, 0,0,image->GetMaxFrame(), frameSpeed,
					(PLAYFLAG)flag1, (INTERRUPTFLAG)flag2, "IDLE" };
}

void Animation::PushTask(string name, Image* image, FPOINT offset, float frameSpeed,
						int flag1, int flag2, string next)
{
	tasks[name] = {false, image,offset,0,0,  image->GetMaxFrame(),frameSpeed,
					(PLAYFLAG)flag1, (INTERRUPTFLAG)flag2,next };
}

void Animation::Play(string name)
{
	for (auto task : tasks)
	{
		if ((task.second.interruptFlag != INTERRUPTFLAG::LOCK) ||
			task.second.currentFrame >= task.second.maxFrame)
		{
			task.second.valid = true;
			task.second.timer = 0;
			task.second.currentFrame = 0;
		}
	}
	
}

int Animation::mod(int from, int to , int current)
{
	if (current < from) return from;
	else if (current > to) return to;
	else return current;
}
