//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_FIELDRENDERER_H
#define FILL_TILES_FIELDRENDERER_H

#include <SDL_image.h>
#include "TileMapMatElement.h"
#include "TileMap.h"
#include "../resource/Image.h"

namespace myGame::field
{
    class FieldRenderer
    {
    public:
        FieldRenderer(const resource::Image *image, const Vec2<int> &matPos, const Vec2<int> &screenPos,
                      SDL_Renderer *renderer, const Vec2<int> &srcSize, const Vec2<double> &renderingSize,
                      TileMap *tileMap);
        bool RenderChip(ETileKind kind);
    private:
        static const int pixelPerMat;
        const resource::Image* m_ResImage;
        const Vec2<int>& m_MatPos;
        const Vec2<int>& m_ScreenPos;
        SDL_Renderer* m_Renderer;
        const Vec2<int>& m_SrcSize;
        const Vec2<double>& m_RenderingSize;
        TileMap* m_TileMapPtr;

        void renderAutoTile(Graph *image, const std::function<bool(int, int)> &isNeighbor,
                            const Vec2<int> &targetSrcOrigin=Vec2{0, 0});
        void renderPlateauCliff(Graph* image, const std::function<bool(int, int)>& isNeighbor);

        template <class... A>
        bool isNeighbor(int x, int y, A... kinds) const;

        void renderCell(Graph* image, const Vec2<int> &cellPos);
    };
}


#endif //FILL_TILES_FIELDRENDERER_H
