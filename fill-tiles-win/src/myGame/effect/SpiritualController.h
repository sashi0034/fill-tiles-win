//
// Created by sashi0034 on 2022/09/06.
//

#ifndef FILL_TILES_SPIRITUALCONTROLLER_H
#define FILL_TILES_SPIRITUALCONTROLLER_H

#include "../MainScene.h"
#include "../EffectManager.h"
#include "./SpiritualElement.h"

namespace myGame::effect
{

    class SpiritualController : public ActorBase
    {
    public:
        static void Produce(EffectManager* effectManager);
        void Update(IAppState *appState) override;
        IChildrenPool<SpiritualElementBase>* GetSpiritualList();
        void RemoveElement(SpiritualElement *element);
        SpriteTextureContext* GetSprContext();
    private:
        explicit SpiritualController(EffectManager *effectManager);
        ProcessTimer _process;
        ChildrenPool<SpiritualElementBase> _spiritList{};
        int _time=0;
        IntCounter _elementCount{};

        // 負荷軽減のためにSpiritual専用の低FPSのContextを作成
        SpriteTexture _canvas = SpriteTexture::Create();
        SpriteTextureContext _canvasContext{};

        ProcessTimer initProcess(EffectManager *effectManager);
        void checkCreateSpiritual(EffectManager *effectManager);
        void appendElement(EffectManager *effectManager);
    };

} // myGame

#endif //FILL_TILES_SPIRITUALCONTROLLER_H
