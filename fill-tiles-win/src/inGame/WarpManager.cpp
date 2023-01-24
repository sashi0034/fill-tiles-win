//
// Created by sashi0034 on 2022/08/21.
//

#include "WarpManager.h"

namespace inGame
{
    void WarpTileSet::AddTile(character::WarpTile *tile)
    {
        setList.emplace_back(tile);
    }

    character::WarpTile *WarpTileSet::GetNext(character::WarpTile *tile)
    {
        int index = arrayUtil::FindIndex(&setList, tile);
        assert(index!=-1);
        return setList[(index + 1) % int(setList.size())];
    }

    WarpTileSet* WarpManager::Register(char key, character::WarpTile* warpTile)
    {
        auto&& warpSet = m_WarpTable[key];
        warpSet.AddTile(warpTile);
        return &warpSet;
    }
} // inGame
