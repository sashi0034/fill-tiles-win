//
// Created by sashi0034 on 2022/08/12.
//

#include "TextureScrapping.h"

namespace inGame::effect
{
    void TextureScrapping::Produce(const TextureScrappingArgs &args)
    {
        args.EffectManagerRef->GetCoroutineManager()->Start([&](auto&& yield){ produceEffectAsync(yield, args);});
    }

    void TextureScrapping::produceEffectAsync(CoroTaskYield &yield, TextureScrappingArgs args)
    {
        yield();

        auto const currPos = args.Pos;
        auto const srcRect = args.SrcRect;
        auto const srcGraph = args.SrcGraph;

        const int stepSize = args.ScrapSize;

        auto&& lua = args.EffectManagerRef->GetRoot()->GetLua()->GetState();
        double focalLength = lua[className]["FocalLength"].get_or(0.0);
        auto const posForAngle = currPos + Vec2<double>(srcRect.Width/2, srcRect.Height * focalLength) - Vec2<double>{stepSize/2.0, stepSize/2.0};

        const double velSize = lua[className]["InitialVelocity"].get_or(0.0);

        const double initialVerticalForce = lua[className]["InitialVerticalForce"].get_or(0.0);

        for (int x=0; x<srcRect.Width; x+=stepSize)
        {
            for (int y=0; y<srcRect.Height; y+= stepSize)
            {
                const Rect<int> stripRect = Rect<int>{x, y, stepSize, stepSize};
                const Vec2<double> stripPos = currPos + Vec2<double>{(double)x , (double)y};
                const double velTheta = std::atan2(stripPos.Y-posForAngle.Y, stripPos.X - posForAngle.X);
                const Vec2<double> normalizedVel{std::cos(velTheta), std::sin(velTheta)};

                args.EffectManagerRef->GetChildren()->Birth(new TextureScrapping(
                        args.EffectManagerRef, srcGraph, stripRect,
                        stripPos, normalizedVel * velSize + Vec2<double>{0, initialVerticalForce}));
            }
        }
    }

    TextureScrapping::TextureScrapping(EffectManager *effectManager, Graph *const srcGraph, const Rect<int> &srcRect,
                                       const Vec2<double> &pos, const Vec2<double> &velocity)
                                       : ActorBase(effectManager->GetChildren()),
                                       m_Manager(effectManager),
                                       m_Pos(pos),
                                       m_Vel(velocity)
    {
        m_Texture.SetGraph(srcGraph);
        m_Texture.SetSrcRect(srcRect);
        effectManager->ApplyParentalPos(m_Texture);
        m_Texture.SetPosition(pos);

        m_Gravity = effectManager->GetRoot()->GetLua()->GetState()[className]["Gravity"].get_or(0.0);
        m_MaxLifetime = effectManager->GetRoot()->GetLua()->GetState()[className]["MaxLifetime"].get_or(0.0);
    }

    void TextureScrapping::Update(IAppState *appState)
    {
        m_Lifetime += appState->GetTime().GetDeltaSec();
        if (m_Lifetime > m_MaxLifetime) {
            getBelongingPool()->Destroy(this);
            return;
        }

        m_Vel = m_Vel + Vec2{0.0, m_Gravity} * appState->GetTime().GetDeltaSec();

        m_Pos = m_Pos + m_Vel * appState->GetTime().GetDeltaSec();
        m_Texture.SetPosition(m_Pos);
    }
} // inGame