//
// Created by sashi0034 on 2022/09/17.
//

#include "WinTile.h"
#include "../ZIndex.h"

namespace inGame::character
{
    WinTile::WinTile(IMainScene *mainScene, const MatPos &matPos) :
        CharacterBase(mainScene->GetFieldManager()),
        Pos(MatPos(matPos.GetVec())),
        m_View(mainScene->GetScrollManager(),
               mainScene->GetRoot()->RscImage->win_24x24.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellSrcSize});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{double(cellSrcSize.X - pixel::PixelPerMat), double(cellSrcSize.Y - pixel::PixelPerMat)}/2.0);

        ZIndexBackGround(&m_View.GetView()).GoFront(1).ApplyZ();

        const double frameDuration = 0.2;
        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->AnimGraph(cellSrcSize)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, frameDuration)
                ->AddFrame(Vec2{1, 0}, frameDuration)
                ->AddFrame(Vec2{2, 0}, frameDuration)
                ->AddFrame(Vec2{3, 0}, frameDuration)
                ->AddFrame(Vec2{4, 0}, frameDuration)
                ->AddFrame(Vec2{5, 0}, frameDuration);

        if (auto player = mainScene->GetPlayer())
        {
            subscribePlayer(matPos, player);
        }
    }

    void WinTile::subscribePlayer(const MatPos &matPos, Player *const player)
    {
        // TODO
        (void)matPos;
        (void)player;
    }
} // inGame::character