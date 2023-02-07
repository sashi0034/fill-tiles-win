//
// Created by sashi0034 on 2022/07/18.
//

#ifndef FILL_TILES_PLAYERACTIONDATA_H
#define FILL_TILES_PLAYERACTIONDATA_H


namespace myGame{
    namespace character
    {
        class Catfish;
    }
}

namespace myGame::player
{


    class PlayerActionData
    {
    public:
        virtual ~PlayerActionData() = default;
    };

    class PlayerActionPushCatfish : public PlayerActionData
    {
    public:
        character::Catfish* const TouchedCatfish;

        explicit PlayerActionPushCatfish(character::Catfish *const touchedCatfish);
    };

} // myGame

#endif //FILL_TILES_PLAYERACTIONDATA_H
