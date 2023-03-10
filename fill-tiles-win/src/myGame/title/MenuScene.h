//
// Created by sashi0034 on 2022/08/25.
//

#ifndef FILL_TILES_MENUSCENE_H
#define FILL_TILES_MENUSCENE_H

#include "../ActorBase.h"

namespace myGame{
    class GameRoot;
}

namespace myGame::title
{
    class MenuSelectedInfo
    {
    public:
        bool IsSelected() const;
        int GetSelectedIndex() const;
        MenuSelectedInfo& ConfirmSelect(int index);
    private:
        bool _isSelected;
        int _selectedIndex;
    };


    class MenuScene: public ActorBase
    {
    public:
        MenuScene(IChildrenPool<ActorBase> *parent, GameRoot *root);
        void Update(IAppState* appState) override;
        ICoroutineManager* GetCoroutine();
        IChildrenPool<ActorBase>* GetChildren();
        ITextureAnimator* GetAnimator();
        GameRoot* const RootRef;

        MenuSelectedInfo& GetInfo();
    private:
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        CoroutineManager m_Coroutine{};

        MenuSelectedInfo m_SelectedInfo{};
    };

} // myGame

#endif //FILL_TILES_MENUSCENE_H
