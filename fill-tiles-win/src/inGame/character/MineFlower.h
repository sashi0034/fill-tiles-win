//
// Created by sashi0034 on 2022/06/26.
//

#ifndef FILL_TILES_MINEFLOWER_H
#define FILL_TILES_MINEFLOWER_H


#include "CharacterBase.h"
#include "../MainScene.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{
    class MineFlower : public CharacterBase
    {
    public:
        MineFlower(MainScene *mainScene, const MatPos &matPos);
        const MatPos Position;
    private:
        CharacterViewModel m_View;
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
    };
}


#endif //FILL_TILES_MINEFLOWER_H
