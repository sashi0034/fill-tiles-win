//
// Created by sashi0034 on 2022/08/13.
//

#ifndef FILL_TILES_SOLIDROCK_H
#define FILL_TILES_SOLIDROCK_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../CharacterViewModel.h"
#include "MovableObjectLogic.h"

namespace inGame::character
{

    class SolidRock : public CharacterBase, public ISprRectColliderOwner
    {
    public:
        SolidRock(IMainScene *mainScene, const MatPos &matPos);
        CharacterViewModel m_View;
        void Update(IAppState *app) override;
        MovableObjectLogic* GetMovable();
    private:
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        MovableObjectLogic m_Movable;
    };

} // inGame

#endif //FILL_TILES_SOLIDROCK_H
