//
// Created by sashi0034 on 2022/06/13.
//

#include "TileMapMatElement.h"
#include "stdafx.h"
#include "../character/GlassFloor.h"

namespace inGame::field{

    TileMapMatElement::TileMapMatElement()
    {}

    void TileMapMatElement::AddChip(const TilePropertyChip *chip)
    {
        assert(!HasChip(chip->Kind));
        m_ChipList.push_back(chip);

        m_IsWall = chip->IsWall;

        m_HasChip[static_cast<int>(chip->Kind)] = true;
    }



    bool TileMapMatElement::InsertChip(const TilePropertyChip *frontChip, const TilePropertyChip *newBackChip)
    {
        assert(!HasChip(newBackChip->Kind));
        if (m_ChipList.size()==0) return false;
        auto iter = std::find(m_ChipList.begin(), m_ChipList.end(), frontChip);
        if (iter==m_ChipList.end()) return false;
        m_ChipList.insert(iter + 1, newBackChip);
        m_HasChip[static_cast<int>(newBackChip->Kind)] = true;
        return true;
    }


    bool TileMapMatElement::ReplaceChip(const TilePropertyChip *oldChip, const TilePropertyChip *newChip)
    {
        assert(!HasChip(newChip->Kind));
        if (m_ChipList.size()==0) return false;
        auto iter = std::find(m_ChipList.begin(), m_ChipList.end(), oldChip);
        if (iter==m_ChipList.end()) return false;
        *iter = newChip;
        m_HasChip[static_cast<int>(oldChip->Kind)] = false;
        m_HasChip[static_cast<int>(newChip->Kind)] = true;
        return true;
    }

    bool TileMapMatElement::RemoveChip(const TilePropertyChip *chip)
    {
        if (m_ChipList.size()==0) return false;
        auto iter = std::find(m_ChipList.begin(), m_ChipList.end(), chip);
        if (iter==m_ChipList.end()) return false;
        m_ChipList.erase(iter);
        m_HasChip[static_cast<int>(chip->Kind)] = false;
        return true;
    }

    bool TileMapMatElement::RemoveChip(const ETileKind kind)
    {
        if (m_ChipList.size() == 0) return false;
        auto iter = std::find_if(m_ChipList.begin(), m_ChipList.end(),
                                 [kind](const TilePropertyChip *chip) { return chip->Kind == kind; });
        if (iter == m_ChipList.end()) return false;
        m_ChipList.erase(iter);
        m_HasChip[static_cast<int>(kind)] = false;
        return true;
    }

    const std::vector<const TilePropertyChip *> &TileMapMatElement::GetChipList() const
    {
        return m_ChipList;
    }

    bool TileMapMatElement::HasChip(ETileKind kind)
    {
        return m_HasChip[static_cast<int>(kind)];
    }

    bool TileMapMatElement::IsWall() const
    {
        return m_IsWall;
    }

    void TileMapMatElement::OverwriteIsWall(bool isWall)
    {
        m_IsWall = isWall;
    }

    void TileMapMatElement::SetCliffFlag(EAngle aspect, bool flag)
    {
        m_CliffAspect[int(aspect)] = flag;
    }

    bool TileMapMatElement::GetCliffFlag(EAngle aspect)
    {
        return m_CliffAspect[int(aspect)];
    }

    bool TileMapMatElement::IsBloomedMineFlower() const
    {
        return m_IsBloomedMineFlower;
    }

    void TileMapMatElement::SetIsBloomedMineFlower(bool flag)
    {
        m_IsBloomedMineFlower= flag;
    }

    void TileMapMatElement::SetWallByTopTile()
    {
        const auto &lastChip = *(m_ChipList.end() - 1);
        m_IsWall = lastChip->IsWall;
    }

    character::GlassFloor *TileMapMatElement::GetGlassFloor()
    {
        return m_GlassFloor.GetPtr();
    }

    void TileMapMatElement::SetGlassFloor(character::GlassFloor *glassFloor)
    {
        m_GlassFloor = glassFloor->GetWeakPtr();
    }

    bool TileMapMatElement::IsIceFloor()
    {
        return HasChip(ETileKind::ice);
    }


}
