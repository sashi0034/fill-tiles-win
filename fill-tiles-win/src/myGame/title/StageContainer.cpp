//
// Created by sashi0034 on 2022/08/25.
//

#include "StageContainer.h"
#include "../GameRoot.h"
#include "../player/input.h"

namespace myGame::title
{
    StageContainer::StageContainer(MenuScene *sceneRef) :
            ActorBase(sceneRef->GetChildren()),
            _sceneRef(sceneRef)
    {
        const std::string imageDir = "./assets/images/screenshots/";

        _emptySpr.SetPositionParent(sceneRef->RootRef->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Middle));

        for (int i=1; i<=99; ++i)
        {
            bool hasCreated = createNewView(i, sceneRef, imageDir);
            if (hasCreated) continue;
            _maxStageIndex = i-1;
            break;
        }

        _infoView = std::make_unique<StageClearInfoView>(StageClearInfoViewArgs{
            sceneRef
        });

        sceneRef->GetCoroutine()->Start([this](auto&& yield){ controlByInputAsync(yield);});
    }

    int StageContainer::getCurrStageIndex() const
    {
        return _currCursorIndex + 1;
    }

    bool StageContainer::createNewView(int index, MenuScene *const sceneRef, const std::string &imageDir)
    {
        std::stringstream screenshotPath{};
        std::stringstream stageIndexText{};
        stageIndexText << index / 10 << index % 10;
        screenshotPath << imageDir << "field_" << stageIndexText.str() << ".png";

        if (!std::filesystem::exists(screenshotPath.str())) return false;

        _viewList.emplace_back(std::make_unique<StageView>(StageViewArgs{
                index,
                sceneRef,
                _emptySpr,
                Vec2<double>((index - 1) * viewOffsetX, 0),
                screenshotPath.str()
        }));

        return true;
    }

    void StageContainer::Update(IAppState*)
    {}

    void StageContainer::controlByInputAsync(CoroTaskYield &yield)
    {
        auto const app = _sceneRef->RootRef->GetAppState();

        bool isPushedOkBefore = true;
        _infoView->UpdateText(getCurrStageIndex());

        while (true)
        {
            yield();

            if (isPushedOkBefore == false && util::IsPushedOk(app))
            {
                // ステージ決定
                _sceneRef->GetInfo().ConfirmSelect(getCurrStageIndex());
                return;
            }
            isPushedOkBefore = util::IsPushedOk(app);

            auto inputSign = PlusMinusSign::FromHorizontal(player::input::GetInputAngle(app->GetKeyboardState()));
            if (inputSign.HasValue()) scrollStageAsync(yield, inputSign);
        }
    }

    void StageContainer::scrollStageAsync(CoroTaskYield &yield, PlusMinusSign inputSign)
    {
        int oldIndex = _currCursorIndex;
        _currCursorIndex = Range<int>(0, _maxStageIndex).MakeInRange(_currCursorIndex + inputSign.Value);
        if (oldIndex==_currCursorIndex) return;

        constexpr double duration = 0.3;
        auto animation = _sceneRef->GetAnimator()->TargetTo(_emptySpr)
                ->AnimPosition(Vec2<double>{double(-viewOffsetX*_currCursorIndex), 0}, duration)
                ->SetEase(EAnimEase::OutBack)
                ->ToWeakPtr();

        _infoView->UpdateText(-1);

        coroUtil::WaitForExpire(yield, animation);

        _infoView->UpdateText(getCurrStageIndex());
    }



} // myGame
