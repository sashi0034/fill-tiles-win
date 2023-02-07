//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_SMALLTREE_H
#define FILL_TILES_SMALLTREE_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace myGame::character
{
    class SmallTree : public CharacterBase
    {
    public:
        SmallTree(MainScene *mainScene, const MatPos &matPos);
        CharacterViewModel m_View;
    private:
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
    };
}


#endif //FILL_TILES_SMALLTREE_H
