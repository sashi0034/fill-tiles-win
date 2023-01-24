//
// Created by sashi0034 on 2022/06/16.
//

#include "MatPos.h"
#include "sstream"
#include "FieldManager.h"

namespace inGame
{
    MatPos::MatPos(const Vec2<int> &pos)
    : m_Pos(pos)
    {}

    Vec2<int> MatPos::GetVec() const
    {
        return m_Pos;
    }

    Vec2<double> MatPos::GetVecByFiledPixel() const
    {
        return m_Pos.CastTo<double>() * FieldManager::PixelPerMat;
    }

    MatPos MatPos::operator+(const MatPos &other) const
    {
        return MatPos(this->m_Pos + other.m_Pos);
    }

    MatPos MatPos::operator-(const MatPos &other) const
    {
        return MatPos(this->m_Pos - other.m_Pos);
    }

    MatPos MatPos::operator*(int times) const
    {
        return MatPos(this->m_Pos * times);
    }

    MatPos::MatPos(int x, int y)
    : MatPos(Vec2<int>{x, y})
    {}

    std::string MatPos::ToString() const
    {
        std::stringstream stream{};
        stream << "(" << m_Pos.X << ", " << m_Pos.Y << ")";
        return stream.str();
    }

    Vec2<double> MatPos::ToPixelPos() const
    {
        return (m_Pos * FieldManager::PixelPerMat).CastTo<double>();
    }

    int MatPos::GetSumXY() const
    {
        return m_Pos.X+m_Pos.Y;
    }

    int MatPos::CalcManhattan(const MatPos &other) const
    {
        auto otherPos = other.GetVec();
        const int diffX = this->m_Pos.X - otherPos.X;
        const int diffY = this->m_Pos.Y - otherPos.Y;

        return std::abs(diffX) + std::abs(diffY);
    }

    bool MatPos::operator==(const MatPos &other) const
    {
        return other.GetVec() == m_Pos;
    }

    bool MatPos::operator!=(const MatPos &other) const
    {
        return other.GetVec() != m_Pos;
    }

}
