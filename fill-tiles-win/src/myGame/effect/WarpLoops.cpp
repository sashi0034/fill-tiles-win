//
// Created by sashi0034 on 2022/08/21.
//

#include "WarpLoops.h"
#include "../ZIndex.h"
#include <functional>

namespace myGame::effect
{
    CoroTask WarpLoops::produceEffectAsync(CoroTaskYield &yield, EffectManager *manager, const Vec2<double> pos)
    {
        yield();

        auto const app = manager->GetRoot()->GetAppState();
        auto const lua = manager->GetRoot()->GetLua();
        const double duration = lua->GetState()[className]["ProducingDuration"];

        while (true)
        {
            coroUtil::WaitForTime(yield, app->GetTime(), duration);
            manager->GetChildren()->Birth(new WarpLoops(manager, pos - Vec2<double>(cellSize/2.0, cellSize/2.0)));
        }
    }

    const auto exMargin = VecOne<double>() * 1;

    WarpLoops::WarpLoops(EffectManager *effectManager, const Vec2<double> &pos) :
        ActorBase(effectManager->GetChildren()), m_Manager(effectManager),
        initialPos(pos - exMargin)
    {
        effectManager->ApplyParentalPos(m_Texture);
        m_Texture.SetGraphThenSrcGraph(effectManager->GetRoot()->RscImage->warp_circle.get());
        m_Texture.SetBlend(GraphBlend(0));

        m_Texture.SetPosition(initialPos);
        m_Texture.SetScale(VecOne<double>() * pixel::PixelPerMat + exMargin * 2);

        m_Texture.SetRenderingProcess(renderingProcess::WrapRenderSprScaleAsDestAlignToUnit(&m_Texture));
        ZIndexEffect(&m_Texture).SetIndex(1).ApplyZ();
    }

    void WarpLoops::Produce(EffectManager *effectManager, const Vec2<double> &pos)
    {
        effectManager->GetCoroutineManager()->Start(
                new CoroTaskCall([&](auto&& yield){ produceEffectAsync(yield, effectManager, pos);}));
    }

    void WarpLoops::Update(IAppState *appState)
    {
        m_Lifetime += appState->GetTime().GetDeltaSec();

        auto const lua = m_Manager->GetRoot()->GetLua();

        lua->GetState()[className]["Update"](
                m_Lifetime,
                std::function([&](double alpha){m_Texture.SetBlend(GraphBlend(alpha));}),
                std::function([&](double x, double y){m_Texture.SetPosition(initialPos + Vec2{x, y});}),
                [&](){getBelongingPool()->Destroy(this);}
        );
    }
} // myGame
