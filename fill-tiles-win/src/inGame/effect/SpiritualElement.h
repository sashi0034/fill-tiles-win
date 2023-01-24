//
// Created by sashi0034 on 2022/09/06.
//

#ifndef FILL_TILES_SPIRITUALELEMENT_H
#define FILL_TILES_SPIRITUALELEMENT_H

#include "../MainScene.h"
#include "../EffectManager.h"
#include "../pixel.h"

namespace inGame::effect
{
    class SpiritualController;

    class SpiritualElementBase
    {
    public:
        virtual void UpdateFixed(){}
        virtual ~SpiritualElementBase() = default;
    };


    class SpiritualElement : public SpiritualElementBase
    {
    public:
        explicit SpiritualElement(SpiritualController *controller, IAppState *app, EffectManager *effectManager);
        void UpdateFixed() override;
    private:
        static const inline Vec2<int> imageSize{64, 64};
        static const inline Vec2<double> imageOriginTerm = (imageSize / 2 / pixel::PixelPerUnit * -1).CastTo<double>();

        SpiritualController* const _parent;
        IAppState* const _app;
        EffectManager* const _effectManager;
        SpriteTexture _texture = SpriteTexture::Create();
        Vec2<double> _pos{};
        Vec2<double> _vel{};
        Vec2<double> _accel{};
        int _animCount{};
        int _remainingLife = 1;
        const bool _canSplit = determineCanSplitRandomly();

        void initTexture(EffectManager *effectManager);
        static bool determineCanSplitRandomly();
        void initCoordinate(const IAppState *app, const EffectManager *effectManager);
        void updateTexture();
        void resetAccel();
        void updateCoordinate();
        void resetPos(const IAppState *app, const EffectManager *effectManager);
        bool checkDie(const Vec2<double> &globalPos, const Vec2<double> &minPos, const Vec2<double> &maxPos);
        void checkCreateSplitAfterImage();
    };

} // inGame

#endif //FILL_TILES_SPIRITUALELEMENT_H
