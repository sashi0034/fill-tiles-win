//
// Created by sashi0034 on 2022/08/06.
//

#ifndef FILL_TILES_READOBJECTINOBJECTGROUP_H
#define FILL_TILES_READOBJECTINOBJECTGROUP_H

#include "../../MainScene.h"

namespace inGame::field::tileMap
{
    void ReadObjectInObjectGroup(
            MainScene* mainScene,
            const std::string &objectType,
            const std::string &objectName,
            const Vec2<int> &pos,
            std::unordered_map<std::string, std::string> &objectProperty);
}


#endif //FILL_TILES_READOBJECTINOBJECTGROUP_H
