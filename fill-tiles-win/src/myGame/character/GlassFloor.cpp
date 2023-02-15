//
// Created by sashi0034 on 2022/08/12.
//

#include "GlassFloor.h"
#include "../ZIndex.h"
#include "../effect/TextureScrapping.h"

namespace myGame::character
{
    GlassFloor::GlassFloor(MainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
            mainScene(mainScene),
            m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->glass_floor_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        ZIndexBackGround(&m_View.GetView()).GoFront(1).ApplyZ();

        auto writable = mainScene->GetFieldManager()->GetTileMap()->GetElementWritableAt(matPos.GetVec());
        writable->SetGlassFloor(this);

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->AnimGraph(cellMatSize * FieldManager::PixelPerMat)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, 0.2 * 10)
                ->AddFrame(Vec2{1, 0}, 0.2)
                ->AddFrame(Vec2{2, 0}, 0.2);
    }

    void GlassFloor::MakeBrokenAndDestroy()
    {
        effect::TextureScrapping::Produce(effect::TextureScrappingArgs{
            mainScene->GetEffectManager(),
            m_View.GetModel().GetPosition(),
            m_View.GetView().GetSrcRect(),
            mainScene->GetRoot()->RscImage->glass_floor_16x16.get()});
        Destroy();
    }
} // myGame
