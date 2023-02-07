//
// Created by sashi0034 on 2022/08/31.
//

#include "FieldViewTest.h"
#include "../MainScene.h"
#include "../pixel.h"
#include "../Player.h"

namespace myGame::test
{

    FieldViewTest::FieldViewTest(MainScene *mainScene, IChildrenPool<ActorBase> *parentPool) :
            ActorBase(parentPool),
            sceneRef(mainScene),
            m_DirChangeDetector(field::TileMap::TileMapDirectory)
    {
        m_ProcessUntilFileChanged = std::make_unique<ProcessTimer>([&](){
            bool changed = m_DirChangeDetector.CheckChanged();
            if (changed) return EProcessStatus::Dead;
            return EProcessStatus::Running;
        }, 0.5);

        invalidatePlayerScroll();
    }

    void FieldViewTest::Update(IAppState *appState)
    {
        scrollByMouse(appState);

        m_ProcessUntilFileChanged->Update(appState->GetTime().GetDeltaSec());
        if (m_ProcessUntilFileChanged->GetStatus()==EProcessStatus::Dead)
        {
            sceneRef->RequestResetScene(MainSceneResetInfo{1, sceneRef->GetScrollManager()->GetScroll()});
            return;
        }
    }

    void FieldViewTest::scrollByMouse(const IAppState *appState)
    {
        invalidatePlayerScroll();

        auto mouse = appState->GetMouseState();
        if (mouse->GetPushed(EMouseButton::Left))
        {
            const auto mousePos = mouse->GetPosition();

            if (!m_IsClickedBefore)
            {
                m_PosOnClicked = mousePos;
                m_IsClickedBefore = true;
            }

            const auto diff = mousePos - m_PosOnClicked;
            const double vel = -0.1;
            auto newPos = sceneRef->GetScrollManager()->GetScroll() + diff * vel;

            auto matSize = sceneRef->GetFieldManager()->GetTileMap()->GetMatSize();
            const double margin = 32;

            const double maxX = margin;
            const double maxY = margin;

            const double minX = -matSize.X * pixel::PixelPerMat + appState->GetScreenSize().X - margin;
            const double minY = -matSize.Y * pixel::PixelPerMat + appState->GetScreenSize().Y - margin;

            newPos.X = Range<double>(minX, maxX).MakeInRange(newPos.X);
            newPos.Y = Range<double>(minY, maxY).MakeInRange(newPos.Y);

            sceneRef->GetScrollManager()->SetScroll(newPos);
        }
    }

    void FieldViewTest::invalidatePlayerScroll()
    { sceneRef->GetPlayer()->GetScroll()->ChangeFocus(nullptr); }

}


// myGame