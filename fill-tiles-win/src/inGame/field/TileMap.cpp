//
// Created by sashi0034 on 2022/06/11.
//

#include "TileMap.h"
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <regex>
#include "magic_enum.h"
#include "../GameRoot.h"
#include "../Player.h"
#include "../FieldManager.h"
#include "tileMap/ReadObjectInObjectGroup.h"
#include "tileMap/SummonCharacterByChip.h"


namespace inGame::field
{

    TileMap::TileMap(IMainScene *mainScene)
    : m_MainScene(mainScene)
    {}


    template<typename T>
    std::vector<T> TileMap::parseCsv(const std::string &source)
    {
        auto result = std::vector<T>{};

        const auto crlf = std::regex("\r?\n");
        const std::string lf = "\n";
        const auto sourceLf = std::regex_replace(source, crlf, lf);

        std::stringstream stream(sourceLf);
        std::string line{};

        while (std::getline(stream, line))
        {
            boost::tokenizer<boost::escaped_list_separator<char> > tokenList(line);
            for (const std::string &str: tokenList)
            {
                if (str == "") continue;
                try
                {
                    T parsedValue = boost::lexical_cast<T>(str);
                    result.push_back(parsedValue);
                }
                catch (boost::bad_lexical_cast &)
                {
                    assert(false);
                    result.push_back(0);
                }
            }
        }
        return result;
    }

    /*
     *  Main Process Of Loading Map File.
     */
    void TileMap::LoadMapFile(const std::string &fileName)
    {
        using namespace boost::property_tree;

        const std::string filePath = TileMapDirectory + fileName;
        ptree xmlMap;
        read_xml(filePath, xmlMap);

        const auto treeMap = xmlMap.get_child("map");
        const auto treeTileset = treeMap.get_child("tileset");
        const std::string tilesetFileName = treeTileset.get<std::string>("<xmlattr>.source");
        loadTilesetFile(tilesetFileName);

        const int mapWidth = boost::lexical_cast<int>(treeMap.get<std::string>("<xmlattr>.width"));
        const int mapHeight = boost::lexical_cast<int>(treeMap.get<std::string>("<xmlattr>.height"));

        resizeMat(mapWidth, mapHeight);

        readLayersAndObjects(treeMap);

        initMatElementsAfterLoaded();
    }

    void TileMap::readLayersAndObjects(
            boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> treeMap)
    {
        for (const auto &treeLayer: treeMap.get_child(""))
        {
            if (treeLayer.first == "layer")
                readLayerData(treeLayer.second.get_child("data"));

            if (treeLayer.first == "objectgroup")
                readObjectGroup(treeLayer.second.get_child(""));
        }
    }

    void TileMap::resizeMat(const int mapWidth, const int mapHeight)
    {
        m_MatSize = Vec2{mapWidth, mapHeight};
        m_Mat.resize(mapWidth*mapHeight, TileMapMatElement());

    }


    void TileMap::initMatElementsAfterLoaded()
    {
        for (int x=0; x<m_MatSize.X; ++x)
            for (int y = 0; y < m_MatSize.Y; ++y)
                checkCliff(Vec2{x, y});

        for (int x=0; x<m_MatSize.X; ++x)
            for (int y = 0; y < m_MatSize.Y; ++y)
                checkCliffShade(Vec2{x, y});
    }

    // @tileSwitch
    void TileMap::checkCliff(const Vec2<int> &pos)
    {
        checkCliffFlagOf(pos, ETileKind::high_plateau, ETileKind::high_plateau_cliff);
        checkCliffFlagOf(pos, ETileKind::normal_plain, ETileKind::normal_plain_cliff);
    }

    // @tileSwitch
    void TileMap::checkCliffFlagOf(const Vec2<int> &pos, ETileKind checkingKind, ETileKind cliffKind)
    {
        if (HasChipAt(pos, checkingKind) == Boolean::False &&
            HasChipAt(pos + Vec2{1, 0}, checkingKind) == Boolean::True)
        {
            getElementAt(pos)->SetCliffFlag(EAngle::Right, true);
            getElementAt(pos + Vec2{1, 0})->SetCliffFlag(EAngle::Left, true);
        }

        if (HasChipAt(pos, checkingKind) == Boolean::False &&
            HasChipAt(pos + Vec2{-1, 0}, checkingKind) == Boolean::True)
        {
            getElementAt(pos)->SetCliffFlag(EAngle::Left, true);
            getElementAt(pos + Vec2{-1, 0})->SetCliffFlag(EAngle::Right, true);
        }

        if (HasChipAt(pos, checkingKind) == Boolean::False &&
            HasChipAt(pos + Vec2{0, 1}, checkingKind) == Boolean::True)
        {
            getElementAt(pos)->SetCliffFlag(EAngle::Down, true);
            getElementAt(pos + Vec2{0, 1})->SetCliffFlag(EAngle::Up, true);
        }

        if (HasChipAt(pos, checkingKind) == Boolean::False &&
            HasChipAt(pos + Vec2{0, -1}, checkingKind) == Boolean::True &&
            HasChipAt(pos, ETileKind::stairs) != Boolean::True)
        {
            getElementAt(pos)->AddChip(staticTileset.GetOf(cliffKind));
        }
    }

