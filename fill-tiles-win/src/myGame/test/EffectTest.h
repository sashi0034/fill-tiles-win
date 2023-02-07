//
// Created by sashi0034 on 2022/08/03.
//

#ifndef FILL_TILES_EFFECTTEST_H
#define FILL_TILES_EFFECTTEST_H

#include "../ActorBase.h"
#include "../LuaEngine.h"


namespace myGame
{
    class MainScene;
}

namespace myGame::test
{

    class EffectTest : public ActorBase
    {
    public:
        explicit EffectTest(MainScene *sceneRef, IChildrenPool<ActorBase> *children);

        void Update(IAppState *appState) override;

    private:
        MainScene* m_SceneRef;
        DirChangeDetector m_FileChangeDetector;
        ProcessTimer m_Timer = initProcessTimer();
        ProcessTimer initProcessTimer();

        void processHotReload(myGame::LuaEngine *const lua);
    };

} // myUtil

#endif //FILL_TILES_EFFECTTEST_H
