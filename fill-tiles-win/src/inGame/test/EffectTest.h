//
// Created by sashi0034 on 2022/08/03.
//

#ifndef FILL_TILES_EFFECTTEST_H
#define FILL_TILES_EFFECTTEST_H

#include "../ActorBase.h"
#include "../LuaEngine.h"


namespace inGame
{
    class IMainScene;
}

namespace inGame::test
{

    class EffectTest : public ActorBase
    {
    public:
        explicit EffectTest(IMainScene *sceneRef, IChildrenPool<ActorBase> *children);

        void Update(IAppState *appState) override;

    private:
        IMainScene* m_SceneRef;
        DirChangeDetector m_FileChangeDetector;
        ProcessTimer m_Timer = initProcessTimer();
        ProcessTimer initProcessTimer();

        void processHotReload(inGame::LuaEngine *const lua);
    };

} // gameEngine

#endif //FILL_TILES_EFFECTTEST_H
