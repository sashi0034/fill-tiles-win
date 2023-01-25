//
// Created by sashi0034 on 2022/08/21.
//

#ifndef FILL_TILES_WARPMANAGER_H
#define FILL_TILES_WARPMANAGER_H

#include "stdafx.h"

namespace inGame
{
    namespace character
    {
        class WarpTile;
    }

    class WarpTileSet
    {
    public:
        void AddTile(character::WarpTile* tile);
        character::WarpTile* GetNext(character::WarpTile* tile);
    private:
        // todo: 念のためWeakPtrに変える
        std::vector<character::WarpTile*> setList{};
    };

    class WarpManager
    {
    public:
        [[nodiscard("キャッシュを取ってください。")]] WarpTileSet* Register(char key, character::WarpTile* warpTile);
    private:
        std::unordered_map<char, WarpTileSet> m_WarpTable;
    };

} // inGame

#endif //FILL_TILES_WARPMANAGER_H
