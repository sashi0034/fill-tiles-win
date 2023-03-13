//
// Created by sashi0034 on 2022/09/06.
//

#include "SpiritualController.h"
#include "../ZIndex.h"

namespace myGame::effect
{

    void SpiritualController::Produce(EffectManager *effectManager, MainScene* mainScene)
    {
        effectManager->GetChildren()->Birth(new SpiritualController(effectManager, mainScene));
    }

    SpiritualController::SpiritualController(EffectManager *effectManager, MainScene* mainScene) :
            ActorBase(effectManager->GetChildren()),
            _process(initProcess(effectManager)),
            m_Scene(mainScene)
    {}

    void SpiritualController::Update(IAppState *appState)
    {
        _process.Update(appState->GetTime().GetDeltaSec());
    }

    ProcessTimer SpiritualController::initProcess(EffectManager *effectManager)
    {
        constexpr int idealFps = 60;
        constexpr int fps = 30;

        return {[this, effectManager](){
            _time++;
            checkCreateSpiritual(effectManager);

            _spiritList.ProcessEach([](SpiritualElementBase& element){element.UpdateFixed(idealFps / fps); });

            return EProcessStatus::Running;
        }, 1.0 / fps};
    }

    IChildrenPool<SpiritualElementBase>* SpiritualController::GetSpiritualList()
    {
        return &_spiritList;
    }

    void SpiritualController::checkCreateSpiritual(EffectManager *effectManager)
    {
        constexpr int duration = 6;
        if (_time%duration < 0) return;

        const int maxSpiritual = 32;
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

    MainScene* const SpiritualController::GetScene()
    {
        return m_Scene;
    }



} // myGame
