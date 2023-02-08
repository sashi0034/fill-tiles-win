#pragma once
#include "ActorBase.h"
#include "TextPassage.h"

namespace myGame {
    class GameRoot;

    class DebugMetaInfoView : public ActorBase
    {
    public:
        DebugMetaInfoView(GameRoot* root);
        void Update(IAppState* app) override;
    private:
        TextPassage initTextPassage(GameRoot* root) const;
        TextPassage m_TextPassage;
        std::string m_TextOld{};
        Time m_Time{};
    };
}
