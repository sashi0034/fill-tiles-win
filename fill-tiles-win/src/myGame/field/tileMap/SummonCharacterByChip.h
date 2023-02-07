//
// Created by sashi0034 on 2022/08/12.
//

#ifndef FILL_TILES_SUMMONCHARACTERBYCHIP_H
#define FILL_TILES_SUMMONCHARACTERBYCHIP_H

#include "../../../myUtil/myUtil.h"


namespace myGame{
    class MainScene;
    class ETileKind;
}

namespace myGame::field::tileMap
{

    bool SummonCharacterByChip(MainScene* mainScene, const Vec2<int> &pos, ETileKind kind);

} // myGame

#endif //FILL_TILES_SUMMONCHARACTERBYCHIP_H
