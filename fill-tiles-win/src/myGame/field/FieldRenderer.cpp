//
// Created by sashi0034 on 2022/06/16.
//

#include "FieldRenderer.h"
#include "../FieldManager.h"

namespace myGame::field
{
    const int FieldRenderer::pixelPerMat = FieldManager::PixelPerMat;

    FieldRenderer::FieldRenderer(const resource::Image *image, const Vec2<int> &matPos,
                                 const Vec2<int> &screenPos, SDL_Renderer *renderer, const Vec2<int> &srcSize,
                                 const Vec2<double> &renderingSize, TileMap *tileMap)
            : m_ResImage(image),
              m_MatPos(matPos),
              m_ScreenPos(screenPos),
              m_Renderer(renderer),
              m_SrcSize(srcSize),
              m_RenderingSize(renderingSize),
              m_TileMapPtr(tileMap)
    {}

    bool FieldRenderer::RenderChip(ETileKind kind)
    {
        switch (kind)
        {
            case ETileKind::normal_plain:
                renderAutoTile(m_ResImage->normal_plain_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::normal_plain);
                });
                break;
            case ETileKind::low_basin:
                // renderBackmostGrassで塗りつぶす
                break;
            case ETileKind::low_basin_shade_face:
                renderCell(m_ResImage->low_basin_16x16.get(), Vec2<int>{4, 4});
                break;
            case ETileKind::low_basin_shade_edge:
                renderAutoTile(m_ResImage->low_basin_16x16.get(), [&](int x, int y) {
                    return !isNeighbor(x, y, ETileKind::low_basin_shade_face);
                }, Vec2<int>{4, 0} * pixelPerMat);
                break;
            case ETileKind::normal_plain_shade_face:
                renderCell(m_ResImage->normal_plain_16x16.get(), Vec2<int>{4, 4});
                break;
            case ETileKind::normal_plain_shade_edge:
                renderAutoTile(m_ResImage->normal_plain_16x16.get(), [&](int x, int y) {
                    return !isNeighbor(x, y, ETileKind::normal_plain_shade_face);
                }, Vec2<int>{4, 0} * pixelPerMat);
                break;
            case ETileKind::normal_plain_cliff:
                renderPlateauCliff(m_ResImage->normal_plain_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::normal_plain_cliff);
                    //return isNeighbor(x, y, ETileKind::normal_plain_cliff, ETileKind::normal_plain);
                });
                break;
            case ETileKind::high_plateau:
                renderAutoTile(m_ResImage->high_plateau_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::high_plateau);
                });
                break;
            case ETileKind::high_plateau_cliff:
                renderPlateauCliff(m_ResImage->high_plateau_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::high_plateau_cliff);
                    //return isNeighbor(x, y, ETileKind::high_plateau_cliff, ETileKind::high_plateau);
                });
                break;
            case ETileKind::ice:
                renderAutoTile(m_ResImage->ice_floor_16x16.get(), [&](int x, int y) {
                    return isNeighbor(x, y, ETileKind::ice);
                });
                break;
            case ETileKind::grass_checked_1:
                renderCell(m_ResImage->grass_checked_16x16.get(), Vec2<int>{0, 0});
                break;
            case ETileKind::grass_checked_2:
                renderCell(m_ResImage->grass_checked_16x16.get(), Vec2<int>{1, 0});
                break;
            case ETileKind::grass_checked_3:
                renderCell(m_ResImage->grass_checked_16x16.get(), Vec2<int>{2, 0});
                break;
            case ETileKind::grass_checked_4:
                renderCell(m_ResImage->grass_checked_16x16.get(), Vec2<int>{3, 0});
                break;
            default:
                return false;
        }

        return true;
    }


    void FieldRenderer::renderAutoTile(Graph *image, const std::function<bool(int, int)> &isNeighbor,  const Vec2<int> &targetSrcOrigin)
    {
        static const Vec2<int> srcStartingPoints[16] = {
                Vec2{0, 0} * pixelPerMat, //
                Vec2{0, 1} * pixelPerMat, //       D
                Vec2{0, 3} * pixelPerMat, //     U
                Vec2{0, 2} * pixelPerMat, //     U D
                Vec2{1, 0} * pixelPerMat, //   R
                Vec2{1, 1} * pixelPerMat, //   R   D
                Vec2{1, 3} * pixelPerMat, //   R U
                Vec2{1, 2} * pixelPerMat, //   R U D
                Vec2{3, 0} * pixelPerMat, // L
                Vec2{3, 1} * pixelPerMat, // L     D
                Vec2{3, 3} * pixelPerMat, // L   U
                Vec2{3, 2} * pixelPerMat, // L   U D
                Vec2{2, 0} * pixelPerMat, // L R
                Vec2{2, 1} * pixelPerMat, // L R   D
                Vec2{2, 3} * pixelPerMat, // L R U
                Vec2{2, 2} * pixelPerMat, // L R U D
        };

        const int srcStartingIndex =
                (int(isNeighbor(m_MatPos.X - 1, m_MatPos.Y)) << 3) +
                (int(isNeighbor(m_MatPos.X + 1, m_MatPos.Y)) << 2) +
                (int(isNeighbor(m_MatPos.X, m_MatPos.Y - 1)) << 1) +
                (int(isNeighbor(m_MatPos.X, m_MatPos.Y + 1)) << 0);

        const auto &srcStarting = srcStartingPoints[srcStartingIndex];

        image->RenderGraph(
                m_Renderer,
                m_ScreenPos, Rect<int>{srcStarting + targetSrcOrigin, m_SrcSize},
                m_RenderingSize);
    }

    void FieldRenderer::renderPlateauCliff(Graph *image, const std::function<bool(int, int)> &isNeighbor)
    {
        static const Vec2<int> srcStartingPoints[4] = {
                Vec2{0, 4} * pixelPerMat, //
                Vec2{1, 4} * pixelPerMat, //   R
                Vec2{3, 4} * pixelPerMat, // L
                Vec2{2, 4} * pixelPerMat, // L R
        };

        const int srcStartingIndex =
                (int(isNeighbor(m_MatPos.X - 1, m_MatPos.Y)) << 1) +
                (int(isNeighbor(m_MatPos.X + 1, m_MatPos.Y)) << 0);

        const auto &srcStarting = srcStartingPoints[srcStartingIndex];

        image->RenderGraph(
                m_Renderer,
                m_ScreenPos, Rect<int>{srcStarting, m_SrcSize},
                m_RenderingSize);
    }


    void FieldRenderer::renderCell(Graph *image, const Vec2<int> &cellPos)
    {
        image->RenderGraph(m_Renderer, m_ScreenPos, Rect<int>{cellPos * pixelPerMat, m_SrcSize}, m_RenderingSize);
    }

    template<class... A>
    bool FieldRenderer::isNeighbor(int x, int y, A... kinds) const
    {
        bool result = false;
        for (ETileKind kind : std::initializer_list<ETileKind>{kinds...})
            result = result ||  m_TileMapPtr->HasChipAt(Vec2{x, y}, kind) == Boolean::True;
        return result;
    }


}
