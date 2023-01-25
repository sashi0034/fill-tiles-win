//
// Created by sashi0034 on 2022/06/27.
//

#include "../gameEngine/gameEngine.h"
#include "FieldEventManager.h"

namespace inGame{
    bool FieldEventManager::IsRunning() const
    {
        return m_RunningEventCount.GetCount()>0;
    }

    bool FieldEventManager::IsTakingScroll() const
    {
        return m_TakingScrollCount.GetCount() > 0;
    }

    FieldEventInScope FieldEventManager::UseEvent()
    {
        return FieldEventInScope(this);
    }

    FieldEventManager* FieldEventManager::AwaitIfEventExist(CoroTaskYield& yield)
    {
        while (IsRunning())
        {
            yield();
        }

        return this;
    }

    IntCounter* FieldEventManager::GetEventCounter()
    {
        return &m_RunningEventCount;
    }

    IntCounter* FieldEventManager::GetTakingScrollCounter()
    {
        return &m_TakingScrollCount;
    }

    FieldEventInScope::FieldEventInScope(IFieldEventManagerCountable *manager)
    : m_Manager(manager)
    {}

    void FieldEventInScope::StartFromHere()
    {
        LOG_ASSERT(!m_IsStarted, "Event has already started.");
        m_IsStarted = true;
        m_Manager->GetEventCounter()->IncreaseCount();
    }

    FieldEventInScope::~FieldEventInScope()
    {
        LOG_ASSERT(m_IsStarted, "Event destroyed without starting.");
        m_Manager->GetEventCounter()->DecreaseCount();
        if (m_TakingScroll != nullptr) m_TakingScroll->DecreaseCount();
    }

    void FieldEventInScope::TakeScroll()
    {
        m_TakingScroll = m_Manager->GetTakingScrollCounter();
        m_TakingScroll->IncreaseCount();
    }
}