    void TileMap::checkCliffShade(const Vec2<int> &pos)
    {
        checkCliffShadeOf(pos, ETileKind::high_plateau, ETileKind::high_plateau_cliff,
                         m_TilesetByKind[ETileKind::normal_plain],
                         staticTileset.GetOf(ETileKind::normal_plain_shade_face), staticTileset.GetOf(ETileKind::normal_plain_shade_edge));

        checkCliffShadeOf(pos, ETileKind::normal_plain, ETileKind::normal_plain_cliff,
                          m_TilesetByKind[ETileKind::low_basin],
                          staticTileset.GetOf(ETileKind::low_basin_shade_face), staticTileset.GetOf(ETileKind::low_basin_shade_edge));
    }


    void
    TileMap::checkCliffShadeOf(const Vec2<int> &pos, ETileKind upperKind, ETileKind upperCliffKind, TilePropertyChip *lowerChip,
                               TilePropertyChip *lowerShadeFace, TilePropertyChip *lowerShadeEdge)
    {
        assert(lowerChip);
        assert(lowerShadeFace);
        assert(lowerShadeEdge);

        const auto isUpper = [&](const Vec2<int> &position) {
            return (HasChipAt(position, upperKind) == Boolean::True ||
                    HasChipAt(position, upperCliffKind) == Boolean::True);
        };

        if ((isUpper(pos)) && HasChipAt(pos, lowerChip->Kind) == Boolean::True)
        {
            bool hasEdge = false;
            for (int y = -1; y <= 1; ++y)
                for (int x = -1; x <= 1; ++x)
                {
                    if (x == 0 && y == 0) continue;

                    const auto edgePos = pos + Vec2{x, y};
                    if (!IsInRange(edgePos)) continue;
                    if (isUpper(edgePos)) continue;

                    hasEdge = true;

                    if (getElementAt(edgePos)->HasChip(lowerShadeEdge->Kind)) continue;
                    
                    getElementAt(edgePos)->InsertChip(lowerChip, lowerShadeEdge);
                }

            if (hasEdge) getElementAt(pos)->InsertChip(lowerChip, lowerShadeFace);
        }
    }




    void TileMap::readLayerData(
            const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeData)
    {
        using namespace boost::property_tree;

        const auto data = treeData.get_value<std::string>();
        const auto parsedData = parseCsv<int>(data);
        const int dataSize = parsedData.size();
        assert(dataSize == m_MatSize.X * m_MatSize.Y);

        for (int y = 0; y < m_MatSize.Y; ++y)
        {
            for (int x = 0; x < m_MatSize.X; ++x)
            {
                const int index = x + y * m_MatSize.X;

                // Tiledのレイヤー要素のマップタイルIDは+1加算されているので、-1が必要
                const int chipId = parsedData[index] - 1;

                if (chipId == -1) continue;

                LOG_ASSERT(m_Tileset.count(chipId) != 0, "登録されていないマップチップがあります。");

                TilePropertyChip *chipPtr = &m_Tileset[chipId];
                bool isSummoned = tileMap::SummonCharacterByChip(m_MainScene, Vec2<int>{x, y}, chipPtr->Kind);
                if (!isSummoned) getElementAt(Vec2{x, y})->AddChip(chipPtr);

            }
        }
    }



    void TileMap::readObjectGroup(
            const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &treeObjectGroup)
    {
        using namespace boost::property_tree;

        for (const auto &treeLayer: treeObjectGroup.get_child(""))
        {
            if (treeLayer.first != "object") continue;

            const auto treeObject = treeLayer.second.get_child("");
            const std::string objectType = treeObject.get<std::string>("<xmlattr>.class");
            const std::string objectName = treeObject.get<std::string>("<xmlattr>.name");
            const int objectX = boost::lexical_cast<int>(treeObject.get<std::string>("<xmlattr>.x"));
            const int objectY = boost::lexical_cast<int>(treeObject.get<std::string>("<xmlattr>.y"));

            std::unordered_map<std::string, std::string> objectProperty{};
            if (const auto properties = treeObject.get_child_optional("properties"))
                for (const auto& property : properties.get())
                {
                    if (property.first != "property") continue;
                    const std::string propertyName =  property.second.get<std::string>("<xmlattr>.name");
                    const std::string propertyValue =  property.second.get<std::string>("<xmlattr>.value");
                    objectProperty[propertyName] = propertyValue;
                }

            tileMap::ReadObjectInObjectGroup(m_MainScene, objectType, objectName, Vec2<int>{objectX, objectY}, objectProperty);
        }
    }


