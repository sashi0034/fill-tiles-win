//
// Created by sashi0034 on 2022/06/07.
//

#include "PlayerState.h"

namespace inGame::player
{
    PlayerState::PlayerState(EPlayerState initialState)
    : m_State(initialState)
    {}

    EPlayerState PlayerState::GetState() const
    {
        return m_State;
    }

    bool PlayerState::UpdateAction()
    {
        if (m_Action == nullptr) return false;

        if (*m_Action)
            (*m_Action)();
        else
            return false;

        return true;
    }

    void PlayerState::ChangeState(EPlayerState newState, CoroTaskCall *newAction)
    {
        m_State = newState;
        m_Action.reset(newAction);
    }
}