#include "TimerManager.h"
#include "Timer.h"
TimerManager::TimerManager()
{
}
float TimerManager::GetTimeDelta(const wchar_t* pTimerTag)
{
	Timer* pTimer = FindTimer(pTimerTag);
	if (nullptr == pTimer)
		return 0.0f;

	return pTimer->GetTimeDelta();
}

void TimerManager::AddTimer(const wchar_t* pTimerTag)
{
	if (nullptr != FindTimer(pTimerTag))
		return;

	Timer* pTimer = new Timer;
	if (nullptr == pTimer)
		return;

	pTimer->Init();

	m_Timers.emplace(pTimerTag, pTimer);
}

void TimerManager::UpdateTimer(const wchar_t* pTimerTag)
{
	Timer* pTimer = FindTimer(pTimerTag);
	if (nullptr == pTimer)
		return;

	pTimer->Update();
}

void TimerManager::Release()
{
	for (auto& Pair : m_Timers)
		delete Pair.second;

	m_Timers.clear();
}

Timer* TimerManager::FindTimer(const wchar_t* pTimerTag)
{
	auto	iter = find_if(m_Timers.begin(), m_Timers.end(), TagFinder(pTimerTag));

	if (iter == m_Timers.end())
		return nullptr;

	return iter->second;
}
