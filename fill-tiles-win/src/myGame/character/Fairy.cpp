//
// Created by sashi0034 on 2022/07/13.
//

#include "Fairy.h"
#include "../ZIndex.h"
#include "../Player.h"
#include "../TalkingBalloon.h"

namespace myGame::character
{

    Fairy::Fairy(MainScene *mainScene, const MatPos &matPos, const std::string &message)
            : CharacterBase(mainScene->GetFieldManager())
            , m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->blobwob_24x24.get())
    {
        const int pixelPerMat = FieldManager::PixelPerMat;
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellSrcSize});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{(cellSrcSize.X - pixelPerMat) / 2.0, double(cellSrcSize.Y - pixelPerMat)});

        m_View.SetCollider(this, mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        ZIndexCharacter(m_View).ApplyZ();

        auto player = mainScene->GetPlayer();
        if (player!= nullptr)
        {
            subscribePlayerMove(mainScene, matPos, message, player);
        }

        mainScene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetView())
                ->DelayVirtual([]() {}, (matPos.GetSumXY() % 4) * 0.2)
                ->Then()
                ->AnimGraph(cellSrcSize)->SetFrameLoopEndless(true)->SetCanFlip(false)
                ->AddFrame(Vec2{0, 0}, 0.2)
                ->AddFrame(Vec2{1, 0}, 0.1)
                ->AddFrame(Vec2{2, 0}, 0.2)
                ->AddFrame(Vec2{3, 0}, 0.1)
                ->AddFrame(Vec2{4, 0}, 0.2)
                ->AddFrame(Vec2{5, 0}, 0.1)
                ->AddFrame(Vec2{6, 0}, 0.2)
                ->AddFrame(Vec2{7, 0}, 0.1)
                ->AddFrame(Vec2{8, 0}, 0.2)
                ->AddFrame(Vec2{9, 0}, 0.4);
    }

    void Fairy::subscribePlayerMove(MainScene *mainScene, const MatPos &selfMatPos, const std::string &message,
                                    const Player *player)
    {
        player->OnMoveBegin().subscribe([&, selfMatPos, message, mainScene](PlayerMoveData *moveData) {
            m_View.GetView().SetFlip(moveData->AfterPos.GetVec().X > selfMatPos.GetVec().X);

            constexpr int awayDistance = 3;
            constexpr int talkAbleDistance = 1;

            // プレイヤーが離れていたらフラグをつける
            if (!m_AwayFromPlayerFlag.GetFlagWithoutTake() && moveData->AfterPos.CalcManhattan(selfMatPos) >= awayDistance)
                m_AwayFromPlayerFlag.PutPoll();

            // プレイヤーが近づいていなかったら中止
            if (moveData->AfterPos.CalcManhattan(selfMatPos) > talkAbleDistance) return;

            // プレイヤーが離れていたフラグがなかったら中止
            if (!m_AwayFromPlayerFlag.TakePoll()) return;

            // 表示した会話が残っていたら中止
            if (!m_TalkingRef.IsNull()) return;

            // 会話を発生
            m_TalkingRef = TalkingBalloon::Create(mainScene, message, selfMatPos)->GetWeakPtr();
        });
    }
}
