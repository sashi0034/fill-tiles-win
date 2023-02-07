//
// Created by sashi0034 on 2022/05/28.
//

#include "TextureAnimationProcessor.h"

#include <memory>
#include "textureAnimation.h"

namespace myUtil::textureAnimator
{
    TextureAnimationProcessor::TextureAnimationProcessor(const WeakPtr <SpriteTexture> &texture,
                                                         IChildrenPool<TextureAnimationProcessor> *parentalPool,
                                                         WeakPtr<TextureAnimationProcessor> *beforeAnimation)
            : m_TargetTexture(texture), m_ParentalPool(parentalPool)
    {
        if (beforeAnimation == nullptr)
            trigger();
        else
            m_BeforeAnimation = *beforeAnimation;
    }


    void TextureAnimationProcessor::Update(double deltaTime)
    {
        if (!m_IsTriggered) return;

        bool isRunning = false;

        if (m_AnimationProcess != nullptr)
            isRunning = m_AnimationProcess->UpdateAnimation(deltaTime);

        if (!isRunning) stepToNextAnimation();
    }

    void TextureAnimationProcessor::stepToNextAnimation()
    {
        if (auto next = m_NextAnimation.GetPtr())
            next->trigger();

        auto isDestroyed = m_ParentalPool->Destroy(this);
        assert(isDestroyed);
    }

    ITextureAnimationStarter *TextureAnimationProcessor::Then()
    {
        return this;
    }

    ITextureAnimationStarter *TextureAnimationProcessor::With()
    {
        m_IsImmediatelyStepToNext = true;
        return this;
    }

    void TextureAnimationProcessor::trigger()
    {
        m_IsTriggered = true;
        if (m_AnimationProcess!= nullptr) m_AnimationProcess->Start();

        if (m_IsImmediatelyStepToNext)
            if (auto next = m_NextAnimation.GetPtr())
                next->trigger();
    }



    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetLoop(int loop)
    {
        auto *animation = dynamic_cast<textureAnimation::EaseAbleAnimationBase *>(m_AnimationProcess.get());
        animation->GetEaser()->SetLoop(loop);
        return this;
    }


    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetEase(myUtil::EAnimEase easeType)
    {
        auto* animation = dynamic_cast<textureAnimation::EaseAbleAnimationBase*>(m_AnimationProcess.get());
        animation->GetEaser()->SetEase(easeType);
        return this;
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::SetRelative(bool isRelative)
    {
        auto* animation = dynamic_cast<textureAnimation::EaseAbleAnimationBase*>(m_AnimationProcess.get());
        animation->GetEaser()->SetRelative(isRelative);
        return this;
    }


    ITextureAnimationLinker *
    TextureAnimationProcessor::DelayVirtual(std::function<void()> process, double delayTime)
    {
        auto nextAnimation = new TextureAnimationProcessor(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::DelayVirtual>(process, delayTime);

        m_ParentalPool->Birth(nextAnimation);
        m_NextAnimation = nextAnimation->GetWeakPtr();
        return static_cast<ITextureAnimationEaseProperty*>(nextAnimation);
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimPosition(Vec2<double> endPos, double duration)
    {
        auto nextAnimation = new TextureAnimationProcessor(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        textureAnimation::AnimationBase* base = new textureAnimation::Position(m_TargetTexture, endPos, duration);
        nextAnimation->m_AnimationProcess = unique_ptr<textureAnimation::AnimationBase>(base);

        m_ParentalPool->Birth(nextAnimation);
        m_NextAnimation = nextAnimation->GetWeakPtr();
        return nextAnimation;
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimRotation(double endDeg, double duration)
    {
        auto nextAnimation = new TextureAnimationProcessor(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Rotation>(
                m_TargetTexture, endDeg, duration);

        m_ParentalPool->Birth(nextAnimation);
        m_NextAnimation = nextAnimation->GetWeakPtr();
        return nextAnimation;
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimScale(const Vec2<double> &endScale, double duration)
    {
        auto nextAnimation =  new TextureAnimationProcessor(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Scale>(
                m_TargetTexture, endScale, duration);

        m_ParentalPool->Birth(nextAnimation);
        m_NextAnimation = nextAnimation->GetWeakPtr();
        return nextAnimation;
    }
    

    TextureAnimationProcessor::~TextureAnimationProcessor()
    = default;

    ITextureAnimationGraphProperty *TextureAnimationProcessor::AnimGraph(Vec2<int> cellSize)
    {
        auto nextAnimation =  new TextureAnimationProcessor(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Graph>(
                m_TargetTexture, cellSize);

        m_ParentalPool->Birth(nextAnimation);
        m_NextAnimation = nextAnimation->GetWeakPtr();
        return nextAnimation;
    }

    ITextureAnimationGraphProperty *TextureAnimationProcessor::SetCellSrcStart(Vec2<int> cellSrcStart)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->SetCellSrcStart(cellSrcStart);
        return this;
    }

    ITextureAnimationGraphProperty *TextureAnimationProcessor::SetCanFlip(bool canFlip)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->SetCanFlip(canFlip);
        return this;
    }


    ITextureAnimationGraph *TextureAnimationProcessor::AddFrame(Vec2<int> cellPos, double duration)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->AddFrame(cellPos, duration, false);
        return this;
    }


    ITextureAnimationGraph *TextureAnimationProcessor::AddFrameFlipped(Vec2<int> cellPos, double duration)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->AddFrame(cellPos, duration, true);
        return this;
    }

    ITextureAnimationGraphProperty *TextureAnimationProcessor::SetFrameLoop(int loop)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->SetLoopMax(loop);
        return this;
    }


    ITextureAnimationGraphProperty *TextureAnimationProcessor::SetFrameLoopEndless(bool isEndless)
    {
        auto* animation = dynamic_cast<textureAnimation::Graph*>(m_AnimationProcess.get());
        animation->SetLoopEndless(isEndless);
        return this;
    }

    void TextureAnimationProcessor::ForceDestroy()
    {
        assert(!m_NextAnimation.IsNull());

        auto isSucceeded = m_ParentalPool->Destroy(this);
        assert(isSucceeded);

        if (auto beforeAnimation = m_BeforeAnimation->GetWeakPtr()) beforeAnimation->ForceDestroy();
    }

    WeakPtr<ITextureAnimationPointer> TextureAnimationProcessor::ToWeakPtr()
    {
        return this->GetWeakPtr().ToUpCasted<ITextureAnimationEaseProperty>().ToUpCasted<ITextureAnimationPointer>();
    }

    ITextureAnimationEaseProperty *TextureAnimationProcessor::AnimBlend(int endBlendPal, double duration)
    {
        auto nextAnimation =  new TextureAnimationProcessor(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::Blend>(
                m_TargetTexture, endBlendPal, duration);

        m_ParentalPool->Birth(nextAnimation);
        m_NextAnimation = nextAnimation->GetWeakPtr();
        return nextAnimation;

    }

    ITextureAnimationEaseProperty* TextureAnimationProcessor::AnimValue(double start, double end, std::function<void(double)> func, double duration)
    {
        auto nextAnimation = new TextureAnimationProcessor(m_TargetTexture, m_ParentalPool, &m_SelfWeakPtr);
        nextAnimation->m_AnimationProcess = std::make_unique<textureAnimation::ValueChange>(
            start, end, func, duration);

        m_ParentalPool->Birth(nextAnimation);
        m_NextAnimation = nextAnimation->GetWeakPtr();
        return nextAnimation;
    }

}


