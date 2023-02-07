//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_BIGTREE_H
#define FILL_TILES_BIGTREE_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace myGame::character
{
    class BigTree : public CharacterBase
    {
    public:
        BigTree(MainScene *mainScene, const MatPos &matPos);
        CharacterViewModel m_View;
    private:
        static const inline Vec2<int>cellMatSize = Vec2<int>{3, 3};
    };
}


#endif //FILL_TILES_BIGTREE_H
