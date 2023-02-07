//
// Created by sashi0034 on 2022/08/31.
//

#ifndef FILL_TILES_FIELDVIEWTEST_H
#define FILL_TILES_FIELDVIEWTEST_H

#include "../GameRoot.h"

namespace myGame
{
    class MainScene;
}

namespace myGame::test
{
    class FieldViewTest : public ActorBase
    {
    public:
        explicit FieldViewTest(MainScene *mainScene, IChildrenPool<ActorBase> *parentPool);
        void Update(IAppState *appState) override;
    private:
        void scrollByMouse(const IAppState *appState);
        void invalidatePlayerScroll();

        MainScene* sceneRef;
        Vec2<double> m_PosOnClicked{};
        bool m_IsClickedBefore = false;
        DirChangeDetector m_DirChangeDetector;
        std::unique_ptr<ProcessTimer> m_ProcessUntilFileChanged{};

    };

} // myGame

#endif //FILL_TILES_FIELDVIEWTEST_H
