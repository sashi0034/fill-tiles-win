//
// Created by sashi0034 on 2022/08/15.
//

#ifndef FILL_TILES_SWITCHACORN_H
#define FILL_TILES_SWITCHACORN_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"

namespace inGame{
    class SwitchAcornManager;
}


namespace inGame::character
{
    enum class ESwitchAcornKind
    {
        Red = 0,
        Blue,
        Max
    };

    class SwitchAcorn : public CharacterBase
    {
        DEF_WEAK_GET(SwitchAcorn);
    public:
        SwitchAcorn(IMainScene *mainScene, const MatPos &matPos, ESwitchAcornKind kind);
    private:
        const ESwitchAcornKind selfKind;
        IMainScene *mainScene;
        CharacterViewModel m_View;
        MatPos initialPos;
        static const inline Vec2<int> cellMatSize = Vec2<int>{1, 1};

        TextureAnimationWeakPtr m_TextureAnimation{};

        void onSwitch(ESwitchAcornKind nextKind);
        SwitchAcornManager* getAcornManager();
    };

} // inGame

#endif //FILL_TILES_SWITCHACORN_H
