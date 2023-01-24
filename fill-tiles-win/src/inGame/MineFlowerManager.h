//
// Created by sashi0034 on 2022/06/24.
//

#ifndef FILL_TILES_MINEFLOWERMANAGER_H
#define FILL_TILES_MINEFLOWERMANAGER_H


#include "MineFlowerClass.h"
#include "UpFlag.h"

namespace inGame
{
    class MineFlowerManager
    {
    public:
        explicit MineFlowerManager(IMainScene *mainScene);
        void Init();
        MineFlowerClass* GetCurrMineFlowerClass();
        MineFlowerClass* GetNextMineFlowerClass();
        MineFlowerClass* GetMineFlowerClassByLevel(int level);

        bool IsMineFlowerMat(const MatPos& matPos) const;
        void CheckStepOnMine(const MatPos &pos);
    private:
        IMainScene* m_MainScene;
        std::vector<MineFlowerClass> m_MineFlowerClass{};
        MineFlowerClass* m_CurrMineFlowerClass{};
        UpFlag AliveFlag{};

        void initMineFlowerCount(MineFlowerClass& mineClass);
        void removeAlreadyClearedBlocks();

        bool checkBloomMineFlower(const MatPos& matPos, MineFlowerClass& mineClass);
        void bloomNewMineFlower(const MatPos &matPos, MineFlowerClass &mineClass, IFieldManager *const field) const;

        static CoroTask driveClearingCheckpointBlocksEvent(CoroTaskYield &yield, MineFlowerManager *self, MineFlowerClass& mineClass);
        CoroTask fadeMineFlowersOneByOne(CoroTaskYield& yield, MineFlowerClass& mineClass);

        void onStepOnMine(const MatPos &matPos);
    };
}


#endif //FILL_TILES_MINEFLOWERMANAGER_H
