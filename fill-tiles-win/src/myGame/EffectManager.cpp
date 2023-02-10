//
// Created by sashi0034 on 2022/07/06.
//

#include "EffectManager.h"
#include "GameRoot.h"

namespace myGame
{
    EffectManager::EffectManager(IChildrenPool<ActorBase> *belongingPool, SpriteTexture *parentalPos, GameRoot *root) :
        ActorBase(belongingPool),
        m_ParentalPos(parentalPos),
        m_Root(root)
    {}

    void EffectManager::Update(IAppState *appState)
    {
        m_Children.ProcessEach([&](ActorBase& child){child.Update(appState);});
        m_CoroutineManager.UpdateEach();
        m_Animator.Update(appState->GetTime().GetDeltaSec());
    }

    TextureAnimator *EffectManager::GetAnimator()
    {
        return &m_Animator;
    }

    CoroutineManager *EffectManager::GetCoroutineManager()
    {
        return &m_CoroutineManager;
    }

    IChildrenPool<ActorBase> * EffectManager::GetChildren()
    {
        return &m_Children;
    }

    void EffectManager::ApplyParentalPos(SpriteTexture &target)
    {
        if (m_ParentalPos == nullptr) return;
        target.SetPositionParent(*m_ParentalPos);
    }

    GameRoot *EffectManager::GetRoot() const
    {
        return m_Root;
    }

    Vec2<double> EffectManager::GetParentalPos() const
    {
        return m_ParentalPos->GetPosition();
    }
} // myGame
