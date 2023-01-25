//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_MATPOS_H
#define FILL_TILES_MATPOS_H

#include "stdafx.h"

namespace inGame
{
    class MatPos
    {
    public:
        explicit MatPos(const Vec2<int>& pos);
        MatPos(int x, int y);
        [[nodiscard]] Vec2<int> GetVec() const;
        [[nodiscard]] Vec2<double> GetVecByFiledPixel() const;
        [[nodiscard]] Vec2<double> ToPixelPos() const;

        MatPos operator+(const MatPos& other) const;
        MatPos operator-(const MatPos& other) const;
        MatPos operator*(int times) const;
        bool operator==(const MatPos& other) const;
        bool operator!=(const MatPos& other) const;

        int GetSumXY() const;
        std::string ToString() const;
        int CalcManhattan(const MatPos& other) const;
    private:
        const Vec2<int> m_Pos;

    };
}


#endif //FILL_TILES_MATPOS_H
