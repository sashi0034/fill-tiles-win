//
// Created by sashi0034 on 2022/06/26.
//

#include "MineFlower.h"
#include "../ZIndex.h"

namespace myGame::character{

    MineFlower::MineFlower(MainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
              Position(matPos),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->mine_flower_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(FieldManager::CharacterPadding);

        //mainScene->GetFieldManager()->OverwriteWallFlag(matPos, true);

        ZIndexCharacter(m_View).ApplyZ();

        constexpr double frameDuration = 0.15;

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                //->DelayVirtual([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                //->Then()
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(false)
                ->AddFrame(Vec2{0, 0}, frameDuration)
                ->AddFrame(Vec2{1, 0}, frameDuration)
                ->AddFrame(Vec2{2, 0}, frameDuration)
                ->AddFrame(Vec2{3, 0}, frameDuration)
                ->AddFrame(Vec2{4, 0}, frameDuration)
                ->AddFrame(Vec2{5, 0}, frameDuration)
                ->Then()
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 1}, frameDuration * 2)
                ->AddFrame(Vec2{1, 1}, frameDuration)
                ->AddFrame(Vec2{2, 1}, frameDuration)
                ->AddFrame(Vec2{3, 1}, frameDuration)
                ->AddFrame(Vec2{4, 1}, frameDuration)
                ->AddFrame(Vec2{5, 1}, frameDuration);

    }
}