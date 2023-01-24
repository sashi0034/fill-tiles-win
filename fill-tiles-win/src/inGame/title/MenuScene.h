//
// Created by sashi0034 on 2022/08/25.
//

#ifndef FILL_TILES_MENUSCENE_H
#define FILL_TILES_MENUSCENE_H

#include "../ActorBase.h"

namespace inGame{
    class GameRoot;
}

namespace inGame::title
{

    class MenuScene: public ActorBase
    {
    public:
        MenuScene(IChildrenPool<ActorBase> *parent, GameRoot *root);
        void Update(IAppState* appState) override;
        ICoroutineManager* GetCoroutine();
        IChildrenPool<ActorBase>* GetChildren();
        ITextureAnimator* GetAnimator();
        GameRoot* const RootRef;
    private:
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        CoroutineManager m_Coroutine{};
    };

} // inGame

#endif //FILL_TILES_MENUSCENE_H
