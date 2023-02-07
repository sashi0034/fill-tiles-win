//
// Created by sashi0034 on 2022/05/29.
//

#include "textureAnimation.h"

namespace myUtil::textureAnimator::textureAnimation
{

    bool AnimationBase::UpdateAnimation(double)
    {
        assert(false);
        return false;
    }


    DelayVirtual::DelayVirtual(std::function<void()> process, double delayTime)
            : m_DelayTime(delayTime), m_Process(process)
    {}

    bool DelayVirtual::UpdateAnimation(double deltaSecond)
    {
        if (m_Time > m_DelayTime) return false;

        m_Time += deltaSecond;
        if (m_Time > m_DelayTime)
        {
            m_Process();
            return false;
        }

        return true;
    }


    Position::Position(const WeakPtr<SpriteTexture> &targetTexture, const Vec2<double> &endPos, double endTime)
            : m_Texture(targetTexture), m_Easer(TextureAnimationEaser(targetTexture, endTime))
    {
        m_EndPos = endPos;
    }

    void Position::Start()
    {
        if (auto texture = m_Texture.GetPtr())
            m_StartPos = texture->GetPosition();
    }

    bool Position::UpdateAnimation(double deltaSecond)
    {
        m_Easer.Update(deltaSecond);
        if (auto texture = m_Texture.GetPtr())
        {
            auto pos = m_Easer.CalcProgressValue<Vec2<double>>(m_StartPos, m_EndPos);
            texture->SetPosition(pos);
        }
        return !m_Easer.IsDead();
    }

    TextureAnimationEaser *Position::GetEaser()
    {
        return &m_Easer;
    }

    Rotation::Rotation(const WeakPtr<SpriteTexture> &targetTexture, double endDeg, double endTime)
            : m_Texture(targetTexture), m_Easer(TextureAnimationEaser(targetTexture, endTime))
    {
        m_EndDeg = endDeg;
    }

    void Rotation::Start()
    {
        if (auto texture = m_Texture.GetPtr())
            m_StartDeg = texture->GetRotationDeg();
    }

    bool Rotation::UpdateAnimation(double deltaSecond)
    {
        m_Easer.Update(deltaSecond);
        if (auto texture = m_Texture.GetPtr())
            texture->SetRotationDeg(m_Easer.CalcProgressValue<double>(m_StartDeg, m_EndDeg));
        return !m_Easer.IsDead();
    }

    TextureAnimationEaser *Rotation::GetEaser()
    {
        return &m_Easer;
    }

    Scale::Scale(const WeakPtr<SpriteTexture> &targetTexture, const Vec2<double> &endScale, double endTime)
            : m_Texture(targetTexture), m_Easer(TextureAnimationEaser(targetTexture, endTime))
    {
        m_EndScale = endScale;
    }

    void Scale::Start()
    {
        if (auto texture = m_Texture.GetPtr())
            m_StartScale = texture->GetScale();
    }

    bool Scale::UpdateAnimation(double deltaSecond)
    {
        m_Easer.Update(deltaSecond);
        if (auto texture = m_Texture.GetPtr())
            texture->SetScale(m_Easer.CalcProgressValue<Vec2<double>>(m_StartScale, m_EndScale));
        return !m_Easer.IsDead();
    }

    TextureAnimationEaser *Scale::GetEaser()
    {
        return &m_Easer;
    }


    Blend::Blend(const WeakPtr<SpriteTexture> &targetTexture, int endBlendPal, double endTime)
            : m_Texture(targetTexture), m_Easer(TextureAnimationEaser(targetTexture, endTime))
    {
        m_EndBlendPal = endBlendPal;
    }

    void Blend::Start()
    {
        if (auto texture = m_Texture.GetPtr())
            m_StartBlend = texture->GetBlend();
    }

    bool Blend::UpdateAnimation(double deltaSecond)
    {
        m_Easer.Update(deltaSecond);
        if (auto texture = m_Texture.GetPtr())
            texture->SetBlend(GraphBlend{
                    m_StartBlend.GetMode(),
                    m_Easer.CalcProgressValue<int>(m_StartBlend.GetPal(), m_EndBlendPal)
            });
        return !m_Easer.IsDead();
    }

    TextureAnimationEaser *Blend::GetEaser()
    {
        return &m_Easer;
    }


    Graph::Graph(const WeakPtr<SpriteTexture> &targetTexture, Vec2<int> cellSize)
        : m_Texture(targetTexture)
    {
        if (!targetTexture.IsNull())
        {
            m_CellSize = cellSize;
            m_LoopMax = 1;
        }
    }


    bool Graph::UpdateAnimation(double deltaSecond)
    {
        if (m_FrameList.empty()) return false;
        if (!m_IsLoopEndless && m_LoopCount >= m_LoopMax) return false;

        if (m_CurrentFrameTime == 0) updateTexture();

        m_CurrentFrameTime += deltaSecond;
        double currFrameTimeMax = m_FrameList[m_CurrentFrameIndex].Duration;
        if (m_CurrentFrameTime >= currFrameTimeMax) stepToNextFrame();

        return true;
    }

    void Graph::SetLoopMax(int loopMax)
    {
        m_LoopMax = loopMax;
    }

    void Graph::SetCellSrcStart(const Vec2<int> &cellSrcStart)
    {
        m_CellSrcStart = cellSrcStart;
    }

    void Graph::SetCanFlip(bool canFlip)
    {
        m_CanFlip = canFlip;
    }

    void Graph::AddFrame(Vec2<int> &cellPos, double duration, bool isFlip)
    {
        assert(!isFlip || (isFlip && m_CanFlip));
        m_FrameList.push_back(FrameElement{cellPos, duration, isFlip});
    }

    void Graph::updateTexture()
    {
        if (auto texture = m_Texture.GetPtr())
        {
            const auto currFrame = m_FrameList[m_CurrentFrameIndex];
            const auto currCellPos = currFrame.CellPos;
            const auto currSrcXY =
                    m_CellSrcStart
                    + Vec2<int>{m_CellSize.X * currCellPos.X, m_CellSize.Y * currCellPos.Y};
            const auto currSrcRect = Rect<int>{currSrcXY.X, currSrcXY.Y, m_CellSize.X, m_CellSize.Y};
            texture->SetSrcRect(currSrcRect);

            if (m_CanFlip) texture->SetFlip(currFrame.IsFlip);
        }
    }

    void Graph::stepToNextFrame()
    {
        m_CurrentFrameTime = 0;
        m_CurrentFrameIndex++;
        const int frameSize = m_FrameList.size();
        if (m_CurrentFrameIndex >= frameSize) stepToNextLoop();
    }

    void Graph::stepToNextLoop()
    {
        m_CurrentFrameIndex = 0;
        m_LoopCount++;
    }

    void Graph::SetLoopEndless(bool isEndless)
    {
        m_IsLoopEndless = isEndless;
    }


}
