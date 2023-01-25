//
// Created by sashi0034 on 2022/09/06.
//

#include "SpiritualElement.h"
#include "SpiritualController.h"
#include "../ZIndex.h"

namespace inGame::effect
{
    class SpiritualElementAfterImage : public SpiritualElementBase
    {
    private:
        SpriteTexture _texture = SpriteTexture::Create();
        SpiritualController* const _controller;
        int _time = 0;
    public:
        explicit SpiritualElementAfterImage(SpriteTexture& baseElement, SpiritualController* controller) :
            _controller(controller)
        {
            _texture.CopyVisuallyFrom(baseElement);
            _texture.SetRenderingProcess([this](auto&& app){renderingProcess::RenderSpriteDotByDot(app, &_texture); });
        }

        void UpdateFixed() override
        {
            _time++;

            constexpr int lifeTime = 60;

            constexpr int updateInterval = 6;

            if (_time % updateInterval != 0) return;
            _texture.SetBlend(GraphBlend(_texture.GetBlend().GetPal() * 0.9));

            if (_time < lifeTime) return;
            _controller->GetSpiritualList()->Destroy(this);
        }
    };


    constexpr double velMax = 20;

    SpiritualElement::SpiritualElement(SpiritualController *controller, IAppState *app, EffectManager *effectManager) :
        _parent(controller),
        _app(app),
        _effectManager(effectManager)
    {
        initCoordinate(app, effectManager);

        initTexture(effectManager);
    }

    void SpiritualElement::initCoordinate(const IAppState *app, const EffectManager *effectManager)
    {
        resetPos(app, effectManager);

        const double velRad = M_PI * Random::Instance->Get(360) / 180.0;
        _vel = Vec2<double>{std::cos(velRad), std::sin(velRad)} * velMax;

        resetAccel();
    }

    void SpiritualElement::resetPos(const IAppState *app, const EffectManager *effectManager)
    {
        const auto screenSize = app->GetScreenSize();
        _pos = Vec2<int>{Random::Instance->Get(screenSize.X), Random::Instance->Get(screenSize.Y)}.CastTo<double>();

        const auto scrollPos = effectManager->GetParentalPos();
        _pos = _pos - scrollPos;
    }

    void SpiritualElement::resetAccel()
    {
        const int accDeg = Random::Instance->Get(360);
        const double accRad = accDeg * M_PI / 180;
        _accel = Vec2<double>{cos(accRad), sin(accRad) } * velMax;
    }

    void SpiritualElement::initTexture(EffectManager *effectManager)
    {
        _texture.SetGraph(effectManager->GetRoot()->RscImage->spirit_64x64.get());
        _texture.SetSrcRect(Rect{Vec2{0, 0}, imageSize});

        constexpr double baseScale = 1.5;
        _texture.SetScale(Vec2<double>{1, 1} * baseScale * 100.0 / (100 + Random::Instance->Get(100)));
        ZIndexEffect(&_texture).SetIndex(0).ApplyZ();
        _texture.SetBlend(GraphBlend(0));
        _texture.SetRenderingProcess([this](auto&& app){renderingProcess::RenderSpriteDotByDot(app, &_texture); });
        effectManager->ApplyParentalPos(_texture);
    }

    bool SpiritualElement::determineCanSplitRandomly()
    {
        int splittable = 30;
        return Random::Instance->Get(100) < splittable;
    }

    void SpiritualElement::UpdateFixed()
    {
        updateTexture();

        checkCreateSplitAfterImage();

        updateCoordinate();

        const auto globalPos = _texture.GetPosition() + _texture.GetParentalGlobalPosition() - imageOriginTerm;
        const auto minPos = imageOriginTerm;
        const auto maxPos = _app->GetScreenSize().CastTo<double>() - imageOriginTerm;

        bool isDie = checkDie(globalPos, minPos, maxPos);
        if (isDie) return;

        _animCount++;
    }

    bool
    SpiritualElement::checkDie(const Vec2<double> &globalPos, const Vec2<double> &minPos,
                               const Vec2<double> &maxPos)
    {
        // 画面外に出て、ライフが0なら削除
        if (
                !Range<double>(minPos.X, maxPos.X).IsBetween(globalPos.X) ||
                !Range<double>(minPos.Y, maxPos.Y).IsBetween(globalPos.Y))
        {
            _remainingLife--;
            if (_remainingLife <= 0)
            {
                _parent->RemoveElement(this);
                return true;
            }
            _animCount = 0;
            resetPos(_app, _effectManager);
        }
        return false;
    }

    void SpiritualElement::updateCoordinate()
    {
        constexpr double delta = 1.0 / 60;

        _vel = _vel + _accel * delta;
        if (_vel.CalcMagnitude() > velMax * velMax)
        {
            constexpr double resistance = 0.9;
            _vel = _vel * resistance;
            resetAccel();
        }
        _pos = _pos + _vel * delta;
    }

    void SpiritualElement::updateTexture()
    {
        constexpr double blendSpeed = 2.0;
        const double blendPhaseDeg =_animCount * blendSpeed;
        const double blendPhaseRad = blendPhaseDeg * M_PI / 180.0;
        _texture.SetBlend(GraphBlend(int(100.0 - 100.0 * std::cos(blendPhaseRad))));
        _texture.SetRotationDeg(blendPhaseDeg);
        _texture.SetPosition(_pos + imageOriginTerm);
    }

    void SpiritualElement::checkCreateSplitAfterImage()
    {
        if (!_canSplit) return;
        constexpr int animDuration = 12;
        if ((_animCount % animDuration) != 0) return;

        _parent->GetSpiritualList()->Birth(new SpiritualElementAfterImage(_texture, _parent));
    }



} // inGame
