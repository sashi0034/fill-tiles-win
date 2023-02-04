//
// Created by sashi0034 on 2022/08/03.
//

#include "EffectTest.h"
#include "../MainScene.h"
#include "../effect/BurningFire.h"
#include "../Player.h"
#include "../effect/GeoExplosion.h"
#include "../effect/SakuraFormation.h"

namespace inGame::test
{
    EffectTest::EffectTest(MainScene *sceneRef, IChildrenPool<ActorBase> *children)
    : ActorBase(children),
    m_SceneRef(sceneRef),
    m_FileChangeDetector("assets/lua")
    {}

    void EffectTest::Update(IAppState *appState)
    {
        m_Timer.Update(appState->GetTime().GetDeltaSec());
    }

    ProcessTimer EffectTest::initProcessTimer()
    {
        return  ProcessTimer([&](){
            const auto lua = m_SceneRef->GetRoot()->GetLua();

            if (m_FileChangeDetector.CheckChanged())
                processHotReload(lua);

            return EProcessStatus::Running;
        }, 0.5);
    }

    void EffectTest::processHotReload(LuaEngine *const lua)
    {
        lua->ReloadAllFiles();

        const std::string testStr = lua->GetState()["Test"]();
        std::cout << testStr << std::endl;

//        effect::GeoExplosion::Produce(
//                m_SceneRef->GetEffectManager(),
//                m_SceneRef->GetPlayer()->GetPos() + FieldManager::MatPixelSize.CastTo<double>() / 2.0);

        effect::SakuraFormation::Produce(
                m_SceneRef->GetEffectManager(),
                m_SceneRef->GetPlayer()->GetPos() + FieldManager::MatPixelSize.CastTo<double>() / 2.0);
    }
} // inGame