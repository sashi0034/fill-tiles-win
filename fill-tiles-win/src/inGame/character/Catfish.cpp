//
// Created by sashi0034 on 2022/07/18.
//

#include "Catfish.h"
#include "../ZIndex.h"
#include "../ParabolaAnimation.h"

namespace inGame::character
{
    Catfish::Catfish(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
              m_Scene(mainScene),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->catfish_24x24.get()),
              m_MovableObjectLogic(mainScene, &m_View)
    {
        const int pixelPerMat = FieldManager::PixelPerMat;
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellSrcSize});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{(cellSrcSize.X - pixelPerMat) / 2.0, double(cellSrcSize.Y - pixelPerMat)});

        m_View.SetCollider(this, mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(cellSrcSize)->SetFrameLoopEndless(true)->SetCanFlip(false)
                ->AddFrame(Vec2{0, 0}, 0.3)
                ->AddFrame(Vec2{1, 0}, 0.2)
                ->AddFrame(Vec2{2, 0}, 0.2)
                ->AddFrame(Vec2{3, 0}, 0.2)
                ->AddFrame(Vec2{4, 0}, 0.2);
    }

    void Catfish::Update(IAppState *)
    {
        ZIndexCharacter(m_View).ApplyZ();
    }

    UpFlag& Catfish::GetEatableFlag()
    {
        return m_EatableFlag;
    }

    ParabolaAnimation* Catfish::JumpWhenEat()
    {
        return ParabolaAnimation::Create(m_Scene->GetEffectManager(), &m_View.GetView())->SetSpeedByPeekHeightAndTime(40.0, 0.5);
    }

    MovableObjectLogic *Catfish::GetMovable()
    {
        return &m_MovableObjectLogic;
    }

} // inGame