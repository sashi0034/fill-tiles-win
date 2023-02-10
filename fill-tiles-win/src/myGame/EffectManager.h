//
// Created by sashi0034 on 2022/07/06.
//

#ifndef FILL_TILES_EFFECTMANAGER_H
#define FILL_TILES_EFFECTMANAGER_H

#include "ActorBase.h"
#include "GameRoot.h"

namespace myGame
{
    class MainScene;

    class EffectManager : public ActorBase
    {
    public:
        EffectManager(IChildrenPool<ActorBase> *belongingPool, SpriteTexture *parentalPos, GameRoot *roo);
        void Update(IAppState* appState) override;
        TextureAnimator* GetAnimator();
        CoroutineManager* GetCoroutineManager();
        IChildrenPool<ActorBase> * GetChildren();
        void ApplyParentalPos(SpriteTexture &target);
        Vec2<double> GetParentalPos() const;
        GameRoot* GetRoot() const;
        MainScene* GetScene();
    private:
        ChildrenPool<ActorBase> m_Children{};
        SpriteTexture* m_ParentalPos;
        GameRoot* m_Root;
        TextureAnimator m_Animator{};
        CoroutineManager m_CoroutineManager{};
    };

} // myGame

#endif //FILL_TILES_EFFECTMANAGER_H
