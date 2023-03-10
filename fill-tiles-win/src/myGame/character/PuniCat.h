//
// Created by sashi0034 on 2022/07/18.
//

#ifndef FILL_TILES_PUNICAT_H
#define FILL_TILES_PUNICAT_H

#include "CharacterBase.h"
#include "../MainScene.h"
#include "../MatPos.h"
#include "../CharacterViewModel.h"

namespace myGame::character
{
    class Catfish;

    class PuniCat final: public CharacterBase, public ISprRectColliderOwner
    {
    public:
        PuniCat(MainScene *mainScene, const MatPos &matPos);

        void Update(IAppState *app) override;
    private:
        MainScene* m_Scene;
        CharacterViewModel m_View;
        TextureAnimationWeakPtr m_AnimationRef{};

        void animByAngle(EAngle angle);

        void moveToEatFish(CoroTaskYield &yield, Catfish *targetFood, const MatPos &goingPos, EAngle angle);

        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{24, 24};

        void subscribePlayerAction(MainScene *mainScene, const Player *player);

        void searchCatfishEveryAngle(MainScene *mainScene, Catfish *nullableTargetCatfish);

        void
        startGoToEatCatfish(MainScene *mainScene, Catfish *targetCatfish, const Vec2<int> &stepVec,
                            const MatPos &checkingPos, EAngle angle);
    };

} // myGame

#endif //FILL_TILES_PUNICAT_H
