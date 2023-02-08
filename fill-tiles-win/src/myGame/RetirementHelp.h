#pragma once
#include "ActorBase.h"
#include "TextPassage.h"
#include "MainScene.h"
#include "player/input.h"

namespace myGame {
    class RetirementHelp : public ActorBase
    {
    public:
        RetirementHelp(MainScene* scene, const MainSceneResetInfo& resetInfo);
        void Update(IAppState* app) override;
    private:
        MainScene* m_Scene;

        SpriteTexture m_IconFront = SpriteTexture::Create();
        SpriteTexture m_IconBack = SpriteTexture::Create();

        TextPassage initTextPassage(GameRoot* root) const;
        TextPassage m_TextPassage;

        double m_PushingBackTime{};
        TextureAnimationWeakPtr m_SelfAnim{};
        TextureAnimator* getAnimator();

        void setupOnPushBackButton();
        void hideOnStopPushButton();
    };
}
