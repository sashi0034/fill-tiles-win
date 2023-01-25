//
// Created by sashi0034 on 2022/05/24.
//

#ifndef FILL_TILES_COROUTINEMANAGER_H
#define FILL_TILES_COROUTINEMANAGER_H

#include <stdafx.h>
#include "WeakPtr.h"
#include "ChildrenPool.h"
#include "CoroTask.h"

namespace gameEngine
{
    class CoroutineElement
    {
        DEF_WEAK_CONTROLLER(CoroutineElement);
    public:
        explicit CoroutineElement(boost::coroutines2::coroutine<CoroTask>::pull_type *mTask);
        [[nodiscard]] boost::coroutines2::coroutine<CoroTask>::pull_type& GetTask() const;
    private:
        std::unique_ptr<boost::coroutines2::coroutine<CoroTask>::pull_type> m_Task;
    };

    class ICoroutineManager
    {
    public:
        virtual WeakPtr<CoroutineElement> Start(std::function<void(CoroTaskYield&)> Task) = 0;
        virtual WeakPtr<CoroutineElement> Start(boost::coroutines2::coroutine<CoroTask>::pull_type *Task) = 0;
        virtual WeakPtr<CoroutineElement> Start(CoroutineElement *task) = 0;
        virtual bool Destroy(CoroutineElement *task) = 0;
    };

    class CoroutineManager : public ICoroutineManager
    {
    public:
        WeakPtr<CoroutineElement> Start(std::function<void(CoroTaskYield&)> task) override;
        WeakPtr<CoroutineElement> Start(boost::coroutines2::coroutine<CoroTask>::pull_type *task) override;
        WeakPtr<CoroutineElement> Start(CoroutineElement *task) override;
        bool Destroy(CoroutineElement *task) override;
        void UpdateEach();
        ~CoroutineManager();
    private:
        ChildrenPool<CoroutineElement> m_Pool;
    };
}


#endif //FILL_TILES_COROUTINEMANAGER_H
