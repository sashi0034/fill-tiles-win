//
// Created by sashi0034 on 2022/06/16.
//

#include "ScrollManager.h"
#include "MainScene.h"

namespace inGame
{
    ScrollManager::ScrollManager(MainScene *parentScene)
            : m_ParentScene(parentScene)
    {}

    void ScrollManager::RegisterSprite(SpriteTexture &target)
    {
        target.SetPositionParent(m_ViewModel);
    }

    Vec2<double> ScrollManager::GetScroll()
    {
        return m_ViewModel.GetPosition();
    }

    void ScrollManager::SetScroll(const Vec2<double> &amount)
    {
        m_ViewModel.SetPosition(amount);
    }

    SpriteTexture* ScrollManager::GetSprite()
    {
        return &m_ViewModel;
    }

    Vec2<double> ScrollManager::CalcScrollToCenter(const Vec2<double>& targetPos)
    {
        return targetPos * -1 +
            (m_ParentScene->GetRoot()->GetAppState()->GetScreenSize() /
            2).CastTo<double>();
    }

    Vec2<double> ScrollManager::MakePosInFieldRange(const Vec2<double> &pos)
    {
        const auto field = m_ParentScene->GetFieldManager();
        const auto fieldSize = field->GetTileMap()->GetSizeByPixel();
        auto screenSize = m_ParentScene->GetRoot()->GetAppState()->GetScreenSize();

        auto result = Vec2{
            Range<double>((fieldSize.X - screenSize.X)*-1, 0).MakeInRange(pos.X),
            Range<double>((fieldSize.Y - screenSize.Y)*-1, 0).MakeInRange(pos.Y)};

        return result;
    }
}
