//
// Created by sashi0034 on 2022/08/15.
//

#include "SwitchButton.h"
#include "../ZIndex.h"
#include "../SwitchAcornManager.h"
#include "../Player.h"

namespace myGame::character
{
    SwitchButton::SwitchButton(MainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
              mainScene(mainScene),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->button_floor_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        ZIndexBackGround(&m_View.GetView()).GoFront(1).ApplyZ();

        if (auto player = mainScene->GetPlayer())
        {
            subscribePlayer(matPos, player);
        }


//        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
//                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
//                ->AddFrame(Vec2{0, 0}, 0.2 * 10)
//                ->AddFrame(Vec2{1, 0}, 0.2)
//                ->AddFrame(Vec2{2, 0}, 0.2);
    }

    void SwitchButton::subscribePlayer(const MatPos &matPos, const Player *player)
    {
        constexpr double animDuration = 0.1;

        player->OnMoveFinish().subscribe([matPos, this](PlayerMoveData* data){
            const auto acornManager = mainScene->GetFieldManager()->GetSwitchAcornManager();

            // ボタンに乗ったとき
            if (data->AfterPos == matPos)
            {
                acornManager->GoNextSwitch(this);

                resetAnimation();
                mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                    ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(false)
                    ->AddFrame(Vec2{0, 0}, animDuration)
                    ->AddFrame(Vec2{1, 0}, animDuration)
                    ->AddFrame(Vec2{2, 0}, animDuration)
                    ->AddFrame(Vec2{3, 0}, animDuration);
            }
        });

        player->OnMoveBegin().subscribe([matPos, this](PlayerMoveData* data){
            // ボタンから離れたとき
            if (data->BeforePos == matPos)
            {
                resetAnimation();
                mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                        ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(false)
                        ->AddFrame(Vec2{3, 0}, animDuration)
                        ->AddFrame(Vec2{2, 0}, animDuration)
                        ->AddFrame(Vec2{1, 0}, animDuration)
                        ->AddFrame(Vec2{0, 0}, animDuration);
            }
        });
    }

    void SwitchButton::resetAnimation()
    { if (!m_Animation.IsNull()) mainScene->GetFieldManager()->GetAnimator()->Destroy(m_Animation); }
} // myGame
