//
// Created by sashi0034 on 2022/09/06.
//

#include "SpiritualController.h"

namespace inGame::effect
{

    void SpiritualController::Produce(EffectManager *effectManager)
    {
        effectManager->GetChildren()->Birth(new SpiritualController(effectManager));
    }

    SpiritualController::SpiritualController(EffectManager *effectManager) :
            ActorBase(effectManager->GetChildren()),
            _process(initProcess(effectManager))
    {}

    void SpiritualController::Update(IAppState *appState)
    {
        _process.Update(appState->GetTime().GetDeltaSec());
    }

    ProcessTimer SpiritualController::initProcess(EffectManager *effectManager)
    {
        return {[this, effectManager](){
            _time++;
            checkCreateSpiritual(effectManager);
            _spiritList.ProcessEach([](SpiritualElementBase& element){element.UpdateFixed(); });
            return EProcessStatus::Running;
        }, 1.0 / 60};
    }

    IChildrenPool<SpiritualElementBase>* SpiritualController::GetSpiritualList()
    {
        return &_spiritList;
    }

    void SpiritualController::checkCreateSpiritual(EffectManager *effectManager)
    {
        constexpr int duration = 6;
        if (_time%duration < 0) return;

        const int maxSpiritual = 16;
        if (_elementCount.GetCount() > maxSpiritual) return;

        appendElement(effectManager);
    }

    void SpiritualController::appendElement(EffectManager *const effectManager)
    {
        _elementCount.IncreaseCount();
        _spiritList.Birth(
                new SpiritualElement(this, effectManager->GetRoot()->GetAppState(), effectManager));
    }

    void SpiritualController::RemoveElement(SpiritualElement *element)
    {
        _elementCount.DecreaseCount();
        _spiritList.Destroy(element);
    }



} // inGame