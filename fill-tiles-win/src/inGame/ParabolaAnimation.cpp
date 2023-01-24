//
// Created by sashi0034 on 2022/07/25.
//

#include "ParabolaAnimation.h"
#include "EffectManager.h"

namespace inGame
{
    ParabolaAnimation::ParabolaAnimation(EffectManager *effectManager, SpriteTexture *target)
        : ActorBase(effectManager->GetChildren()),
          m_EffectManager(effectManager), m_Target(target->GetWeakPtr())
    {}

    void ParabolaAnimation::Update(IAppState *appState)
    {
        const auto&& target = m_Target.GetPtr();
        if (target== nullptr)
        {
            getBelongingPool()->Destroy(this);
            return;
        }

        const double deltaTime = appState ->GetTime().GetDeltaSec();
        m_Speed += m_SpeedAccel * deltaTime;

        m_DeltaMove += m_Speed * deltaTime;
        target->SetPosition(target->GetPosition() + m_NormalizedDirection * m_Speed * deltaTime);

        ActorBase::Update(appState);
    }

    ParabolaAnimation* ParabolaAnimation::AwaitForReturnToStart(CoroTaskYield &yield)
    {
        coroUtil::WaitForTrue(yield, [&](){
            return this->isReturnToStart();
        });
        return this;
    }

    bool ParabolaAnimation::isReturnToStart() const
    {
        return this->m_DeltaMove < 0;
    }

    void ParabolaAnimation::Forget()
    {
        getBelongingPool()->Destroy(this);
    }

    ParabolaAnimation * ParabolaAnimation::Create(EffectManager *effectManager, SpriteTexture *target)
    {
        auto&& product = new ParabolaAnimation(effectManager, target);
        effectManager->GetChildren()->Birth(product);
        return product;
    }

    ParabolaAnimation* ParabolaAnimation::SetSpeedByPeekHeightAndTime(double height, double second)
    {
        // 物理の計算結果
        m_Speed = 2 * height / second;
        m_SpeedAccel = - 2 * height / (second * second);

        return this;
    }


} // inGame