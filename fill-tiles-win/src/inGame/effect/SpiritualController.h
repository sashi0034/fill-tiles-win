//
// Created by sashi0034 on 2022/09/06.
//

#ifndef FILL_TILES_SPIRITUALCONTROLLER_H
#define FILL_TILES_SPIRITUALCONTROLLER_H

#include "../MainScene.h"
#include "../EffectManager.h"
#include "./SpiritualElement.h"
#include "../IntCounter.h"

namespace inGame::effect
{

    class SpiritualController : public ActorBase
    {
    public:
        static void Produce(EffectManager* effectManager);
        void Update(IAppState *appState) override;
        IChildrenPool<SpiritualElementBase>* GetSpiritualList();
        void RemoveElement(SpiritualElement *element);
    private:
        explicit SpiritualController(EffectManager *effectManager);
        ProcessTimer _process;
        ChildrenPool<SpiritualElementBase> _spiritList{};
        int _time=0;
        IntCounter _elementCount{};
        ProcessTimer initProcess(EffectManager *effectManager);
        void checkCreateSpiritual(EffectManager *effectManager);
        void appendElement(EffectManager *effectManager);
    };

} // inGame

#endif //FILL_TILES_SPIRITUALCONTROLLER_H
