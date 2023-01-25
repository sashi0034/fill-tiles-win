//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_RECT_H
#define FILL_TILES_RECT_H

#include <stdafx.h>

using std::unique_ptr;

namespace gameEngine
{
    template<typename T> struct Rect
    {
        T X;
        T Y;
        T Width;
        T Height;

        Rect(T x, T y, T width, T height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        Rect(const Vec2<T>& startingPoint, const Vec2<T>& size)
        {
            X = startingPoint.X;
            Y = startingPoint.Y;
            Width = size.X;
            Height = size.Y;
        }

        Vec2<T> GetStartingPoint() const
        {
            return Vec2<T>{X, Y};
        }

        Vec2<T> GetSize() const
        {
            return Vec2<T>{Width, Height};
        }

        bool IsIntersectWith(const Rect<T>& other) const
        {
            return std::abs(other.X + other.Width / 2.0 - (this->X + this->Width / 2.0)) < (this->Width + other.Width) / 2.0
            && std::abs(other.Y + other.Height / 2.0 - (this->Y + this->Height / 2.0)) < (this->Height + other.Height) / 2.0;
        }
    };
}


#endif //FILL_TILES_RECT_H
