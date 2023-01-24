//
// Created by sashi0034 on 2022/08/12.
//

#ifndef FILL_TILES_SUMMONCHARACTERBYCHIP_H
#define FILL_TILES_SUMMONCHARACTERBYCHIP_H

#include "../../../gameEngine/gameEngine.h"


namespace inGame{
    class IMainScene;
    class ETileKind;
}

namespace inGame::field::tileMap
{

    bool SummonCharacterByChip(IMainScene* mainScene, const Vec2<int> &pos, ETileKind kind);

} // inGame

#endif //FILL_TILES_SUMMONCHARACTERBYCHIP_H
