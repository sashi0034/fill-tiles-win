//
// Created by sashi0034 on 2022/09/17.
//

#ifndef FILL_TILES_WINTILE_H
#define FILL_TILES_WINTILE_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace myGame::character
{

    class WinTile : public CharacterBase
    {
    public:
        WinTile(MainScene *mainScene, const MatPos &matPos);
        const MatPos Pos;
    private:
        static const inline Vec2<int> cellSrcSize{24, 24};
        CharacterViewModel m_View;

        void subscribePlayer(const MatPos &matPos, Player *const player, MainScene* const scene);
    };

} // myGame::character

#endif //FILL_TILES_WINTILE_H
