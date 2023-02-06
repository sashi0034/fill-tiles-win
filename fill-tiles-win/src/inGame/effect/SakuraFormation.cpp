//
// Created by sashi0034 on 2022/08/11.
//

#include "SakuraFormation.h"

namespace inGame::effect
{
    void SakuraFormation::Update(IAppState *appState)
    {
        m_Lifetime += appState->GetTime().GetDeltaSec();

        auto const lua = m_Manager->GetRoot()->GetLua();

        lua->GetState()[className]["Update"](
                m_Lifetime,
                [&](double alpha){m_Texture.SetBlend(GraphBlend(alpha));},
                [&](int frame){m_Texture.SetSrcRect(Rect{frame*cellSize, 0, cellSize, cellSize});},
                [&](double scaleX, double scaleY){m_Texture.SetScale(Vec2{scaleX, scaleY});},
                std::function([&](double rotationDeg)->void{m_Texture.SetRotationDeg(rotationDeg);}),
                [&](){getBelongingPool()->Destroy(this);}
        );
    }

    SakuraFormation::SakuraFormation(EffectManager *effectManager, const Vec2<double> &pos, int kind)
            : ActorBase(effectManager->GetChildren()), m_Manager(effectManager)
    {
        effectManager->ApplyParentalPos(m_Texture);
        m_Texture.SetGraph(effectManager->GetRoot()->RscImage->sakura_32x32.get());
        m_Texture.SetSrcRect(Rect<int>{kind * cellSize, 0, cellSize, cellSize});
        m_Texture.SetBlend(GraphBlend(0));
        util::SetTextureByCenter(m_Texture, pos);
    }

    void SakuraFormation::Produce(EffectManager *effectManager, const Vec2<double> &pos)
    {
        effectManager->GetCoroutineManager()->Start(
                new CoroTaskCall([&](auto&& yield){ produceEffectAsync(yield, effectManager, pos);}));
    }

    CoroTask SakuraFormation::produceEffectAsync(CoroTaskYield &yield, EffectManager *manager, const Vec2<double> pos)
    {
        yield();

        auto const lua = manager->GetRoot()->GetLua();

        lua->RunCoroutine(
                yield,
                (sol::function)lua->GetState()[className]["ProduceEffects"],
                [&](double x, double y, int kind)->void {manager->GetChildren()->Birth(new SakuraFormation(manager, pos + Vec2{x, y}, kind));}
        );

    }
} // inGame
