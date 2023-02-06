//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_TEXTUREANIMATIONPROCESSOR_H
#define FILL_TILES_TEXTUREANIMATIONPROCESSOR_H

#include "../WeakPtr.h"
#include "../SpriteTexture.h"
#include "../ChildrenPool.h"

namespace gameEngine{
    enum class EAnimEase;
    class TextureAnimator;

}
namespace gameEngine::textureAnimator
{
    namespace textureAnimation
    {
        class AnimationBase;
    }
    class ITextureAnimationEaseProperty;
    class ITextureAnimationLinker;
    class ITextureAnimationGraphProperty;


    class ITextureAnimationStarter
    {
    public:
        virtual ITextureAnimationEaseProperty * AnimPosition(Vec2<double> endPos, double duration) = 0;
        virtual ITextureAnimationEaseProperty * AnimRotation(double endDeg, double duration) = 0;
        virtual ITextureAnimationEaseProperty * AnimScale(const Vec2<double> &endScale, double duration) = 0;
        virtual ITextureAnimationEaseProperty * AnimBlend(int blendPal, double duration) = 0;
        virtual ITextureAnimationGraphProperty * AnimGraph(Vec2<int> cellSize) = 0;
        virtual ITextureAnimationLinker * DelayVirtual(std::function<void()> process, double deltaTime) = 0;
    };

    class ITextureAnimationPointer
    {
    public:
        virtual WeakPtr<ITextureAnimationPointer> ToWeakPtr() = 0;
        virtual void ForceDestroy() = 0;
    };

    class ITextureAnimationWith : public ITextureAnimationPointer
    {
    public:
        virtual ITextureAnimationStarter * With() = 0;
    };

    class ITextureAnimationLinker : public ITextureAnimationWith
    {
    public:
        virtual ITextureAnimationStarter * Then() = 0;
    };

    class ITextureAnimationEaseProperty : public ITextureAnimationLinker
    {
    public:
        virtual ITextureAnimationEaseProperty * SetEase(gameEngine::EAnimEase easeType) = 0;
        virtual ITextureAnimationEaseProperty * SetLoop(int loop) = 0;
        virtual ITextureAnimationEaseProperty * SetRelative(bool isRelative) = 0;
    };

    class ITextureAnimationGraph : public ITextureAnimationLinker
    {
    public:
        virtual ITextureAnimationGraph* AddFrame(Vec2<int> cellPos, double duration) = 0;
        virtual ITextureAnimationGraph* AddFrameFlipped(Vec2<int> cellPos, double duration) = 0;
    };

    class ITextureAnimationGraphProperty : public ITextureAnimationGraph
    {
    public:
        virtual ITextureAnimationGraphProperty* SetFrameLoop(int loop) = 0;
        virtual ITextureAnimationGraphProperty* SetFrameLoopEndless(bool loop) = 0;
        virtual ITextureAnimationGraphProperty* SetCellSrcStart(Vec2<int> cellSrcStart) = 0;
        virtual ITextureAnimationGraphProperty* SetCanFlip(bool canFlip) = 0;
    };

    class TextureAnimationProcessor final:
            public ITextureAnimationStarter,
            public ITextureAnimationEaseProperty,
            public ITextureAnimationGraphProperty
    {
    public:
        DEF_WEAK_CONTROLLER(TextureAnimationProcessor);
        WeakPtr<ITextureAnimationPointer> ToWeakPtr() override;
    public:
        TextureAnimationProcessor(const WeakPtr <SpriteTexture> &texture, IChildrenPool <TextureAnimationProcessor> *parentalPool, WeakPtr<TextureAnimationProcessor> *beforeAnimation);

        ITextureAnimationEaseProperty * AnimPosition(Vec2<double> endPos, double duration) override;
        ITextureAnimationEaseProperty * AnimRotation(double endDeg, double duration) override;
        ITextureAnimationEaseProperty * AnimScale(const Vec2<double> &endScale, double duration) override;
        ITextureAnimationEaseProperty * AnimBlend(int endBlendPal, double duration) override;
        ITextureAnimationLinker * DelayVirtual(std::function<void()> process, double delayTime) override;
        ITextureAnimationStarter * Then() override;
        ITextureAnimationStarter * With() override;
        ITextureAnimationEaseProperty * SetEase(gameEngine::EAnimEase easeType) override;
        ITextureAnimationEaseProperty * SetLoop(int loop) override;
        ITextureAnimationEaseProperty * SetRelative(bool isRelative) override;

        ITextureAnimationGraphProperty *AnimGraph(Vec2<int> cellSize) override;
        ITextureAnimationGraphProperty *SetCellSrcStart(Vec2<int> cellSrcStart) override;
        ITextureAnimationGraphProperty* SetCanFlip(bool canFlip) override;
        ITextureAnimationGraph *AddFrame(Vec2<int> cellPos, double duration) override;
        ITextureAnimationGraphProperty *SetFrameLoop(int loop) override;
        ITextureAnimationGraph *AddFrameFlipped(Vec2<int> cellPos, double duration) override;

        void Update(double deltaTime);
        void ForceDestroy() override;

        ~TextureAnimationProcessor();

        ITextureAnimationGraphProperty *SetFrameLoopEndless(bool isEndless) override;

    private:
        WeakPtr<TextureAnimationProcessor> m_SelfWeakPtr{};
        unique_ptr<textureAnimation::AnimationBase> m_AnimationProcess{};
        WeakPtr<SpriteTexture> m_TargetTexture;
        IChildrenPool <TextureAnimationProcessor> * m_ParentalPool;
        double m_CountTime = 0;

        bool m_IsImmediatelyStepToNext = false;
        bool m_IsTriggered = false;
        WeakPtr<TextureAnimationProcessor> m_BeforeAnimation{};
        WeakPtr<TextureAnimationProcessor> m_NextAnimation{};

        void trigger();
        void stepToNextAnimation();
    };
}


#endif //FILL_TILES_TEXTUREANIMATIONPROCESSOR_H
