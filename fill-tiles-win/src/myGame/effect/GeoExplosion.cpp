//
// Created by sashi0034 on 2022/08/04.
//

#include "GeoExplosion.h"

namespace myGame::effect
{

    void GeoExplosion::Update(IAppState *appState)
    {
        m_Lifetime += appState->GetTime().GetDeltaSec();

        auto const lua = m_Manager->GetRoot()->GetLua();

        lua->GetState()["GeoExplosion"]["Update"](
                m_Lifetime,
                [&](double alpha){m_Texture.SetBlend(GraphBlend(alpha));},
                [&](int frame){m_Texture.SetSrcRect(Rect{frame*cellSize, 0, cellSize, cellSize});},
                [&](double scaleX, double scaleY){m_Texture.SetScale(Vec2{scaleX, scaleY});},
                [&](){getBelongingPool()->Destroy(this);}
        );
    }

    GeoExplosion::GeoExplosion(EffectManager *effectManager, const Vec2<double> &pos)
            : ActorBase(effectManager->GetChildren()), m_Manager(effectManager)
    {
        effectManager->ApplyParentalPos(m_Texture);
        m_Texture.SetGraph(effectManager->GetRoot()->RscImage->geo_explode_24x24.get());
        m_Texture.SetSrcRect(Rect<int>{0, 0, cellSize, cellSize});
        m_Texture.SetBlend(GraphBlend(0));
        util::SetTextureByCenter(m_Texture, pos);
    }

    void GeoExplosion::Produce(EffectManager *effectManager, const Vec2<double> &pos)
    {
        effectManager->GetCoroutineManager()->Start(
                new CoroTaskCall([&](auto&& yield){ produceEffectAsync(yield, effectManager, pos);}));
    }

    CoroTask GeoExplosion::produceEffectAsync(CoroTaskYield &yield, EffectManager *manager, const Vec2<double> pos)
    {
        yield();

        auto const lua = manager->GetRoot()->GetLua();

        lua->RunCoroutine(
                yield,
                (sol::function)lua->GetState()["GeoExplosion"]["ProduceEffects"],
                [&](double x, double y)->void {manager->GetChildren()->Birth(new GeoExplosion(manager, pos + Vec2{x, y}));}
        );

    }


} // myGame