    void TileMap::loadTilesetFile(const std::string &fileName)
    {
        using namespace boost::property_tree;

        const std::string filePath = TileMapDirectory + fileName;
        ptree xmlTileset;
        read_xml(filePath, xmlTileset);

        const auto treeTileset = xmlTileset.get_child("tileset");
        const int numColumns = boost::lexical_cast<int>(treeTileset.get<std::string>("<xmlattr>.columns"));
        const int tileWidth = boost::lexical_cast<int>(treeTileset.get<std::string>("<xmlattr>.tilewidth"));
        const int tileHeight = boost::lexical_cast<int>(treeTileset.get<std::string>("<xmlattr>.tileheight"));
        const std::string imageName = treeTileset.get<std::string>("image.<xmlattr>.source");

        m_TilesetImage.reset(Graph::CreateFromFilePath(GameRoot::GetInstance().GetAppState()->GetRenderer(),
                                                       TileMapDirectory + imageName));

        for (const auto &tile: treeTileset)
        {
            if (tile.first != "tile") continue;

            const int id = boost::lexical_cast<int>(tile.second.get<std::string>("<xmlattr>.id"));

            auto newTile = TilePropertyChip{};
            newTile.SrcPoint = Vec2{(id % numColumns) * tileWidth, (id / numColumns) * tileHeight};

            for (const auto &property: tile.second.get_child("properties"))
            {
                readTileProperty(property.second, &newTile);
            }

            LOG_ASSERT(newTile.Kind != ETileKind::none, "Tile property may not be registered at ETileKind.");

            m_Tileset[id] = newTile;
            m_TilesetByKind[newTile.Kind] = &m_Tileset[id];
        }


    }

    void
    TileMap::readTileProperty(
            const boost::property_tree::basic_ptree<std::basic_string<char>, std::basic_string<char>> &property,
            TilePropertyChip *propertyRef)
    {
        const auto propertyName = property.get<std::string>("<xmlattr>.name");
        const auto value = property.get<std::string>("<xmlattr>.value");

        if (propertyName == "kind")
        {
            ETileKind kind = magic_enum::enum_cast<ETileKind>(value).value_or(ETileKind::none);
            propertyRef->Kind = kind;

            initTilePropertyByKind(propertyRef, kind);
        }
        else
        {
            assert(!"Invalid chip property exit.");
        }
    }

    // @tileSwitch
    void TileMap::initTilePropertyByKind(TilePropertyChip *propertyRef, const ETileKind &kind) const
    {
        switch (kind)
        {
//            case ETileKind::checkpoint_block_1:
//            case ETileKind::checkpoint_block_2:
//            case ETileKind::checkpoint_block_3:
//            case ETileKind::checkpoint_block_4:
//                propertyRef->IsWall = true;
            default:
                break;
        }
        (void)propertyRef;
    }

    Vec2<int> TileMap::GetMatSize() const
    {
        return m_MatSize;
    }

    Vec2<int> TileMap::GetSizeByPixel() const
    {
        return m_MatSize * FieldManager::PixelPerMat;
    }


    ITileMapMatElement * TileMap::GetElementAt(const Vec2<int> &pos)
    {
        return getElementAt(pos);
    }

    ITileMapMatElementWritable *TileMap::GetElementWritableAt(const Vec2<int> &pos)
    {
        return getElementAt(pos);
    }


    Graph &TileMap::GetTilesetImage() const
    {
        return *m_TilesetImage;
    }

    TileMapMatElement* TileMap::getElementAt(const Vec2<int> &pos)
    {
        int index = pos.X + pos.Y * m_MatSize.X;

        assert(Range<int>(0, m_Mat.size()-1).IsBetween(index));

        const TileMapMatElement* element = &m_Mat[index];

        return const_cast<TileMapMatElement*>(element);
    }

    bool TileMap::IsInRange(const Vec2<int>& pos) const
    {
        return Range<int>(0, m_MatSize.X-1).IsBetween(pos.X)
        && Range<int>(0, m_MatSize.Y-1).IsBetween(pos.Y);
    }

    Boolean TileMap::HasChipAt(const Vec2<int> &pos, ETileKind checkingKind)
    {
        if (!IsInRange(pos)) return Boolean::Null;
        const auto element = getElementAt(pos);
        return static_cast<Boolean>(element->HasChip(checkingKind));
    }

    const StaticTileset &TileMap::GetStaticTileSet()
    {
        return staticTileset;
    }


}

