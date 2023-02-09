//
// Created by sashi0034 on 2022/09/20.
//

#ifndef FILL_TILES_STAGECLEAREVENT_H
#define FILL_TILES_STAGECLEAREVENT_H

#include "MainScene.h"
#include "NinePatchImage.h"
#include "TextPassage.h"

namespace myGame
{
    struct StageClearEventArgs
    {
        MainScene* const SceneRef;

        GameRoot* GetRoot() const;
        TextureAnimator* GetAnimator() const;
        CoroutineManager* GetCoroutineManager() const;
        int GetClearedStep() const;
        int GetClearedTime() const;
    };

    class StageClearEvent
    {
    public:
        static void Start(const StageClearEventArgs& args);
    private:
        static void startEvent(CoroTaskYield &yield, StageClearEventArgs args);

        static void setupClearLabel(const StageClearEventArgs &args, SpriteTexture &labelClear, double animationDuration);

        static unique_ptr<NinePatchImage> createTextBackground(const StageClearEventArgs &args, double animationDuration);

        static unique_ptr<TextPassage> createText(const StageClearEventArgs &args);
    };

} // myGame

#endif //FILL_TILES_STAGECLEAREVENT_H
