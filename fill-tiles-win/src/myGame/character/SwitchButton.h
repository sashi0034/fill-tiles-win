//
// Created by sashi0034 on 2022/08/15.
//

#ifndef FILL_TILES_SWITCHBUTTON_H
#define FILL_TILES_SWITCHBUTTON_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"


namespace myGame::character
{

    class SwitchButton : public CharacterBase
    {
    public:
        SwitchButton(MainScene *mainScene, const MatPos &matPos);
    private:
        MainScene* mainScene;
        CharacterViewModel m_View;
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};

        void subscribePlayer(const MatPos &matPos, const Player *player);
        TextureAnimationWeakPtr m_Animation{};

        void resetAnimation();
    };

} // myGame

#endif //FILL_TILES_SWITCHBUTTON_H
