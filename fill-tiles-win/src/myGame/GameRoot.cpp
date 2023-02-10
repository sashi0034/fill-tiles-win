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

    const char* saveFileName = "save.dat";

    GameRoot::GameRoot(IAppState *appState)
    : RscImage(std::make_unique<resource::Image>(appState)),
      RscFont(std::make_unique<resource::Font>(appState)),
      m_AppState(appState)
    {
        createSelfSpr();

        m_SaveData.ReadData(saveFileName);

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

    const GameSaveData& GameRoot::GetSaveData() const
    {
        return m_SaveData;
    }

    GameSaveData* const GameRoot::MutSaveData()
    {
        return &m_SaveData;
    }

    void GameRoot::WriteSaveData()
    {
        m_SaveData.WriteData(saveFileName);
    }

    void GameRoot::processAppFlow(CoroTaskYield& yield)
    {
#ifdef MYGAME_DEBUG
        m_ChildrenPool.Birth(new DebugMetaInfoView(this));
#endif
        auto&& interlude = m_ChildrenPool.BirthAs<InterludeCurtain>(new InterludeCurtain(this));

#ifdef MYGAME_DEBUG_MAINSCENE
        flowMainScene(yield, interlude, title::MenuSelectedInfo().ConfirmSelect(MYGAME_DEBUG_MAINSCENE));
#endif

        while (true) {
            auto info = flowMenuScene(yield, interlude);

            flowMainScene(yield, interlude, info);
        }
    }

    title::MenuSelectedInfo GameRoot::flowMenuScene(myUtil::CoroTaskYield& yield, InterludeCurtain* interlude)
    {
        interlude->StartOpen();

        auto title = m_ChildrenPool.BirthAs<title::MenuScene>(new title::MenuScene(&m_ChildrenPool, this));

        auto&& info = title->GetInfo();
        while (info.IsSelected() == false) { yield(); }

        interlude->WaitProcessClose(yield);

        auto result = info;
        m_ChildrenPool.Destroy(title);

        return result;
    }

    void GameRoot::flowMainScene(myUtil::CoroTaskYield& yield, InterludeCurtain* interlude, title::MenuSelectedInfo info)
    {
        interlude->StartOpen();

        auto&& mainScene = m_ChildrenPool.BirthAs<MainScene>(
            new MainScene(&m_ChildrenPool, this, MainSceneResetInfo::FromLevel(1), info.GetSelectedIndex()));

        while (mainScene->IsFinished() == false) { yield(); }

        interlude->WaitProcessClose(yield);

        m_ChildrenPool.Destroy(mainScene);
    }

}


