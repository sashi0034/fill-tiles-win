//
// Created by sashi0034 on 2022/05/13.
//

#include "SpriteTexture.h"

#include <utility>
#include <cassert>

namespace gameEngine
{
    std::vector<WeakPtr<SpriteTexture>> SpriteTexture::spriteTexturePool = {};

    SpriteTexture::SpriteTexture(Graph *graph, const Rect<int> &srcRect)
    {
        m_Graph = graph;
        m_SrcRect = srcRect;
        m_UpdateProcess = [](IAppState*){};
        m_RenderingProcess = [this](IAppState* appState){
            renderingProcess::RenderSpriteAlignToUnit(appState, this);
        };
    }

    SpriteTexture SpriteTexture::Create()
    {
        return Create(nullptr);
    }

    SpriteTexture SpriteTexture::Create(Graph *graph)
    {
        auto srcRect = Rect<int>{0, 0, 0, 0};

        return Create(graph, srcRect);
    }

    SpriteTexture SpriteTexture::Create(Graph *graph, const Rect<int> &srcRect)
    {
        auto product = SpriteTexture(graph, srcRect);

        spriteTexturePool.push_back(product.GetWeakPtr());

        return product;
    }

    void SpriteTexture::SetPosition(const Vec2<double> &pos)
    {
        m_Position = pos;
    }

    Vec2<double> SpriteTexture::GetPosition() const
    {
        return m_Position;
    }

    void SpriteTexture::SetZ(double z)
    {
        m_Z = z;
    }

    double SpriteTexture::GetZ() const
    {
        return m_Z;
    }

    void SpriteTexture::SetGraph(Graph *graph)
    {
        m_Graph = graph;
    }

    Graph *SpriteTexture::GetGraph() const
    {
        return m_Graph;
    }

    void SpriteTexture::SetSrcRect(const Rect<int> &srcRect)
    {
        m_SrcRect = srcRect;
    }

    void SpriteTexture::SetSrcRect(const Vec2<int> &startingPoint)
    {
        m_SrcRect.X = startingPoint.X;
        m_SrcRect.Y = startingPoint.Y;
    }

    Rect<int> SpriteTexture::GetSrcRect() const
    {
        return m_SrcRect;
    }

    void SpriteTexture::SetScale(const Vec2<double> &scale)
    {
        m_Scale = scale;
    }

    Vec2<double> SpriteTexture::GetScale() const
    {
        return m_Scale;
    }

    void SpriteTexture::SetFlip(bool isFlip)
    {
        m_IsFlip = isFlip;
    }

    bool SpriteTexture::GetFlip() const
    {
        return m_IsFlip;
    }

    void SpriteTexture::SetPositionParent(SpriteTexture &parent)
    {
        m_PositionParent = parent.GetWeakPtr();
    }

    WeakPtr<SpriteTexture> SpriteTexture::GetPositionParent() const
    {
        return m_PositionParent;
    }

    void SpriteTexture::SetRotationDeg(double deg)
    {
        m_RotationDeg = deg;
    }

    double SpriteTexture::GetRotationDeg() const
    {
        return m_RotationDeg;
    }

    void SpriteTexture::SetBlend(const GraphBlend &blend)
    {
        m_Blend = blend;
    }

    GraphBlend SpriteTexture::GetBlend() const
    {
        return m_Blend;
    }

    void SpriteTexture::SetRenderingProcess(const std::function<void(IAppState*)>& process)
    {
        m_RenderingProcess = process;
    }

    Vec2<double> SpriteTexture::GetParentalGlobalPosition()
    {
        if (auto parent = m_PositionParent.GetPtr())
        {
            auto parentPosition = parent->GetParentalGlobalPosition();
            return parent->m_Position + parentPosition;
        }
        else
        {
            return Vec2<double>{0,0};
        }
    }

    bool SpriteTexture::GetParentalVisibility()
    {
        if (auto parent = m_PositionParent.GetPtr())
        {
            bool parentVisibility = parent->GetParentalVisibility();
            return parent->m_IsVisible && parentVisibility;
        }
        else
        {
            return true;
        }
    }



    void SpriteTexture::UpdateAll(IAppState *appState)
    {
        int size = spriteTexturePool.size();
        std::vector<int> garbageIndexes{};

        for (int i = 0; i < size; ++i)
            if (auto updatingSpr = spriteTexturePool[i].GetPtr())
                updatingSpr->m_UpdateProcess(appState);
            else
                garbageIndexes.push_back(i);

        collectGarbageInSpriteTexturePool(garbageIndexes);
    }

    void SpriteTexture::RenderAll(IAppState*appState)
    {
        std::stable_sort(spriteTexturePool.begin(), spriteTexturePool.end(), [](const WeakPtr<SpriteTexture> &left, const WeakPtr<SpriteTexture> &right) -> bool {
            auto leftShared =left.GetPtr();
            auto rightShared = right.GetPtr();
            return (leftShared ? leftShared->GetZ() : 0.0) > (rightShared ? rightShared->GetZ() : 0.0); });
        std::vector<int> garbageIndexes{};
        int size = spriteTexturePool.size();

        for (int i=0; i < size ; ++i)
            if (auto renderingSpr = spriteTexturePool[i].GetPtr())
            {
                if (renderingSpr == nullptr) continue;

                renderingSpr->m_RenderingProcess(appState);
            }
            else
            {
                garbageIndexes.push_back(i);
            }

        collectGarbageInSpriteTexturePool(garbageIndexes);
    }

    SpriteTexture::SpriteTexture()
    {
        assert(false);
    }

    void SpriteTexture::collectGarbageInSpriteTexturePool(std::vector<int> &garbageIndexes)
    {
        for (int i=garbageIndexes.size()-1; i>=0; --i)
        {
            int index = garbageIndexes[i];
            spriteTexturePool.erase(spriteTexturePool.begin() + index);
        }
    }

    void SpriteTexture::SetVisibilityParent(SpriteTexture &parent)
    {
        m_VisibilityParent = parent.GetWeakPtr();
    }

    WeakPtr<SpriteTexture> SpriteTexture::GetVisibilityParent() const
    {
        return m_VisibilityParent;
    }

    void SpriteTexture::SetVisible(bool isVisible)
    {
        m_IsVisible=isVisible;
    }

    bool SpriteTexture::GetVisible() const
    {
        return m_IsVisible;
    }

    void SpriteTexture::SetUpdateProcess(const std::function<void(IAppState *)> &process)
    {
        m_UpdateProcess = process;
    }

    void SpriteTexture::CopyVisuallyFrom(SpriteTexture& origin)
    {
        auto&& clone = *this;
        
        clone.SetPosition(origin.GetPosition());
        clone.SetZ(origin.GetZ());
        if (auto ptr = origin.GetPositionParent().GetPtr()) clone.SetPositionParent(*ptr);
        clone.SetSrcRect(origin.GetSrcRect());
        clone.SetGraph(origin.GetGraph());
        clone.SetSrcRect(origin.GetSrcRect());
        clone.SetFlip(origin.GetFlip());
        clone.SetRotationDeg(origin.GetRotationDeg());
        clone.SetScale(origin.GetScale());
        clone.SetBlend(origin.GetBlend());
        clone.SetVisible(origin.GetVisible());
        if (auto ptr = origin.GetVisibilityParent().GetPtr()) clone.SetVisibilityParent(*ptr);
    }



}