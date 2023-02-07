//
// Created by sashi0034 on 2022/08/31.
//

#ifndef FILL_TILES_PLUSMINUSSIGN_H
#define FILL_TILES_PLUSMINUSSIGN_H

#include "../Angle.h"

namespace myGame::title
{

    class PlusMinusSign
    {
    public:
        static PlusMinusSign FromHorizontal(EAngle angle);
        explicit PlusMinusSign(int value);
        bool HasValue() const;
        const int Value;
    };

} // myGame

#endif //FILL_TILES_PLUSMINUSSIGN_H
