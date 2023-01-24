//
// Created by sashi0034 on 2022/08/19.
//

#include "WarpTile.h"
#include "../ZIndex.h"
#include "../Player.h"
#include "../effect/WarpLoops.h"

using namespace inGame;

namespace inGame::character
{
    // TODO: 時間があったらキノコくんがぐるぐるするアニメーションを作りたいかも

    WarpTile::WarpTile(IMainScene *mainScene, const MatPos &matPos, char key)
            : CharacterBase(mainScene->GetFieldManager()),
              Pos(MatPos(matPos.GetVec())),
              m_View(mainScene->GetScrollManager(),
              mainScene->GetRoot()->RscImage->warp_tile_16x16.get())
    {
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellMatSize * FieldManager::PixelPerMat});

        m_View.SetModelPos(matPos);

        ZIndexBackGround(&m_View.GetView()).GoFront(1).ApplyZ();

        m_Warp = mainScene->GetFieldManager()->GetWarpManager()->Register(key, this);

        if (auto player = mainScene->GetPlayer())
        {
            subscribePlayer(matPos, player);
        }

        effect::WarpLoops::Produce(mainScene->GetEffectManager(), matPos.ToPixelPos() + FieldManager::MatPixelSize.CastTo<double>() / 2.0 );
    }

    void WarpTile::subscribePlayer(const MatPos &matPos, Player *const player)
    {
        player->OnMoveFinish().subscribe([this, matPos, player](PlayerMoveData* data){
            if (data->AfterPos==matPos)
            {
                auto&& nextWarp = m_Warp->GetNext(this);
                player->ChangeStateToWarp(this->Pos, nextWarp->Pos);
            }
        });
    }
} // inGame