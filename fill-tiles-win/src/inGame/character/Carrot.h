//
// Created by sashi0034 on 2022/09/17.
//

#ifndef FILL_TILES_CARROT_H
#define FILL_TILES_CARROT_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace inGame::character
{
    class Carrot : public CharacterBase
    {
    public:
        Carrot(IMainScene *mainScene, const MatPos &matPos);
        CharacterViewModel m_View;
    private:
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 2};
    };
} // inGame

#endif //FILL_TILES_CARROT_H
