//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_TILEMAP_H
#define FILL_TILES_TILEMAP_H

#include "../../myUtil/myUtil.h"

#include "TileMapMatElement.h"

#include "StaticTileset.h"
#include "../MatPos.h"

namespace myGame{
    class MainScene;
    class FieldManager;
}

namespace myGame::field
{
    class TileMap
    {
    public:
        explicit TileMap(MainScene *mainScene);
        void LoadMapFile(const std::string &fileName);
        Vec2<int> GetMatSize() const;
        Vec2<int> GetSizeByPixel() const;
        TileMapMatElement * GetElementAt(const Vec2<int>& pos);
        TileMapMatElementWritable * GetElementWritableAt(const Vec2<int>& pos);
        bool IsInRange(const Vec2<int>& pos) const;
        Boolean HasChipAt(const Vec2<int> &pos, ETileKind checkingKind);
        Graph& GetTilesetImage() const;
        const StaticTileset &GetStaticTileSet();
        TilePropertyChip* GetTilePropOf(ETileKind kind);

        static inline const std::string TileMapDirectory = "./assets/tilemaps/";
    private:
        MainScene* m_MainScene;
        unique_ptr<Graph> m_TilesetImage{};
        std::unordered_map<int, TilePropertyChip> m_Tileset;
        std::unordered_map<ETileKind, TilePropertyChip*> m_TilesetByKind{};
        const StaticTileset staticTileset{};
        Vec2<int> m_MatSize{};
        std::vector<TileMapMatElement> m_Mat{};

        void loadTilesetFile(const std::string &fileName);

        void readTileProperty(
                const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &property,
                TilePropertyChip *propertyRef);

        void readLayerData(
                const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeData);
        void readObjectGroup(const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeObjectGroup);

        template<typename T>
        static std::vector<T> parseCsv(const std::string &source);

        void resizeMat(int mapWidth, int mapHeight);

        void readLayersAndObjects(
                boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> treeMap);

        TileMapMatElement* getElementAt(const Vec2<int>& pos);

        void initMatElementsAfterLoaded();

        void checkCliff(const Vec2<int> &pos);
        void checkCliffShade(const Vec2<int> &pos);

        void
        checkCliffShadeOf(const Vec2<int> &pos, ETileKind upperKind, ETileKind upperCliffKind, TilePropertyChip *lowerChip,
                          TilePropertyChip *lowerShadeFace, TilePropertyChip *lowerShadeEdge);
        void checkCliffFlagOf(const Vec2<int> &pos, ETileKind checkingKind, ETileKind cliffKind);

        void initTilePropertyByKind(TilePropertyChip *propertyRef, const ETileKind &kind) const;

        bool isChipStairAt(const Vec2<int>& pos);
    };
}


#endif //FILL_TILES_TILEMAP_H
