//
// Created by sashi0034 on 2022/08/06.
//

#include "MineFlowerClass.h"
#include "character/MineFlower.h"

namespace inGame
{
    MineFlowerClass::MineFlowerClass(field::ETileKind mineFlowerTile, field::ETileKind blockTile, int classLevel)
            : MineFlowerTile(mineFlowerTile), BlockTile(blockTile), m_ClassLevel{classLevel}
    {}

    void MineFlowerClass::IncreaseMineFlower()
    {
        ++m_MineFlowerCount;
    }

    void MineFlowerClass::DecreaseMineFlower()
    {
        --m_MineFlowerCount;
    }

    bool MineFlowerClass::HasMineFlower()
    {
        return m_MineFlowerCount>0;
    }

    int MineFlowerClass::GetClassLevel() const
    {
        return m_ClassLevel;
    }

    int MineFlowerClass::GetMaxMineFlowerCount() const
    {
        return m_MaxMineFlowerCount;
    }

    void MineFlowerClass::FixMaxMineFlowerCount()
    {
        assert(m_MaxMineFlowerCount==0);
        m_MaxMineFlowerCount = m_MineFlowerCount;
    }

    int MineFlowerClass::GetMineFlowerCount() const
    {
        return m_MineFlowerCount;
    }

    void MineFlowerClass::SetRespawnMatPos(const MatPos &pos)
    {
        assert(m_RespawnMatPos== nullptr);

        m_RespawnMatPos = std::make_unique<MatPos>(pos.GetVec());
    }

    MatPos MineFlowerClass::GetRespawnMatPos() const
    {
        return MatPos(m_RespawnMatPos->GetVec());
    }

    void MineFlowerClass::PushBloomedMineFlower(character::MineFlower *element)
    {
        m_BloomedMineFlowerList.push_back(element);
    }

    std::vector<character::MineFlower*> &MineFlowerClass::GetBloomedList()
    {
        return m_BloomedMineFlowerList;
    }

    MineFlowerClass *MineFlowerClass::SortBloomedListByPos(const MatPos &centerPos)
    {
        std::stable_sort(m_BloomedMineFlowerList.begin(), m_BloomedMineFlowerList.end(), [&](character::MineFlower* left, character::MineFlower* right)->bool{
            return centerPos.CalcManhattan(left->Position) < centerPos.CalcManhattan(right->Position);
        });
        return this;
    }

} // inGame