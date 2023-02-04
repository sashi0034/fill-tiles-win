//
// Created by sashi0034 on 2022/09/20.
//

#include "StageClearEvent.h"
#include "ZIndex.h"

namespace inGame
{
    GameRoot *StageClearEventArgs::GetRoot() const
    {
        return SceneRef->GetRoot();
    }

    TextureAnimator *StageClearEventArgs::GetAnimator() const
    {
        return SceneRef->GetEffectManager()->GetAnimator();
    }

    CoroutineManager *StageClearEventArgs::GetCoroutineManager() const
    {
        return SceneRef->GetEffectManager()->GetCoroutineManager();
    }

    constexpr int zIndexValue = 100;

    void StageClearEvent::Start(const StageClearEventArgs &args)
    {
        args.GetCoroutineManager()->Start([&args](auto&& yield){ StageClearEvent::startEvent(yield, args);});
    }

    void StageClearEvent::startEvent(CoroTaskYield &yield, StageClearEventArgs args)
    {
        auto eventInScope = args.SceneRef->GetFieldEventManager()->UseEvent();
        eventInScope.StartFromHere();
        yield();

        constexpr double duration = 0.5;

        // CLEARラベルを表示
        SpriteTexture labelClear = SpriteTexture::Create();
        setupClearLabel(args, labelClear, duration);

        coroUtil::WaitForTime(yield, duration);

        // テキストの背景を表示
        unique_ptr<NinePatchImage> textBackground = createTextBackground(args, duration);
        (void)textBackground;

        coroUtil::WaitForTime(yield, duration);

        // テキスト表示
        auto textPassage = createText(args);
        (void)textPassage;

        coroUtil::WaitForTime(yield, duration);

        while (true)
        {
            yield();
        }
    }

    const Vec2<double> bgSize = Vec2<double>{160.0, 48.0};
    constexpr double bgCenterY = 64;

    void StageClearEvent::setupClearLabel(const StageClearEventArgs &args, SpriteTexture &labelClear, double animationDuration)
    {
        auto const labelClearImage = args.GetRoot()->RscImage->clear_label.get();

        labelClear.SetGraph(labelClearImage);
        labelClear.SetSrcRect(Rect<int>{Vec2{0, 0}, labelClearImage->GetSize()});
        labelClear.SetRenderingProcess(renderingProcess::WrapRenderSpriteDotByDot(&labelClear));
        labelClear.SetPositionParent(args.GetRoot()->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Middle));
        labelClear.SetPosition(Vec2<double>{-labelClearImage->GetSize().X / 2.0, -labelClearImage->GetSize().Y / 1.0} /
                               pixel::PixelPerUnit);
        labelClear.SetScale(Vec2{0.0, 1.0});
        ZIndexUi(&labelClear).SetIndex(zIndexValue).ApplyZ();

        args.GetAnimator()->TargetTo(labelClear)->AnimScale(Vec2{1.0, 1.0}, animationDuration)->SetEase(EAnimEase::OutBack);
    }

    unique_ptr<NinePatchImage>
    StageClearEvent::createTextBackground(const StageClearEventArgs &args, double animationDuration)
    {
        const auto sideRatio = Vec2{0.2, 0.2};
        auto textBackground = std::make_unique<NinePatchImage>(
                args.GetRoot()->GetAppState(),
                args.GetRoot()->RscImage->ui_black_window.get(),
                Vec2{0.0, 0.0}, Vec2<double>{bgSize.X, bgSize.Y}, sideRatio);
        textBackground->GetSprite().SetPositionParent(args.GetRoot()->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Middle));

        util::SetTextureByCenter(textBackground->GetSprite(), Vec2<double>(0, bgCenterY), pixel::DotByDot);
        ZIndexUi(&textBackground->GetSprite()).SetIndex(zIndexValue).ApplyZ();

        textBackground->GetSprite().SetScale(Vec2{0.0, 1.0});
        args.GetAnimator()->TargetTo(textBackground->GetSprite())->AnimScale(Vec2{1.0, 1.0}, animationDuration)->SetEase(EAnimEase::OutBack);

        return textBackground;
    }

    unique_ptr<TextPassage> StageClearEvent::createText(const StageClearEventArgs &args)
    {
        auto text = std::make_unique<TextPassage>(
                args.GetRoot()->GetAppState(),
                args.GetRoot()->RscFont->PixelMPlus24Px.get(),
                Rgba(255, 255, 255), Rgba(16, 16, 16));

        constexpr double padX = 16;
        text->SetPos(Vec2<double>(-bgSize.X/2.0 + padX, bgCenterY));
        text->SetAlignment(ETextHorizontalAlign::Left, ETextVerticalAlign::Center);
        text->SetPositionParent(args.GetRoot()->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Middle));
        text->SetZIndex(zIndexValue + 1);
        text->UpdateTextAndView("ステップ数:  0<br>クリア時間:  01:23");

        return text;
    }
} // inGame
