//
// Created by sashi0034 on 2022/07/01.
//

#include "TalkingBalloon.h"
#include "MainScene.h"
#include "ZIndex.h"
#include "LuaEngine.h"

namespace myGame{

    TalkingBalloon::TalkingBalloon(MainScene *scene, const std::string &text, const Vec2<double> &pos) :
          ActorBase(scene->GetEffectManager()->GetChildren()),
          m_Scene(scene),
          m_Text(text),
          m_TextPassage(scene->GetRoot()->GetAppState(),
                        scene->GetRoot()->RscFont->KHDotAkihabara32px.get(), Rgba(255, 255, 255), Rgba(16, 16, 16, 144))
    {
        m_SpriteRoot.SetPosition(pos);
        scene->GetScrollManager()->RegisterSprite(m_SpriteRoot);
        initBackground(scene);
        initTextPassage();
        scene->GetEffectManager()->GetCoroutineManager()->Start(new CoroTaskCall(
                [&](auto&& yield){this->startAppear(yield); }
                ));
    }

    void TalkingBalloon::initBackground(MainScene *scene)
    {
        const auto sideRatio = Vec2{0.1, 0.1};

        m_Background = std::make_unique<NinePatchImage>(
                scene->GetRoot()->GetAppState(),
                scene->GetRoot()->RscImage->ui_rounnd_rect_blue.get(),
                Vec2{0.0, 0.0}, Vec2<double>{bgSize.X, bgSize.Y}, sideRatio);
        constexpr int bgAlpha = 224;
        m_Background->GetSprite().SetBlend(GraphBlend(bgAlpha));
        m_Background->GetSprite().SetPositionParent(m_SpriteRoot);
        m_Background->GetSprite().SetScale(Vec2{0.0, 1.0});
    }


    void TalkingBalloon::initTextPassage()
    {
        m_TextPassage.SetPos(bgSize/2.0);
        m_TextPassage.SetAlignment(ETextHorizontalAlign::Center, ETextVerticalAlign::Center);
        m_TextPassage.SetZIndex(1);
        m_TextPassage.SetPositionParent(m_Background->GetSprite());
        m_TextPassage.UpdateTextAndView("");
    }


    CoroTask TalkingBalloon::startAppear(CoroTaskYield &yield)
    {
        yield();
        constexpr double duration = 0.5;

        auto&& animator = m_Scene->GetEffectManager()->GetAnimator();
        auto scaling = animator->TargetTo(m_Background->GetSprite())
                ->AnimScale(Vec2{1.0, 1.0}, duration)->SetEase(EAnimEase::OutBack)->ToWeakPtr();
        coroUtil::WaitForExpire(yield, scaling);

        sol::table multiByteCharFunc = m_Scene->GetRoot()->GetLua()->GetState()["MultiByteChar"];
        int textLength = multiByteCharFunc["Length"](m_Text);

        bool isInTag = false;
        std::string currStr{};

        for (int i=1; i<=textLength; ++i)
        {
            std::string nextStr = multiByteCharFunc["GetAt"](m_Text, i);

            if (!isInTag && nextStr=="<") isInTag = true;
            if (isInTag && nextStr==">") isInTag = false;

            currStr += nextStr;
            m_TextPassage.UpdateTextAndView(currStr);

            if (isInTag) continue;

            coroUtil::WaitForTime(yield, m_Text[i]!='>' ? duration/10.0 : duration);
        }

        coroUtil::WaitForTime(yield, 2.5);

        //performAnimGuruGuruChar(yield, duration / 4.0, currStr, 1);
        //performAnimGuruGuruChar(yield, duration / 2.0, currStr, 1);

        //coroUtil::WaitForTime(yield, duration);

        auto&& animFade = animator->TargetVirtual()
            ->AnimValue(1, 0, [this](double value) {
                    const auto scale = VecDouble2{ value, 1 };
                    m_TextPassage.SetScale(scale);
                    m_TextPassage.UpdateView();
                    m_Background->GetSprite().SetScale(scale);
                }, duration)->SetEase(EAnimEase::InBack)
            ->ToWeakPtr();

        coroUtil::WaitForExpire(yield, animFade);

        getBelongingPool()->Destroy(this);
    }

    void
    TalkingBalloon::performAnimGuruGuruChar(CoroTaskYield &yield, const double duration, std::string &currStr, int numGruGru)
    {
        const std::string tempSpace = "  ";
        currStr += tempSpace;

        for (int count=0; count < 4 * numGruGru; count++)
        {
            char animChar = ' ';
            switch (count % 4)
            {
                case 0:
                    animChar = '|'; break;
                case 1:
                    animChar = '/'; break;
                case 2:
                    animChar = '-'; break;
                case 3:
                    animChar = '\\'; break;
            }
            currStr[currStr.length()-1] = animChar;

            m_TextPassage.UpdateTextAndView(currStr);
            coroUtil::WaitForTime(yield, duration);
        }

        for (int i = 0; i < int(tempSpace.size()); ++i)
        {
            currStr.pop_back();
        }

        m_TextPassage.UpdateTextAndView(currStr);
    }


    TalkingBalloon* TalkingBalloon::Create(MainScene *scene, const std::string &text, const MatPos &pos)
    {
        auto effectManager = scene->GetEffectManager()->GetChildren();
        auto product = new TalkingBalloon(scene, text, pos.ToPixelPos() + FieldManager::MatPixelSize.CastTo<double>() / 2.0 +
                Vec2<double>(0, -bgSize.Y/2.0 - FieldManager::PixelPerMat));
        effectManager->Birth(product);
        return product;
    }

}
