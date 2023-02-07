//
// Created by sashi0034 on 2022/06/16.
//

#include "StaticTileset.h"

namespace myGame::field
{
    StaticTileset::StaticTileset()
    : m_StaticTileset(createStaticTileset())
    {}

    std::unordered_map<ETileKind, TilePropertyChip> StaticTileset::createStaticTileset()
    {
        auto tileset = std::unordered_map<ETileKind, TilePropertyChip>();

        addStaticChip(&tileset, ETileKind::low_basin_shade_edge, false);
        addStaticChip(&tileset, ETileKind::low_basin_shade_face, false);

        addStaticChip(&tileset, ETileKind::normal_plain_cliff, true);
        addStaticChip(&tileset, ETileKind::normal_plain_shade_edge, false);
        addStaticChip(&tileset, ETileKind::normal_plain_shade_face, false);

        addStaticChip(&tileset, ETileKind::high_plateau_cliff, true);

        return tileset;
    }


    void StaticTileset::addStaticChip(std::unordered_map<ETileKind, TilePropertyChip> *tileset, ETileKind kind, bool isWall)
    {
        assert((*tileset).count(kind) == 0);
        (*tileset)[kind] = TilePropertyChip{kind, isWall, Vec2{0, 0}};
    }

    TilePropertyChip *StaticTileset::GetOf(ETileKind kind) const
    {
        auto iter = m_StaticTileset.find(kind);
        assert(iter != m_StaticTileset.end());
        auto ret = &iter->second;
        return const_cast<TilePropertyChip*>(ret);
    }
}
