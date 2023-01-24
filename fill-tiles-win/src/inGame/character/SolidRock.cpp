//
// Created by sashi0034 on 2022/08/13.
//

#include "SolidRock.h"
#include "../ZIndex.h"

namespace inGame::character
{
    SolidRock::SolidRock(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
            m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->solid_rock_16x16.get()),
            m_Movable(mainScene, &m_View)
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(FieldManager::CharacterPadding);

        m_View.SetCollider(this, mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        ZIndexCharacter(m_View).ApplyZ();

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.5)
                ->Then()
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, 1.0)
                ->AddFrame(Vec2{1, 0}, 0.5);
    }

    void SolidRock::Update(IAppState*)
    {
        ZIndexCharacter(m_View).ApplyZ();
    }

    MovableObjectLogic *SolidRock::GetMovable()
    {
        return &m_Movable;
    }
} // inGame