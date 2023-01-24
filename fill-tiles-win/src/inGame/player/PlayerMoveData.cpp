//
// Created by sashi0034 on 2022/07/16.
//

#include "PlayerMoveData.h"

namespace inGame::player
{
    PlayerMoveData::PlayerMoveData(const MatPos &beforePos, const MatPos &afterPos, const Angle &movingAngle,
                                   const bool isDash) : BeforePos(beforePos), AfterPos(afterPos),
                                                        MovingAngle(movingAngle), IsDash(isDash)
    {}

    bool PlayerMoveData::IsJustInRange(const MatPos pos, int manhattanDistance)
    {
        return pos.CalcManhattan(this->AfterPos) <= manhattanDistance &&
                pos.CalcManhattan(this->BeforePos) > manhattanDistance;
    }
}
