//
// Created by sashi0034 on 2022/08/12.
//

#ifndef FILL_TILES_GLASSFLOOR_H
#define FILL_TILES_GLASSFLOOR_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace myGame::character
{

    class GlassFloor : public CharacterBase
    {
        DEF_WEAK_GET(GlassFloor);
    public:
        GlassFloor(MainScene *mainScene, const MatPos &matPos);
        void MakeBrokenAndDestroy();
    private:
        MainScene* mainScene;
        CharacterViewModel m_View;
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{16, 16};
    };

} // myGame

#endif //FILL_TILES_GLASSFLOOR_H
