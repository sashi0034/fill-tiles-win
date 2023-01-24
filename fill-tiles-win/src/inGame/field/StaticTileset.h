//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_STATICTILESET_H
#define FILL_TILES_STATICTILESET_H

#include "TileMapMatElement.h"

namespace inGame::field
{
    class StaticTileset
    {
    public:
        StaticTileset();
        TilePropertyChip* GetOf(ETileKind kind) const;
    private:
        const std::unordered_map<ETileKind, TilePropertyChip> m_StaticTileset{};
        static std::unordered_map<ETileKind, TilePropertyChip> createStaticTileset();
        static void addStaticChip(std::unordered_map<ETileKind, TilePropertyChip>* tileset, ETileKind kind, bool isWall);
    };
}


#endif //FILL_TILES_STATICTILESET_H
