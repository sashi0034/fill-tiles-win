//
// Created by sashi0034 on 2022/08/10.
//

#ifndef FILL_TILES_STEPPEDONMINEEVENT_H
#define FILL_TILES_STEPPEDONMINEEVENT_H

#include "MineFlowerClass.h"

namespace myGame
{
    struct SteppedOnMineEventArgs
    {
        MainScene* const MainScene;
        MineFlowerClass* const ClassAtFailed;
        MatPos const SteppedPos;

        FieldManager* GetFieldManager() const;
    };

    class SteppedOnMineEvent
    {
    public:
        void StartEvent(const SteppedOnMineEventArgs& args);
    private:
        void performExplosionAsync(CoroTaskYield& yield, SteppedOnMineEventArgs args);
        void explodeFlowersAsync(CoroTaskYield &yield, SteppedOnMineEventArgs args);
    };

} // myGame

#endif //FILL_TILES_STEPPEDONMINEEVENT_H
