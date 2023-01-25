//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_GRAPH_H
#define FILL_TILES_GRAPH_H

#include <stdafx.h>
#include "Vec2.h"
#include "Rect.h"
#include "GraphBlend.h"

using std::unique_ptr;
using std::shared_ptr;

namespace gameEngine
{
    class Graph
    {
        SDL_Surface* m_SdlSurface = nullptr;
        SDL_Texture* m_SdlTexture = nullptr;

        static const inline GraphBlend defaultBlend{};
    public:
        Graph(SDL_Renderer *renderer, SDL_Surface *surface);
        Graph(SDL_Surface *surface, SDL_Texture* texture);
        Graph(SDL_Texture* texture);
        static Graph* CreateFromFilePath(SDL_Renderer *renderer, const std::string& filePath);
        ~Graph();
        [[nodiscard]] SDL_Texture* GetSdlTexture() const;
        Vec2<int> GetSize() const;
        void RenderGraph(const SDL_Renderer* renderer, const Vec2<int>& startPoint, const Rect<int>& srcRect, Vec2<double> scale, double rotationDeg=0, bool isFlipHorizontal= false, const GraphBlend &blend=defaultBlend);
    };
}


#endif //FILL_TILES_GRAPH_H
