//
// Created by sashi0034 on 2022/07/18.
//

#include "PlayerActionData.h"

namespace myGame::player
{
    PlayerActionPushCatfish::PlayerActionPushCatfish(character::Catfish *const touchedCatfish) : TouchedCatfish(
            touchedCatfish)
    {}
} // myGame