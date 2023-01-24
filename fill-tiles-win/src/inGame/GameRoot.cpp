//
// Created by sashi0034 on 2022/05/23.
//

#include "GameRoot.h"

#include <memory>
#include "MainScene.h"
#include "../debug.h"
#include "title/MenuScene.h"

namespace inGame{
    GameRoot::GameRoot(IAppState *appState)
    : RscImage(std::make_unique<resource::Image>(appState)),
      RscFont(std::make_unique<resource::Font>(appState)),
      m_AppState(appState)
    {
        createSelfSpr();

#ifdef INGAME_DEBUG_MAINSCENE
        m_ChildrenPool.Birth(new MainScene(&m_ChildrenPool, this, MainSceneResetInfo::FromLevel(1)));
#else
        m_ChildrenPool.Birth(new title::MenuScene(&m_ChildrenPool, this));
#endif
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
}


