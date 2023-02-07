//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_TEXTUREANIMATOR_H
#define FILL_TILES_TEXTUREANIMATOR_H

#include <stdafx.h>
#include "SpriteTexture.h"
#include "ChildrenPool.h"
#include "boost/coroutine2/coroutine.hpp"
#include "textureAnimator/TextureAnimationProcessor.h"

namespace myUtil
{
    namespace textureAnimator
    {
        class ITextureAnimationStarter;
    }

    enum class EAnimEase{
        Linear,
        InBack,
        OutBack,
    };


    using TextureAnimationWeakPtr = WeakPtr<textureAnimator::ITextureAnimationPointer>;

    class ITextureAnimator
    {
    public:
        virtual textureAnimator::ITextureAnimationStarter * TargetTo(SpriteTexture &texture) = 0;
        virtual bool Destroy(TextureAnimationWeakPtr& target) = 0;
    };

    class TextureAnimator : public ITextureAnimator
    {
    public:
        textureAnimator::ITextureAnimationStarter * TargetTo(SpriteTexture &texture) override;
        textureAnimator::ITextureAnimationStarter* TargetVirtual();

        bool Destroy(TextureAnimationWeakPtr &target) override;

        void Update(double deltaTime);
        void Release();
        ~TextureAnimator();
    private:
        ChildrenPool<textureAnimator::TextureAnimationProcessor> m_Pool;
    };


}


#endif //FILL_TILES_TEXTUREANIMATOR_H
