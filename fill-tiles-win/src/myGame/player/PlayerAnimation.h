//
// Created by sashi0034 on 2022/08/11.
//

#ifndef FILL_TILES_PLAYERANIMATION_H
#define FILL_TILES_PLAYERANIMATION_H

#include "../../myUtil/myUtil.h"

#include "../Angle.h"
#include "../MatPos.h"

namespace myGame{
    class MainScene;
    class CharacterViewModel;
}

namespace myGame::player
{
    class PlayerAnimation
    {
    public:
        PlayerAnimation(MainScene *mainScene, const Vec2<int> &cellSize, TextureAnimator &animator,
                        CharacterViewModel *const view);

        void AnimWalk(EAngle angle, double frameSpeed);
        void AnimWait(EAngle angle);
        void PerformDead(CoroTaskYield& yield, IAppState* appState);
        void PerformWarp(CoroTaskYield& yield, const MatPos& startPos, const MatPos& endPos);
    private:
        MainScene* const mainScene;
        const Vec2<int> cellSize;
        TextureAnimator& animator;
        CharacterViewModel* const view;
    };

} // myGame

#endif //FILL_TILES_PLAYERANIMATION_H
