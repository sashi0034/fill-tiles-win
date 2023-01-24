//
// Created by sashi0034 on 2022/08/11.
//

#ifndef FILL_TILES_PLAYERANIMATION_H
#define FILL_TILES_PLAYERANIMATION_H

#include "../Angle.h"
#include "../../gameEngine/gameEngine.h"
#include "../MatPos.h"

namespace inGame{
    class IMainScene;
    class CharacterViewModel;
}

namespace inGame::player
{
    class PlayerAnimation
    {
    public:
        PlayerAnimation(IMainScene *mainScene, const Vec2<int> &cellSize, TextureAnimator &animator,
                        CharacterViewModel *const view);

        void AnimWalk(EAngle angle, double frameSpeed);
        void AnimWait(EAngle angle);
        void PerformDead(CoroTaskYield& yield, IAppState* appState);
        void PerformWarp(CoroTaskYield& yield, const MatPos& startPos, const MatPos& endPos);
    private:
        IMainScene* const mainScene;
        const Vec2<int> cellSize;
        TextureAnimator& animator;
        CharacterViewModel* const view;
    };

} // inGame

#endif //FILL_TILES_PLAYERANIMATION_H
