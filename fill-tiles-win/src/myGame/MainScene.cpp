//
// Created by sashi0034 on 2022/06/12.
//

#include "MainScene.h"

#include <memory>
#include "Player.h"
#include "AnimTest.h"
#include "GameRoot.h"
#include "RemainingMineUi.h"
#include "./test/EffectTest.h"
#include "../debug.h"
#include "test/FieldViewTest.h"
#include "effect/SpiritualController.h"
#include "StageClearEvent.h"
#include "ScreenSweeper.h"
#include "RetirementHelp.h"

namespace myGame{
    MainScene::MainScene(IChildrenPool<ActorBase> *parent, GameRoot *root, const MainSceneResetInfo &resetInfo):
            ActorBase(parent),
            m_Root(root)
    {
        constructInternal(resetInfo);
    }

    void MainScene::constructInternal(const myGame::MainSceneResetInfo& resetInfo)
    {
        // 解放
        m_ChildrenPool.Release();
        m_TextureAnimator.Release();
        m_ScrollManager.reset();

        // 初期化
        m_LevelOnRestart = resetInfo.InitialLevel;

        m_FieldEventManager = FieldEventManager();

        m_ScrollManager = std::make_unique<ScrollManager>(this);

        m_FieldManager = m_ChildrenPool.BirthAs<FieldManager>(new FieldManager(&m_ChildrenPool, this));

        m_Player = m_ChildrenPool.BirthAs<Player>(new Player(&m_ChildrenPool, this, resetInfo));

        m_EffectManager = m_ChildrenPool.BirthAs<EffectManager>(new EffectManager(&m_ChildrenPool,
            m_ScrollManager->GetSprite()->GetWeakPtr(),
            m_Root));
        m_ChildrenPool.Birth(new RemainingMineUi(this, m_FieldManager->GetMineFlowerManager()));

#ifdef MYGAME_DEBUG_EFFECTTEST
        m_ChildrenPool.Birth(new test::EffectTest(this, &m_ChildrenPool));
#endif
#ifdef MYGAME_DEBUG_FIELDVIEW
        m_ChildrenPool.Birth(new test::FieldViewTest(this, &m_ChildrenPool));
#endif
        effect::SpiritualController::Produce(m_EffectManager);

        m_ScrollManager->SetScroll(resetInfo.ScrollPos);

        m_ChildrenPool.Birth(new RetirementHelp(this, resetInfo));

        initAfterBirth();

        m_Root->GetAppState()->MutTime().Restart();
    }

    MainScene::~MainScene()
    {
        m_ChildrenPool.Release();
    }

    TextureAnimator &MainScene::GetTextureAnimator()
    {
        return m_TextureAnimator;
    }

    void MainScene::Update(IAppState* appState)
    {
        m_ChildrenPool.ProcessEach([&](auto& child){ child.Update(appState);});

        m_TextureAnimator.Update(appState->GetTime().GetDeltaSec());

        m_PassedMilliSec += appState->GetTime().GetDeltaMilli();

        if (m_NextResetInfo.get()!= nullptr) resetScene();
    }

    GameRoot *MainScene::GetRoot()
    {
        return m_Root;
    }

    FieldManager* MainScene::GetFieldManager()
    {
        return m_FieldManager;
    }

    ScrollManager *MainScene::GetScrollManager()
    {
        return m_ScrollManager.get();
    }

    void MainScene::initAfterBirth()
    {
        m_ChildrenPool.ProcessEach([&](auto& child){ child.Init();});

#ifdef MYGAME_DEBUG_IMMEDIATE_CLEAREVENT
        StageClearEvent::Start(StageClearEventArgs{this});
#endif
    }

    Player *MainScene::GetPlayer()
    {
        return m_Player;
    }

    FieldEventManager *MainScene::GetFieldEventManager()
    {
        return &m_FieldEventManager;
    }

    EffectManager *MainScene::GetEffectManager()
    {
        return m_EffectManager;
    }

    ChildrenPool<ActorBase>* MainScene::GetChildren()
    {
        return &m_ChildrenPool;
    }

    void MainScene::RequestResetScene(MainSceneResetInfo resetInfo)
    {
        m_NextResetInfo = unique_ptr<MainSceneResetInfo>(new MainSceneResetInfo(resetInfo));
    }

    void MainScene::FinishScene()
    {
        m_IsFinished = true;
    }

    bool MainScene::IsFinished() const
    {
        return m_IsFinished;
    }

    int MainScene::GetLevelOnRestart() const
    {
        return m_LevelOnRestart;
    }

    int MainScene::GetPassedMilliSec() const
    {
        return m_PassedMilliSec;
    }

    void MainScene::resetScene()
    {
        auto const gameRoot = m_Root;
        auto const resetInfo = std::move(m_NextResetInfo);

        constructInternal(*resetInfo);

        m_ChildrenPool.Birth(new ScreenSweeper(
            &m_ChildrenPool,
            m_Root->GetAppState(),
            &m_TextureAnimator,
            SpriteTextureContext::Global()
        ));
    }

    MainSceneResetInfo MainSceneResetInfo::FromLevel(int level)
    {
        auto result = MainSceneResetInfo{};
        result.InitialLevel = level;
        return result;
    }
    MainSceneResetInfo& MainSceneResetInfo::WriteCurrSceneInfo(MainScene* scene)
    {
        this->PassedStetppedCount = scene->GetPlayer()->GetSteppedCount();
        return *this;
    }
    bool MainSceneResetInfo::IsFirstTry() const
    {
        return PassedStetppedCount == 0;
    }
}


