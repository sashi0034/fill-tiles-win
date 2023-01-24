//
// Created by sashi0034 on 2022/06/16.
//

#ifndef FILL_TILES_SCROLLMANAGER_H
#define FILL_TILES_SCROLLMANAGER_H

#include "ActorBase.h"

namespace inGame
{
    class IMainScene;

    class ScrollManager final
    {
    public:
        explicit ScrollManager(IMainScene* parentScene);
        void RegisterSprite(SpriteTexture &target);

        Vec2<double> GetScroll();
        void SetScroll(const Vec2<double> &amount);
        SpriteTexture* GetSprite();
        Vec2<double> CalcScrollToCenter(const Vec2<double>& targetPos);
        Vec2<double> MakePosInFieldRange(const Vec2<double> &pos);
    private:
        SpriteTexture m_ViewModel = SpriteTexture::Create(nullptr);
        IMainScene* m_ParentScene;
    };
}


#endif //FILL_TILES_SCROLLMANAGER_H
