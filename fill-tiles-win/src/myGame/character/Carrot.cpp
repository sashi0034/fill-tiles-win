//
// Created by sashi0034 on 2022/09/17.
//

#include "Carrot.h"
#include "../ZIndex.h"

namespace myGame::character
{
    Carrot::Carrot(MainScene *mainScene, const MatPos &matPos) :
            CharacterBase(mainScene->GetFieldManager()),
            m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->carrot_16x32.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});;

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(Vec2<double>{0, double(1 - cellMatSize.Y) * FieldManager::PixelPerMat}
                                     + FieldManager::CharacterPadding);

        mainScene->GetFieldManager()->OverwriteWallFlag(matPos, Vec2<int>{cellMatSize.X, cellMatSize.Y * -1 + 1}, true);

        ZIndexCharacter(m_View).ApplyZ();

        const double frameDuration = 0.3;
        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, frameDuration)
                ->AddFrame(Vec2{1, 0}, frameDuration)
                ->AddFrame(Vec2{2, 0}, frameDuration)
                ->AddFrame(Vec2{3, 0}, frameDuration)
                ->AddFrame(Vec2{4, 0}, frameDuration);
    }
} // myGame