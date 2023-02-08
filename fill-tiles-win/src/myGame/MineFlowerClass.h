//
// Created by sashi0034 on 2022/08/06.
//

#ifndef FILL_TILES_MINEFLOWERCLASS_H
#define FILL_TILES_MINEFLOWERCLASS_H

#include "ActorBase.h"
#include "field/TileMapMatElement.h"
#include "MatPos.h"

namespace myGame
{
    class MainScene;

    namespace character{
        class MineFlower;
    }

    class MineFlowerClass
    {
    public:
        MineFlowerClass(field::ETileKind mineFlowerTile, field::ETileKind blockTile, int classLevel);

        const field::ETileKind MineFlowerTile;
        const field::ETileKind BlockTile;
        void RegisterMineFlower(VecInt2 pos);
        void DecreaseMineFlower();
        bool HasMineFlower();
        void FixMaxMineFlowerCount();

        int GetClassLevel() const;
        int GetMaxMineFlowerCount() const;
        int GetMineFlowerCount() const;

        void SetRespawnMatPos(const MatPos& pos);
        [[nodiscard]] MatPos GetRespawnMatPos() const;

        void PushBloomedMineFlower(character::MineFlower* element);
        std::vector<character::MineFlower*>& GetBloomedList();
        std::vector<VecInt2>& GetAllPosList();

        MineFlowerClass* SortBloomedListByPos(const MatPos& centerPos);
    private:
        int m_MaxMineFlowerCount = 0;
        int m_MineFlowerCount = 0;
        int m_ClassLevel{};

        unique_ptr<MatPos> m_RespawnMatPos{};
        std::vector<character::MineFlower*> m_BloomedMineFlowerList;
        std::vector<VecInt2> m_AllPosList;
    };

} // myGame

#endif //FILL_TILES_MINEFLOWERCLASS_H
