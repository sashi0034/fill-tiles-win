//
// Created by sashi0034 on 2022/07/13.
//

#ifndef FILL_TILES_FAIRY_H
#define FILL_TILES_FAIRY_H


#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../FieldManager.h"
#include "../CharacterViewModel.h"
#include "../PollFlag.h"

namespace inGame{
    class TalkingBalloon;
}

namespace inGame::character
{
    class Fairy : public CharacterBase, public ISprRectColliderOwner
    {
    public:
        Fairy(MainScene *mainScene, const MatPos &matPos, const std::string &message);
    private:
        CharacterViewModel m_View;
        WeakPtr<TalkingBalloon> m_TalkingRef;
        PollFlag m_AwayFromPlayerFlag{true};
        static const inline Vec2<int>cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int>cellSrcSize = Vec2<int>{24, 24};

        void subscribePlayerMove(MainScene *mainScene, const MatPos &selfMatPos, const std::string &message,
                                 const Player *player);
    };
}


#endif //FILL_TILES_FAIRY_H
