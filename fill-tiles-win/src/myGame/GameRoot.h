//
// Created by sashi0034 on 2022/05/23.
//

#ifndef FILL_TILES_GAMEROOT_H
#define FILL_TILES_GAMEROOT_H

#include "ActorBase.h"
#include "resource/Image.h"
#include "resource/Font.h"
#include "LuaEngine.h"
#include "./NineAnchor.h"
#include "GameSaveData.h"

namespace myGame
{
    namespace resource
    {
        class Image;
        class Font;
    }

    class LuaEngine;
    class InterludeCurtain;


    class GameRoot : public Singleton<GameRoot>
    {
    public:
        explicit GameRoot(IAppState* appState);
        ~GameRoot() override;
        const unique_ptr<resource::Image> RscImage;
        const unique_ptr<resource::Font> RscFont;
        IAppState* GetAppState();
        TextureAnimator& GetTextureAnimator();
        LuaEngine* GetLua();
        IChildrenPool<ActorBase>* GetChildren();
        NineAnchor* GetAnchor();
    private:
        SpriteTexture m_Spr = SpriteTexture::Create();
        ChildrenPool<ActorBase> m_ChildrenPool{};
        TextureAnimator m_TextureAnimator{};
        IAppState* m_AppState;
        LuaEngine m_LuaEngine{this};
        CoroutineManager m_Coro{};
        NineAnchor m_Anchor{};
        GameSaveData m_SaveData{};
        void createSelfSpr();
        void processAppFlow(CoroTaskYield& yield);
        void flowMenuScene(CoroTaskYield& yield, InterludeCurtain* intrule);
        void flowMainScene(CoroTaskYield& yield, InterludeCurtain* interlude);
        void testSaveData();
    };
}


#endif //FILL_TILES_GAMEROOT_H
