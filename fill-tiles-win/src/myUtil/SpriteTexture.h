//
// Created by sashi0034 on 2022/05/13.
//

#ifndef FILL_TILES_SPRITETEXTURE_H
#define FILL_TILES_SPRITETEXTURE_H

#include <stdafx.h>
#include "WeakPtr.h"
#include "Vec2.h"
#include "Graph.h"
#include "GraphBlend.h"
#include "AppState.h"
#include "renderingProcess.h"

using std::unique_ptr;

namespace myUtil
{
    class SpriteTextureContext
    {
    public:
        void RenderAll(IAppState* appState);
        void UpdateAll(IAppState* appState);
        void AddSprite(SpriteTexture& texture);
        Graph* const GetRenderingBuffer();
        static SpriteTextureContext* const Global();
    private:
        static SpriteTextureContext globalInstance;

        unique_ptr<Graph> _renderingBuffer{};
        Vec2<int> _renderingSize{};
        std::vector<WeakPtr<SpriteTexture>> _spriteTexturePool;

        void checkResetRenderingBuffer(IAppState* appState);
        void resetRenderingBuffer(IAppState* appState, Vec2<int> newSize);
        void collectGarbageInSpriteTexturePool(std::vector<int>& garbageIndexes);
    };

    class SpriteTexture
    {
        DEF_WEAK_CONTROLLER(SpriteTexture);

        Vec2<double> m_Position{0, 0};
        WeakPtr<SpriteTexture> m_PositionParent{};
        double m_Z{};
        Graph* m_Graph{};
        Rect<int> m_SrcRect{0, 0, 0, 0};
        Vec2<double> m_Scale{1.0, 1.0};
        bool m_IsFlip = false;
        double m_RotationDeg = 0;
        GraphBlend m_Blend{};
        bool m_IsVisible = true;
        WeakPtr<SpriteTexture> m_VisibilityParent{};

        std::function<void(IAppState*)> m_RenderingProcess;
        std::function<void(IAppState*)> m_UpdateProcess;

        SpriteTexture();
        SpriteTexture(Graph *graph, const Rect<int> &srcRect);
    public:
        static SpriteTexture Create();
        static SpriteTexture Create(Graph *graph);
        static SpriteTexture Create(Graph *graph, const Rect<int> &srcRect);

        void SetPosition(const Vec2<double>& pos);
        [[nodiscard]] Vec2<double> GetPosition() const;

        void SetZ(double z);
        [[nodiscard]] double GetZ() const;

        void SetGraph(Graph* graph);
        [[nodiscard]] Graph* GetGraph() const;

        void SetSrcRect(const Rect<int>& srcRect);
        void SetSrcRect(const Vec2<int>& startingPoint);
        [[nodiscard]] Rect<int> GetSrcRect() const;

        void SetScale(const Vec2<double> &scale);
        [[nodiscard]] Vec2<double> GetScale() const;

        void SetFlip(bool isFlip);
        [[nodiscard]] bool GetFlip() const;

        void SetPositionParent(SpriteTexture &parent);
        [[nodiscard]] WeakPtr<SpriteTexture> GetPositionParent() const;

        void SetVisible(bool isVisible);
        [[nodiscard]] bool GetVisible() const;

        void SetVisibilityParent(SpriteTexture &parent);
        [[nodiscard]] WeakPtr<SpriteTexture> GetVisibilityParent() const;

        void SetRotationDeg(double deg);
        [[nodiscard]] double GetRotationDeg() const;

        void SetBlend(const GraphBlend &blend);
        [[nodiscard]] GraphBlend GetBlend() const;

        void SetUpdateProcess(const std::function<void(IAppState*)>& process);
        [[nodiscard]] std::function<void(IAppState*)>& GetUpdateProcess();

        void SetRenderingProcess(const std::function<void(IAppState*)>& process);
        [[nodiscard]] std::function<void(IAppState*)>& GetRenderingProcess();

        Vec2<double> GetParentalGlobalPosition();
        bool GetParentalVisibility();

        void CopyVisuallyFrom(SpriteTexture& origin);

        static void RenderAll(IAppState* appState);
        static void UpdateAll(IAppState* appState);
    };
}


#endif //FILL_TILES_SPRITETEXTURE_H
