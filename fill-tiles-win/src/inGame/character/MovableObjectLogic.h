//
// Created by sashi0034 on 2022/08/13.
//

#ifndef FILL_TILES_MOVABLEOBJECTLOGIC_H
#define FILL_TILES_MOVABLEOBJECTLOGIC_H

#include "CharacterBase.h"
#include "../MatPos.h"
#include "../MainScene.h"
#include "../CharacterViewModel.h"
#include "../UpFlag.h"

namespace inGame::character
{

    class MovableObjectLogic
    {
    public:
        bool CanMove(EAngle angle);
        void ForceMove(EAngle angle);

        MovableObjectLogic(MainScene *mainScene, CharacterViewModel *view);
    private:
        void move(CoroTaskYield& yield, EAngle angle);

        MainScene* mainScene;
        CharacterViewModel* view;
    };

} // inGame

#endif //FILL_TILES_MOVABLEOBJECTLOGIC_H
