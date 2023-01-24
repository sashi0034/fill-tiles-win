//
// Created by sashi0034 on 2022/08/17.
//

#ifndef FILL_TILES_GROWINGCHICK_H
#define FILL_TILES_GROWINGCHICK_H

#include "CharacterBase.h"
#include "../MainScene.h"
#include "../MatPos.h"
#include "../CharacterViewModel.h"
#include "../TextPassage.h"

namespace inGame::character
{
    enum class EGrowingChickGrowth
    {
        Egg,
        Child,
        Adult
    };

    class GrowingChick final : public CharacterBase, public ISprRectColliderOwner
    {
    public:
        GrowingChick(IMainScene *mainScene, const MatPos &matPos);

        void Update(IAppState *app) override;
    private:
        static const inline std::string className = "GrowingChick";
        IMainScene* m_Scene;
        ITextureAnimator* animator = m_Scene->GetFieldManager()->GetAnimator();
        CharacterViewModel m_View;
        TextureAnimationWeakPtr m_AnimationRef{};
        EGrowingChickGrowth m_Growth = EGrowingChickGrowth::Egg;
        IAppState* appState = m_Scene->GetRoot()->GetAppState();
        LuaEngine* lua = m_Scene->GetRoot()->GetLua();

        void subscribePlayerMove(IMainScene *mainScene, const Player *player);

        static const inline Vec2<int> cellMatSize = Vec2<int>{1, 1};
        static const inline Vec2<int> eggCellSrcSize = Vec2<int>{16, 16};
        static const inline Vec2<int> childCellSrcSize = Vec2<int>{16, 16};
        static const inline Vec2<int> adultCellSrcSize = Vec2<int>{32, 32};

        void animWhenEgg();
        void startChildProcess(CoroTaskYield& yield);

        void setViewPos(const Vec2<int>& cellSize);

        void animWaitWhenChild(EAngle angle);
        void animMoveWhenChild(EAngle angle);

        bool tryMoveByAngleSync(CoroTaskYield &yield, EAngle inputAngle, const std::function<void()>& onStartAnim);

        void flipViewByAngle(const EAngle &angle);

        bool isFlipViewByAngle(const EAngle &angle) const;

        void moveUntilConfirm(CoroTaskYield &yield);

        bool moveIfNewInputIsSameOfBefore(CoroTaskYield &yield, EAngle *inputAngle);

        void becomeAdult();

        void becomeChild();


        void performAnimJumpUpWhenBorn(CoroTaskYield &yield);

        unique_ptr<TextPassage> createManualText(IMainScene *mainScene) const;

        void initManualText(unique_ptr<TextPassage> &manualText);
    };

} // inGame

#endif //FILL_TILES_GROWINGCHICK_H
