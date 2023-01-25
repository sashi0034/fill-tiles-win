//
// Created by sashi0034 on 2022/06/27.
//

#ifndef FILL_TILES_FIELDEVENTMANAGER_H
#define FILL_TILES_FIELDEVENTMANAGER_H

#include "stdafx.h"
#include "IntCounter.h"

namespace inGame
{
    class FieldEventManager;

    class IFieldEventManagerCountable
    {
    public:
        virtual IntCounter * GetEventCounter() = 0;
        virtual IntCounter * GetTakingScrollCounter() = 0;
    };

    class FieldEventInScope
    {
    public:
        explicit FieldEventInScope(IFieldEventManagerCountable* manager);
        ~FieldEventInScope();
        void StartFromHere();
        void TakeScroll();
        IFieldEventManagerCountable* m_Manager;
        bool m_IsStarted = false;
        IntCounter* m_TakingScroll = nullptr;
    };

    class FieldEventManager final : private IFieldEventManagerCountable
    {
    public:

        /**
         * フィールド上でcoroutine非同期イベントを発生させるときは、イベントスコープの冒頭で以下のように使用します。
         * ```
         * auto eventInScope = instance()->AwaitIfEventExist(yield)->UseEvent();
         * eventInScope.StartFromHere();
         * ```
         */
        [[nodiscard("Hold this object until scope end.")]] FieldEventInScope UseEvent();
        [[nodiscard]] bool IsRunning() const;
        [[nodiscard]] bool IsTakingScroll() const;
        FieldEventManager* AwaitIfEventExist(CoroTaskYield& yield);

    private:
        IntCounter * GetEventCounter() override;
        IntCounter * GetTakingScrollCounter() override;
    private:
        IntCounter m_RunningEventCount{};
        IntCounter m_TakingScrollCount{};
    };
}


#endif //FILL_TILES_FIELDEVENTMANAGER_H
