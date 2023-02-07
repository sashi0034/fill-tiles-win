//
// Created by sashi0034 on 2022/05/28.
//

#ifndef FILL_TILES_ANIMTEST_H
#define FILL_TILES_ANIMTEST_H

#include "ActorBase.h"

using namespace boost::coroutines2;

namespace myGame
{
    class AnimTest final : public ActorBase
    {
    public:
        explicit AnimTest(IChildrenPool<ActorBase> *belonging);

        void Update(IAppState *appState) override;

    private:
        Vec2<double> m_Pos{};
        shared_ptr<SpriteTexture> m_Texture;
        Graph *m_Image;
        coroutine<CoroTask>::pull_type m_Action;

        static CoroTask wait(coroutine<CoroTask>::push_type &yield, AnimTest *self);
    };
}


#endif //FILL_TILES_ANIMTEST_H
