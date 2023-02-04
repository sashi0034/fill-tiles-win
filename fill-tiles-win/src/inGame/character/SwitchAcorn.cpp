//
// Created by sashi0034 on 2022/08/15.
//

#include "SwitchAcorn.h"
#include "../ZIndex.h"
#include "../SwitchAcornManager.h"

namespace inGame::character
{
    SwitchAcorn::SwitchAcorn(MainScene *mainScene, const MatPos &matPos, ESwitchAcornKind kind)
            : CharacterBase(mainScene->GetFieldManager()),
              selfKind(kind),
              mainScene(mainScene),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->rb_acorn_16x16.get()),
              initialPos(matPos)
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(FieldManager::CharacterPadding);

        ZIndexCharacter(m_View).ApplyZ();

        getAcornManager()->OnSwitch().subscribe([&](SwitchAcornEventArgs* event){
            onSwitch(event->NextActiveKind);
        });

        onSwitch(getAcornManager()->GetCurrSwitch());
    }


    SwitchAcornManager *SwitchAcorn::getAcornManager()
    {
        return mainScene->GetFieldManager()->GetSwitchAcornManager();
    }

    void SwitchAcorn::onSwitch(ESwitchAcornKind nextKind)
    {
        const int cellY = int(selfKind);

        const bool isActive = nextKind == selfKind;

        mainScene->GetFieldManager()->OverwriteWallFlag(initialPos, isActive);

        if (!m_TextureAnimation.IsNull()) mainScene->GetFieldManager()->GetAnimator()->Destroy(m_TextureAnimation);

        if (isActive)
        {
            ZIndexCharacter(m_View).ApplyZ();
            m_View.GetView().SetSrcRect(Rect<int>{Vec2{0, cellY} * FieldManager::PixelPerMat, cellMatSize * FieldManager::PixelPerMat});
            m_TextureAnimation = mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                    ->VirtualDelay([]() {}, (initialPos.GetSumXY() % 4) * 0.2)
                    ->Then()
                    ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                    ->AddFrame(Vec2{0, cellY}, 0.2)
                    ->AddFrame(Vec2{1, cellY}, 0.2)
                    ->AddFrame(Vec2{2, cellY}, 0.2)
                    ->AddFrame(Vec2{3, cellY}, 0.2)
                    ->ToWeakPtr();
        }
        else
        {
            ZIndexBackGround(&m_View.GetView()).GoFront(10).ApplyZ();
            int idleCellX = 4;
            m_View.GetView().SetSrcRect(Rect<int>{Vec2{idleCellX, cellY} * FieldManager::PixelPerMat,
                                                  cellMatSize * FieldManager::PixelPerMat});
        }
    }

} // inGame