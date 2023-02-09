//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_PLAYER_H
#define FILL_TILES_PLAYER_H

#include "ActorBase.h"
#include "player/PlayerState.h"
#include "Angle.h"
#include "FieldManager.h"
#include "MainScene.h"
#include "CharacterViewModel.h"
#include "rx.h"
#include "player/PlayerMoveData.h"
#include "player/PlayerActionData.h"
#include "character/Catfish.h"
#include "player/PlayerAnimation.h"
#include "player/PlayerScroll.h"
#include "player/input.h"

using namespace myGame::player;

namespace myGame
{

    struct PlayerWalkArgs
    {
        IAppState *AppStateRef;
        EAngle NewAngle;
        bool CanChangeAnim;
        bool IsDash;
        bool IsFromOnIce;
    };

    class Player final : public ActorBase, ISprRectColliderOwner
    {
    public:
        explicit Player(IChildrenPool<ActorBase> *belonging, MainScene *mainScene, const MainSceneResetInfo& resetInfo);
        void Init() override;
        void Update(IAppState *appState) override;
        Vec2<double> GetPos();
        void SetPos(const Vec2<double> &pos);
        MatPos GetMatPos();
        [[nodiscard]] rx::observable<PlayerMoveData*> OnMoveBegin() const;
        [[nodiscard]] rx::observable<PlayerMoveData*> OnMoveFinish() const;
        [[nodiscard]] rx::observable<PlayerActionData*> OnAction() const;
        void ChangeStateToDead();
        void ChangeStateToWarp(const MatPos& startPos, const MatPos& endPos);
        PlayerScroll* GetScroll();
        int GetSteppedCount() const;

        static inline const Vec2<int> CellSize{32, 32};
    private:
        void setPos(Vec2<double> newPos);
        void initViewModel();

        void initAction();

        static bool isDashing(const Uint8 *keyState);

        unique_ptr<CharacterViewModel> m_View{};
        unique_ptr<PlayerAnimation> m_AnimationLogic{};
        unique_ptr<PlayerScroll> m_PlayerScroll{};

        Graph* m_Image;

        TextureAnimator m_PlayerAnimator{};
        PlayerState m_State = PlayerState(EPlayerState::Walking);
        EAngle m_Angle = EAngle::Down;
        MainScene* m_ParentalScene;
        FieldManager* m_Field;

        int m_SteppedCount = 0;

        ChildrenPool<ProcessTimer> m_SubProcess{};
        rx::subject<PlayerMoveData*> m_OnMoveBegin{};
        rx::subject<PlayerMoveData*> m_OnMoveFinish{};
        rx::subject<PlayerActionData*> m_OnAction;

        void changeStateToWalking(const PlayerWalkArgs& args);

        CoroTask wait(CoroTaskYield &yield, IAppState *appState);
        CoroTask walk(CoroTaskYield &yield, PlayerWalkArgs args);
        CoroTask performDead(CoroTaskYield& yield, IAppState* appState);
        CoroTask performWarp(CoroTaskYield &yield, MatPos startPos, MatPos endPos);

        EAngle tryWalkOrActionByInput(CoroTaskYield &yield, const IAppState *appState);

        bool isRunningFieldEvent();

        void waitFieldEvent(CoroTaskYield &yield);

        void tackleToFieldObject(CoroTaskYield &yield, EAngle angle, const std::function<void()> &onTackleHit);

        void pushCatfish(CoroTaskYield &yield, EAngle &inputAngle, myGame::character::Catfish *catfish);

        bool checkPushMovableObject(CoroTaskYield &yield, EAngle &inputAngle, character::MovableObjectLogic* movable);
    };


}


#endif //FILL_TILES_PLAYER_H
