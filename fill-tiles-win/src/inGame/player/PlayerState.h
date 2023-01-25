//
// Created by sashi0034 on 2022/06/07.
//

#ifndef FILL_TILES_PLAYERSTATE_H
#define FILL_TILES_PLAYERSTATE_H


#include "../../gameEngine/gameEngine.h"

namespace inGame::player
{
    enum class EPlayerState
    {
        Waiting,
        Walking,
        Dead,
        Warping,
    };

    class PlayerState
    {
    public:
        explicit PlayerState(EPlayerState initialState);
        [[nodiscard]] EPlayerState GetState() const;
        bool UpdateAction();
        void ChangeState(EPlayerState newState, CoroTaskCall* newAction);
    private:
        EPlayerState m_State = EPlayerState::Waiting;
        unique_ptr<CoroTaskCall> m_Action{};
    };
}


#endif //FILL_TILES_PLAYERSTATE_H
