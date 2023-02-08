//
// Created by sashi0034 on 2022/06/12.
//

#ifndef FILL_TILES_MAINSCENE_H
#define FILL_TILES_MAINSCENE_H

#include "ActorBase.h"
#include "../myUtil/ChildBase.h"
#include "resource/Image.h"
#include "field/TileMap.h"
#include "FieldManager.h"
#include "ScrollManager.h"
#include "FieldEventManager.h"
#include "EffectManager.h"
#include "../debug.h"

namespace myGame
{
    class GameRoot;
    class Player;
    class MainScene;

    struct MainSceneResetInfo
    {
        int InitialLevel{};
        Vec2<double> ScrollPos{};
        int PassedStetppedCount{};

        static MainSceneResetInfo FromLevel(int level);
        MainSceneResetInfo& WriteCurrSceneInfo(MainScene* scene);
        bool IsFirstTry() const;
    };

    class MainScene: public ActorBase
    {
    public:
        explicit MainScene(IChildrenPool<ActorBase> *parent, GameRoot *root, const MainSceneResetInfo &resetInfo);
        ~MainScene();

        Player* GetPlayer();
        TextureAnimator& GetTextureAnimator();
        void Update(IAppState* appState) override;
        GameRoot *GetRoot();
        FieldManager* GetFieldManager();
        ScrollManager *GetScrollManager();
        FieldEventManager *GetFieldEventManager();
        EffectManager* GetEffectManager();
        ChildrenPool<ActorBase>* GetChildren();
        void RequestResetScene(MainSceneResetInfo resetInfo);

        void FinishScene();
        bool IsFinished() const;
        int GetLevelOnRestart() const;
        int GetPassedMilliSec() const;
    private:
        void initAfterBirth();
        void constructInternal(const myGame::MainSceneResetInfo& resetInfo);
        void resetScene();

        GameRoot* m_Root;
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        FieldManager* m_FieldManager{};
        Player* m_Player;
        FieldEventManager m_FieldEventManager{};
        unique_ptr<ScrollManager> m_ScrollManager{};
        EffectManager* m_EffectManager;

        unique_ptr<MainSceneResetInfo> m_NextResetInfo{};

        bool m_IsFinished = false;
        int m_LevelOnRestart{};
        int m_PassedMilliSec{};
    };
}


#endif //FILL_TILES_MAINSCENE_H
