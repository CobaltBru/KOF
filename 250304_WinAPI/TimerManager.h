#pragma once
#include "config.h"

class TagFinder
{
private:
	const wchar_t* m_pStr;

public:
	TagFinder(const wchar_t* pStr)
		: m_pStr(pStr)
	{

	}

public:
	template<typename T>
	bool	operator()(T& Pair)
	{
		if (!lstrcmp(m_pStr, Pair.first))
			return true;

		return false;
	}
};

class TimerManager
{
public:
	TimerManager();
	virtual ~TimerManager() = default;

public:
	float GetTimeDelta(const wchar_t* pTimerTag);
	void AddTimer(const wchar_t* pTimerTag);
	void UpdateTimer(const wchar_t* pTimerTag);
	void Release();
private:
	using TIMERS = map<const wchar_t*, class Timer*>;
	TIMERS m_Timers;
	
private:
	class Timer* FindTimer(const wchar_t* pTimerTag);

};

