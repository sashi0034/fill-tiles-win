//
// Created by sashi0034 on 2022/07/18.
//

#ifndef FILL_TILES_CATFISH_H
#define FILL_TILES_CATFISH_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../CharacterViewModel.h"
#include "../ParabolaAnimation.h"
#include "MovableObjectLogic.h"

namespace myGame::character
{

    class Catfish final: public CharacterBase, public ISprRectColliderOwner
    {
    public:
        Catfish(MainScene *mainScene, const MatPos &matPos);
        ParabolaAnimation * JumpWhenEat();
        MovableObjectLogic* GetMovable();
        void ScrapSelf();

        void Update(IAppState *app) override;
        UpFlag& GetEatableFlag();
        //CharacterViewModel* const GetView();
    private:
        MainScene* m_Scene;
        CharacterViewModel m_View{};
        UpFlag m_EatableFlag{};
        MovableObjectLogic m_MovableObjectLogic;

        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{24, 24};
    };

} // myGame

#endif //FILL_TILES_CATFISH_H
