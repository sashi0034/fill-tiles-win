//
// Created by sashi0034 on 2022/05/23.
//

#include "GameRoot.h"

#include <memory>
#include "MainScene.h"
#include "../debug.h"
#include "title/MenuScene.h"
#include "InterludeCurtain.h"
#include "DebugMetaInfoView.h"

namespace myGame{
    GameRoot::GameRoot(IAppState *appState)
    : RscImage(std::make_unique<resource::Image>(appState)),
      RscFont(std::make_unique<resource::Font>(appState)),
      m_AppState(appState)
    {
        createSelfSpr();
        m_Coro.Start([this](CoroTaskYield& yield) { processAppFlow(yield); });
    }

    GameRoot::~GameRoot()
    {
        m_ChildrenPool.Release();
    }

    void GameRoot::createSelfSpr()
    {
        m_Spr.SetUpdateProcess([&](IAppState* app){
            m_ChildrenPool.ProcessEach([&](ActorBase& child){ child.Update(app);});
            m_TextureAnimator.Update(app->GetTime().GetDeltaSec());
            m_Coro.UpdateEach();
        });
    }

    TextureAnimator &GameRoot::GetTextureAnimator()
    {
        return m_TextureAnimator;
    }

    IAppState *GameRoot::GetAppState()
    {
        return m_AppState;
    }

    LuaEngine *GameRoot::GetLua()
    {
        return &m_LuaEngine;
    }

    IChildrenPool<ActorBase>* GameRoot::GetChildren()
    {
        return &m_ChildrenPool;
    }

    NineAnchor* GameRoot::GetAnchor()
    {
        return &m_Anchor;
    }

    void GameRoot::processAppFlow(CoroTaskYield& yield)
    {
#ifdef MYGAME_DEBUG
        m_ChildrenPool.Birth(new DebugMetaInfoView(this));
#endif
        auto&& interlude = m_ChildrenPool.BirthAs<InterludeCurtain>(new InterludeCurtain(this));

#ifdef MYGAME_DEBUG_MAINSCENE
        flowMainScene(yield, interlude);
#endif

        while (true) {
            flowMenuScene(yield, interlude);

            flowMainScene(yield, interlude);
        }
    }

    void GameRoot::flowMenuScene(myUtil::CoroTaskYield& yield, InterludeCurtain* interlude)
    {
        interlude->StartOpen();

        auto title = m_ChildrenPool.BirthAs<title::MenuScene>(new title::MenuScene(&m_ChildrenPool, this));

        while (title->GetInfo().IsSelected() == false) { yield(); }

        interlude->WaitProcessClose(yield);

        m_ChildrenPool.Destroy(title);
    }

    void GameRoot::flowMainScene(myUtil::CoroTaskYield& yield, InterludeCurtain* interlude)
    {
        interlude->StartOpen();

        auto&& mainScene = m_ChildrenPool.BirthAs<MainScene>(new MainScene(&m_ChildrenPool, this, MainSceneResetInfo::FromLevel(1)));

        while (mainScene->IsFinished() == false) { yield(); }

        interlude->WaitProcessClose(yield);

        m_ChildrenPool.Destroy(mainScene);
    }

}


