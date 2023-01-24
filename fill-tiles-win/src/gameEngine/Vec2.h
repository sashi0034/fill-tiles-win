//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_VEC_H
#define FILL_TILES_VEC_H

#include "sstream"

namespace gameEngine
{
    template<typename T> struct Vec2
    {
        T X;
        T Y;

        Vec2()= default;
        Vec2(T x, T y){
            X = x;
            Y = y;
        }

        Vec2<T> operator+(const Vec2<T>& other) const
        {
            return Vec2<T>{this->X + other.X, this->Y + other.Y};
        }

        Vec2<T> operator-(const Vec2<T>& other) const
        {
            return Vec2<T>{this->X - other.X, this->Y - other.Y};
        }

        Vec2<T> operator*(int times) const
        {
            return Vec2<T>{X * times, Y * times};
        }

        Vec2<T> operator*(double times) const
        {
            return Vec2<T>{T(X * times), T(Y * times)};
        }

        Vec2<T> operator/(int div) const
        {
            return Vec2<T>{static_cast<T>(X / div), static_cast<T>(Y / div)};
        }

        Vec2<T> operator/(double div) const
        {
            return Vec2<T>{static_cast<T>(X / div), static_cast<T>(Y / div)};
        }

        bool operator==(const Vec2<T>& other) const
        {
            return this->X == other.X && this->Y == other.Y;
        }

        bool operator!=(const Vec2<T>& other) const
        {
            return !(this->X == other.X && this->Y == other.Y);
        }

        template<typename U>
        Vec2<U> CastTo() const
        {
            return Vec2<U>{static_cast<U>(this->X), static_cast<U>(this->Y)};
        }

        T CalcMagnitude() const
        {
            return this->X * this->X + this->Y * this->Y;
        }

        std::string ToString() const
        {
            std::stringstream stream{};
            stream << "(" << X << ", " << Y << ")";
            return stream.str();
        }
    };

    template <class InputIterator>
    Vec2(InputIterator, InputIterator)
    -> Vec2<typename std::iterator_traits<InputIterator>::value_type>;
}

#endif //FILL_TILES_VEC_H
