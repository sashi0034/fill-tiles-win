//
// Created by sashi0034 on 2022/08/03.
//

#include "BurningFire.h"
namespace myGame::effect
{

    void BurningFire::Produce(EffectManager *effectManager, const Vec2<double> &pos)
    {
        effectManager->GetChildren()->Birth(new BurningFire(effectManager, pos));
    }


    CoroTask BurningFire::produceEffectsAsync()
    {}


    void BurningFire::Update(IAppState *appState)
    {
        m_Lifetime += appState->GetTime().GetDeltaSec();

        auto const lua = m_Manager->GetRoot()->GetLua();

        lua->GetState()["BurningFire"]["Update"](
                m_Lifetime,
                [&](double alpha){m_Texture.SetBlend(GraphBlend(alpha));},
                [&](int frame){m_Texture.SetSrcRect(Rect{frame*cellSize, 0, cellSize, cellSize});},
                [&](double scaleX, double scaleY){m_Texture.SetScale(Vec2{scaleX, scaleY});},
                [&](){getBelongingPool()->Destroy(this);}
                );
    }

    BurningFire::BurningFire(EffectManager *effectManager, const Vec2<double> &pos)
            : ActorBase(effectManager->GetChildren()), m_Manager(effectManager)
    {
        effectManager->ApplyParentalPos(m_Texture);
        m_Texture.SetGraph(effectManager->GetRoot()->RscImage->burning_192x192.get());
        m_Texture.SetSrcRect(Rect<int>{0, 0, cellSize, cellSize});
        m_Texture.SetBlend(GraphBlend(0));
        util::SetTextureByCenter(m_Texture, pos);
    }

}