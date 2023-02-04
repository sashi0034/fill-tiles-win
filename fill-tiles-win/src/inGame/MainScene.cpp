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

namespace inGame{
    MainScene::MainScene(IChildrenPool<ActorBase> *parent, GameRoot *root, const MainSceneResetInfo &resetInfo):
            ActorBase(parent),
            InitialLevel(resetInfo.InitialLevel),
            m_Root(root)
    {
        m_ScrollManager = std::make_unique<ScrollManager>(this);

        m_FieldManager = m_ChildrenPool.BirthAs<FieldManager>(new FieldManager(&m_ChildrenPool, this));

        m_Player = m_ChildrenPool.BirthAs<Player>(new Player(&m_ChildrenPool, this));

        m_EffectManager = m_ChildrenPool.BirthAs<EffectManager>(new EffectManager(&m_ChildrenPool,
                                                                                  m_ScrollManager->GetSprite()->GetWeakPtr(),
                                                                                  m_Root));
        m_ChildrenPool.Birth(new RemainingMineUi(this, m_FieldManager->GetMineFlowerManager()));

#ifdef INGAME_DEBUG_EFFECTTEST
        m_ChildrenPool.Birth(new test::EffectTest(this, &m_ChildrenPool));
#endif
#ifdef INGAME_DEBUG_FIELDVIEW
        m_ChildrenPool.Birth(new test::FieldViewTest(this, &m_ChildrenPool));
#endif
        effect::SpiritualController::Produce(m_EffectManager);

        m_ScrollManager->SetScroll(resetInfo.ScrollPos);

        initAfterBirth();
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

#ifdef INGAME_DEBUG_IMMEDIATE_CLEAREVENT
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

    void MainScene::RequestResetScene(MainSceneResetInfo resetInfo)
    {
        m_NextResetInfo = unique_ptr<MainSceneResetInfo>(new MainSceneResetInfo(resetInfo));
    }

    void MainScene::resetScene()
    {
        auto const gameRoot = m_Root;
        auto const resetInfo = std::move(m_NextResetInfo);
        gameRoot->GetChildren()->Destroy(this);
        gameRoot->GetChildren()->Birth(new MainScene(gameRoot->GetChildren(), gameRoot, *resetInfo));
    }

    MainSceneResetInfo MainSceneResetInfo::FromLevel(int level)
    {
        return MainSceneResetInfo{level, Vec2{0.0, 0.0}};
    }
}


