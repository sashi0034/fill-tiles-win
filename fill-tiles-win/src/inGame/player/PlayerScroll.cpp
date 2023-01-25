//
// Created by sashi0034 on 2022/08/17.
//

#include "stdafx.h"

#include "PlayerScroll.h"
#include "../ScrollManager.h"
#include "../FieldEventManager.h"

namespace inGame::player
{

    void PlayerScroll::scrollByTracking(const Vec2<double> &trackingPos)
    {
        if (m_ShouldResetScroll)
        {
            m_ShouldResetScroll = false;
            scrollManager->SetScroll(trackingPos);
            return;
        }

        auto currPos = scrollManager->GetScroll();

        const double deltaMovingRate = 0.02;
        auto newPos = currPos * (1 - deltaMovingRate ) + trackingPos * deltaMovingRate;

        scrollManager->SetScroll(newPos);
    }

    void PlayerScroll::UpdateFixedly()
    {
        if (fieldEvent->IsTakingScroll()) return;

        if (m_FocusingSprite== nullptr) return;

        auto scrollPos = scrollManager->CalcScrollToCenter(m_FocusingSprite->GetPosition());
        scrollPos = scrollManager->MakePosInFieldRange(scrollPos);
//            constexpr int overhangByWalk = 60;
//            if (m_State.GetState()==EPlayerState::Walking)
//                scrollPos = scrollPos - Angle(m_Angle).ToXY().CastTo<double>() * overhangByWalk;
        scrollByTracking(scrollPos);
    }

    PlayerScroll::PlayerScroll(FieldEventManager *fieldEvent, ScrollManager *scrollManager,
                               SpriteTexture *playerSprite) : fieldEvent(fieldEvent), scrollManager(scrollManager),
                                                                  m_PlayerSprite(playerSprite)
    {
        m_FocusingSprite = m_PlayerSprite;
    }

    void PlayerScroll::ChangeFocus(SpriteTexture* target)
    {
        m_FocusingSprite = target;
    }

    void PlayerScroll::ResetFocus()
    {
        m_FocusingSprite = m_PlayerSprite;
    }

    void PlayerScroll::RequestResetScroll()
    {
        m_ShouldResetScroll = true;
    }
} // inGame
