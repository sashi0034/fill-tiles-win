//
// Created by sashi0034 on 2022/05/24.
//

#include "CoroutineManager.h"

using namespace boost::coroutines2;
namespace myUtil{

    CoroutineElement::CoroutineElement(boost::coroutines2::coroutine<CoroTask>::pull_type * task) : m_Task(task)
    {}

    boost::coroutines2::coroutine<CoroTask>::pull_type& CoroutineElement::GetTask() const
    {
        return *m_Task;
    }


    WeakPtr<CoroutineElement> CoroutineManager::Start(std::function<void(CoroTaskYield&)> task)
    {
        return Start(new CoroTaskCall(task));
    }

    WeakPtr<CoroutineElement> CoroutineManager::Start(boost::coroutines2::coroutine<CoroTask>::pull_type *task)
    {
        return m_Pool.Birth(new CoroutineElement(task))->GetWeakPtr();
    }

    WeakPtr<CoroutineElement> CoroutineManager::Start(CoroutineElement *task)
    {
        return m_Pool.Birth(task)->GetWeakPtr();
    }

    bool CoroutineManager::Destroy(CoroutineElement *task)
    {
        return m_Pool.Destroy(task);
    }

    void CoroutineManager::UpdateEach()
    {
        m_Pool.ProcessEach([&](CoroutineElement& element){{
            auto& task = element.GetTask();
            (task)();
            if (task)
                {}
            else
                Destroy(&element);
        }});
    }

    CoroutineManager::~CoroutineManager()
    {
        m_Pool.Release();
    }
}
