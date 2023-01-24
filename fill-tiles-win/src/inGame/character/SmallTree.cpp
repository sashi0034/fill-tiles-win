//
// Created by sashi0034 on 2022/06/17.
//

#include "SmallTree.h"
#include "../ZIndex.h"

namespace inGame::character{

    SmallTree::SmallTree(IMainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager())
            , m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->tree_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(FieldManager::CharacterPadding);

        mainScene->GetFieldManager()->OverwriteWallFlag(matPos, true);

        ZIndexCharacter(m_View).ApplyZ();

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->VirtualDelay([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, 0.2)
                ->AddFrame(Vec2{1, 0}, 0.2)
                ->AddFrame(Vec2{2, 0}, 0.2)
                ->AddFrame(Vec2{3, 0}, 0.4);
    }
}
