//
// Created by sashi0034 on 2022/08/25.
//

#ifndef FILL_TILES_STAGECONTAINER_H
#define FILL_TILES_STAGECONTAINER_H

#include "./StageView.h"
#include "StageClearInfoView.h"
#include "../pixel.h"
#include "./PlusMinusSign.h"


namespace myGame::title
{


    class StageContainer : public ActorBase
    {
    public:
        explicit StageContainer(MenuScene *sceneRef);
        void Update(IAppState *appState) override;
    private:
        MenuScene* const _sceneRef;
        std::vector<unique_ptr<StageView>> _viewList;
        unique_ptr<StageClearInfoView> _infoView;
        SpriteTexture _emptySpr = SpriteTexture::Create();
        int _currStageIndex = 0;
        int _maxStageIndex{};
        static constexpr int viewOffsetX = 880 / pixel::PixelPerUnit;

        bool createNewView(int index, MenuScene *const sceneRef, const std::string &imageDir);
        void controlByInputAsync(CoroTaskYield& yield);
        void scrollStageAsync(CoroTaskYield& yield, PlusMinusSign inputSign);
    };

} // myGame

#endif //FILL_TILES_STAGECONTAINER_H
