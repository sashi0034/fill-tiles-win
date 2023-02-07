//
// Created by sashi0034 on 2022/07/05.
//

#include "Smoke.h"
#include "../ZIndex.h"

namespace myGame::effect
{

    Smoke::Smoke(EffectManager *effectManager, const Vec2<double> &pos, const Vec2<double> &velocity,
                 double rotationDeg)
    : ActorBase(effectManager->GetChildren()), m_Vel(velocity), m_Manager(effectManager)
    {
        effectManager->ApplyParentalPos(m_Texture);
        m_Texture.SetGraph(effectManager->GetRoot()->RscImage->smoke_48x32.get());
        //m_Target.SetRenderingProcess(std::bind(renderingProcess::RenderSpriteTwoDots, std::placeholders::_1, &m_Target));
        m_Texture.SetSrcRect(Rect<int>{0, 0, 48, 32});
        m_Texture.SetRotationDeg(rotationDeg);
        m_Texture.SetBlend(GraphBlend(0));
        ZIndexEffect(&m_Texture).SetIndex(1).ApplyZ();
        util::SetTextureByCenter(m_Texture, pos);

//        m_Target.SetScale(Vec2{0.0, 0.0});
//        effectManager->GetAnimator()->TargetTo(m_Target.GetWeakPtr())
//            ->AnimScale(Vec2{1.0, 1.0}, 1.0)->SetEase(EAnimEase::OutBack)
//            ->Then()
//            ->AnimScale(Vec2{.0, .0}, 1.0)->SetEase(EAnimEase::Linear);
    }

    void Smoke::Produce(EffectManager *effectManager, const Vec2<double> &pos)
    {

        effectManager->GetCoroutineManager()->Start(
                new CoroTaskCall(std::bind(produceWithRotating, std::placeholders::_1, effectManager, pos)));
    }

    CoroTask Smoke::produceWithRotating(CoroTaskYield &yield, EffectManager *manager, const Vec2<double> &pos)
    {
        constexpr int numGenerate = 6;
        constexpr int numCircuit = 2;
        constexpr double duration = 0.05;

        for (int i=0; i<numGenerate * numCircuit + 1; ++i)
        {
            const int deg = i * ((360.0-360.0/(numGenerate*numCircuit)) / numGenerate);
            const double rad = deg / 180.0 * M_PI;
            constexpr double radius = 4;
            constexpr double velSize = 20;
            const Vec2<double> deltaPos = Vec2{std::cos(rad), std::sin(rad)} * radius;
            const Vec2<double> vel = Vec2{std::cos(rad), std::sin(rad)} * velSize;
            manager->GetChildren()->Birth(new Smoke(manager, pos + deltaPos, vel, getCorrectedDeg(deg)));

            coroUtil::WaitForTime(yield, duration);
        }
    }

    int Smoke::getCorrectedDeg(const int deg)
    { return 90 + deg; }

    void Smoke::Update(IAppState *appState)
    {
        constexpr double scaleSpeed = 5;
        const double scale = 0.7 - 0.3 * std::cos(m_LifeTime * scaleSpeed * M_PI);

        m_Texture.SetScale(Vec2{scale, scale});
        m_Texture.SetPosition(m_Texture.GetPosition() + m_Vel * appState->GetTime().GetDeltaSec());

        if (passLifeTime(appState)) return;
    }

    bool Smoke::passLifeTime(const IAppState *appState)
    {
        m_LifeTime += appState->GetTime().GetDeltaSec();
        constexpr double lifeTime = 3.0;
        constexpr double fadingTime = 0.6;
        constexpr double fadingStartTime = lifeTime - fadingTime;

        // フェードアウト処理
        if (m_LifeTime > fadingStartTime)
        {
            double fadingRate = 1 - (m_LifeTime - fadingStartTime) / fadingTime;
            int alpha = Range<int>(0, 255).MakeInRange(initialAlpha * fadingRate);
            m_Texture.SetBlend(GraphBlend(alpha));
        }
        else
        {
            m_Texture.SetBlend(GraphBlend(initialAlpha));
        }

        // 寿命
        if (m_LifeTime > lifeTime)
        {
            m_Manager->GetChildren()->Destroy(this);
            return true;
        }
        return false;
    }
}