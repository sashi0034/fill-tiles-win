//
// Created by sashi0034 on 2022/07/16.
//

#ifndef FILL_TILES_PLAYERMOVEDATA_H
#define FILL_TILES_PLAYERMOVEDATA_H

#include "../MatPos.h"
#include "../Angle.h"

namespace inGame::player
{
    struct PlayerMoveData
    {
    public:
        const MatPos BeforePos;
        const MatPos AfterPos;
        const Angle MovingAngle;
        const bool IsDash;

        PlayerMoveData(
                const MatPos &beforePos,
                const MatPos &afterPos,
                const Angle &movingAngle,
                const bool isDash);

        bool IsJustInRange(const MatPos pos, int manhattanDistance);
    };
}


#endif //FILL_TILES_PLAYERMOVEDATA_H
