#include "stdafx.h"
#include "RetirementHelp.h"
#include "ZIndex.h"

namespace myGame {
    RetirementHelp::RetirementHelp(MainScene* scene, const MainSceneResetInfo& resetInfo) :
        ActorBase(scene->GetChildren()),
        m_Scene(scene),
        m_TextPassage(initTextPassage(scene->GetRoot()))
    {
        if (resetInfo.IsFirstTry() == false) return;

        // 初回の表示
        m_TextPassage.SetPositionParent(scene->GetRoot()->GetAnchor()->GetOf(ENineAnchorX::Left, ENineAnchorY::Bottom));
        m_TextPassage.SetPos(VecDouble2{ 4, -4 });
        m_TextPassage.SetAlignment(ETextHorizontalAlign::Left, ETextVerticalAlign::Bottom);
        m_TextPassage.SetZIndex(0);
        m_TextPassage.UpdateTextAndView("Backspace長押しでステージ選択画面に戻ります");

        // 左から出てきてフェードする
        m_SelfAnim = getAnimator()->TargetVirtual()
            ->AnimValue(-m_TextPassage.GetMaxWidth(), 4, [this](double value) {
                m_TextPassage.SetPos(VecDouble2{ value, -4 });
                m_TextPassage.UpdateView();
            }, 1.0)->SetEase(EAnimEase::OutBack)
            ->Then()
            ->DelayVirtual(util::FuncEmpty(), 3.0)
            ->Then()
            ->AnimValue(1, 0, [this](double value) {
                m_TextPassage.SetScale(VecDouble2{ 1, value });
                m_TextPassage.UpdateView();
            }, 0.5)->SetEase(EAnimEase::InBack)
            ->ToWeakPtr();
    }

    constexpr int iconLength = 32;

    void RetirementHelp::Update(IAppState* app)
    {
        if (player::input::IsPushingBack(app->GetKeyboardState()) == false)
        {
            // 押すのをやめた
            if (m_PushingBackTime > 0) hideOnStopPushButton();

            m_PushingBackTime = 0;
            return;
        }

        // Backspace押されてる
        if (m_PushingBackTime == 0)
        {
            setupOnPushBackButton();
        }

        constexpr double maxPushingBackTime = 1.5;
        m_PushingBackTime += app->GetTime().GetDeltaSec();

        const double progressRate = std::min(1.0, m_PushingBackTime / maxPushingBackTime);
        const int progressIconWidth = progressRate * iconLength;
        m_IconFront.SetSrcRect(RectInt{ iconLength, 0, progressIconWidth, iconLength });

        if (m_PushingBackTime > maxPushingBackTime) {
            m_Scene->FinishScene();
        }
    }

    void RetirementHelp::hideOnStopPushButton()
    {
        getAnimator()->Destroy(m_SelfAnim);
        m_IconBack.SetVisible(false);
        m_IconFront.SetVisible(false);
        m_TextPassage.HideImmediately();
    }

    void RetirementHelp::setupOnPushBackButton()
    {
        getAnimator()->Destroy(m_SelfAnim);

        auto&& root = m_Scene->GetRoot();
        auto&& image = root->RscImage->icon_back_32x32.get();
        //const auto iconPos = VecDouble2{ 4, -16 } - (VecUp<double>() * image->GetSize().Y);
        const double iconPosY = -16 - image->GetSize().Y;
        auto&& anchor = root->GetAnchor()->GetOf(ENineAnchorX::Left, ENineAnchorY::Bottom);

        m_IconFront.SetVisible(true);
        m_IconFront.SetGraph(image);
        m_IconFront.SetPositionParent(anchor);
        //m_IconFront.SetPosition(iconPos);
        //m_IconFront.SetSrcRect(RectInt{ iconLength, 0, iconLength, iconLength });
        ZIndexUi(&m_IconFront).SetIndex(1).ApplyZ();

        m_IconBack.SetVisible(true);
        m_IconBack.SetGraph(image);
        m_IconBack.SetPositionParent(anchor);
        //m_IconBack.SetPosition(iconPos);
        m_IconBack.SetSrcRect(RectInt{ 0, 0, iconLength, iconLength });
        ZIndexUi(&m_IconBack).ApplyZ();

        m_TextPassage.ShowImmediately();
        m_TextPassage.SetPositionParent(anchor);
        m_TextPassage.SetPos(VecDouble2{ 4, -4 });
        m_TextPassage.SetAlignment(ETextHorizontalAlign::Left, ETextVerticalAlign::Bottom);
        m_TextPassage.SetZIndex(0);
        m_TextPassage.SetScale(VecOne<double>());
        m_TextPassage.UpdateTextAndView("ステージ選択画面に戻ります");

        // 左から出てくるアニメーション
        m_SelfAnim = getAnimator()->TargetVirtual()
            ->AnimValue(-m_TextPassage.GetMaxWidth(), 4, [this, iconPosY](double value) {
                    const auto iconPos = VecDouble2{value, iconPosY};
                    m_IconFront.SetPosition(iconPos);
                    m_IconBack.SetPosition(iconPos);
                    m_TextPassage.SetPos(VecDouble2{ value, -4 });
                    m_TextPassage.UpdateView();
                }, 0.5)->SetEase(EAnimEase::OutBack)
            ->ToWeakPtr();
    }

    TextPassage RetirementHelp::initTextPassage(GameRoot* root) const
    {
        return TextPassage(
            root->GetAppState(),
            root->RscFont->KHDotAkihabara32px.get(),
            Rgba(255, 255, 255),
            Rgba(32, 32, 32));
    }
    TextureAnimator* RetirementHelp::getAnimator()
    {
        return &m_Scene->GetTextureAnimator();
    }
}
