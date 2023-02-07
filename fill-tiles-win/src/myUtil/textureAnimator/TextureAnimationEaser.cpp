//
// Created by sashi0034 on 2022/05/29.
//

#include <cassert>
#include "TextureAnimationEaser.h"
#include "../easing.h"

namespace myUtil::textureAnimator
{
    TextureAnimationEaser::TextureAnimationEaser(const WeakPtr<SpriteTexture> &mTargetTexture, double endSecond)
            : m_TargetTexture(mTargetTexture), m_EndTime(endSecond)
    {}

    void TextureAnimationEaser::SetEase(EAnimEase ease)
    {
        m_Ease = ease;
    }

    void TextureAnimationEaser::SetLoop(int loopMax)
    {
        m_LoopMax = loopMax;
    }

    void TextureAnimationEaser::SetRelative(bool isRelative)
    {
        m_IsRelative = isRelative;
    }

    void TextureAnimationEaser::Update(double deltaSec)
    {
        if (m_EndTime == 0) return;
        if (IsDead()) return;

        m_Time = std::min(deltaSec + m_Time, m_EndTime);

        switch (m_Ease)
        {
            case EAnimEase::Linear:
                m_ProgressRatio = m_Time / m_EndTime;
                break;
            case EAnimEase::InBack:
                m_ProgressRatio = easing::EaseInBack(m_Time / m_EndTime);
                break;
            case EAnimEase::OutBack:
                m_ProgressRatio = easing::EaseOutBack(m_Time / m_EndTime);
                break;
            default:
                assert(false);
        }

        if (m_Time >= m_EndTime) stepNextLoop();
    }

    void TextureAnimationEaser::stepNextLoop()
    {
        m_Time=0;
        m_LoopCount += 1;
    }

    bool TextureAnimationEaser::IsDead() const
    {
        return m_LoopCount>=m_LoopMax;
    }
}