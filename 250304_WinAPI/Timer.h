#pragma once
#include "config.h"
class Timer
{
public:
	Timer();
	~Timer();

public:
	void Init();
	void Update();
	float GetTimeDelta() { return m_fTimeDelta; }
private:
	LARGE_INTEGER m_CurrentTime;
	LARGE_INTEGER m_OldTime;
	LARGE_INTEGER m_OriginTime;
	LARGE_INTEGER m_CpuTick;
	float m_fTimeDelta;
};

