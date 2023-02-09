//
// Created by sashi0034 on 2022/08/25.
//

#include "MenuScene.h"
#include "TitleBackground.h"
#include "./StageContainer.h"

namespace myGame::title
{
    MenuScene::MenuScene(IChildrenPool<ActorBase> *parent, GameRoot *root) :
            ActorBase(parent),
            RootRef(root)
    {
        m_ChildrenPool.Birth(new TitleBackground(this));

        m_ChildrenPool.Birth(new StageContainer(this));

        m_ChildrenPool.ProcessEach([&](auto& child){ child.Init();});
    }

    void MenuScene::Update(IAppState *appState)
    {
        m_ChildrenPool.ProcessEach([&](auto& child){ child.Update(appState);});
        m_Coroutine.UpdateEach();
        m_TextureAnimator.Update(appState->GetTime().GetDeltaSec());
    }

    ICoroutineManager *MenuScene::GetCoroutine()
    {
        return &m_Coroutine;
    }

    IChildrenPool<ActorBase> *MenuScene::GetChildren()
    {
        return &m_ChildrenPool;
    }

    ITextureAnimator *MenuScene::GetAnimator()
    {
        return &m_TextureAnimator;
    }
    MenuSelectedInfo& MenuScene::GetInfo()
    {
        return m_SelectedInfo;
    }
    bool MenuSelectedInfo::IsSelected() const
    {
        return _isSelected;
    }
    int MenuSelectedInfo::GetSelectedIndex() const
    {
        return _selectedIndex;
    }
    MenuSelectedInfo& MenuSelectedInfo::ConfirmSelect(int index)
    {
        _isSelected = true;
        _selectedIndex = index;
        return *this;
    }
} // myGame
