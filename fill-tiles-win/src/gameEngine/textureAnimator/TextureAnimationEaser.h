//
// Created by sashi0034 on 2022/05/29.
//

#ifndef FILL_TILES_TEXTUREANIMATIONEASER_H
#define FILL_TILES_TEXTUREANIMATIONEASER_H

#include "../TextureAnimator.h"

namespace gameEngine::textureAnimator
{

    class TextureAnimationEaser
    {
    private:
    public:
        explicit TextureAnimationEaser(const WeakPtr<SpriteTexture> &mTargetTexture, double endSecond);

        void SetEase(EAnimEase ease);
        void SetLoop(int loopMax);
        void SetRelative(bool isRelative);
        void Update(double deltaSec);
        bool IsDead() const;

    private:
        WeakPtr<SpriteTexture> m_TargetTexture;
        EAnimEase m_Ease = EAnimEase::Linear;

        const double m_EndTime = 0;
        double m_Time = 0;
        double m_ProgressRatio = 0;

        int m_LoopMax = 1;
        int m_LoopCount = 0;

        bool m_IsRelative = false;

        void stepNextLoop();
    public:
        template<typename T> T CalcProgressValue(const T& startValue, const T& globalEndValue){
            T endValue = globalEndValue;
            if (m_IsRelative) endValue = endValue + startValue;
            T ret = startValue * (1.0-m_ProgressRatio) + endValue * m_ProgressRatio;
            return ret;
        }
    };
}


#endif //FILL_TILES_TEXTUREANIMATIONEASER_H
