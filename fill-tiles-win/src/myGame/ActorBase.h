//
// Created by sashi0034 on 2022/06/12.
//

#ifndef FILL_TILES_ACTORBASE_H
#define FILL_TILES_ACTORBASE_H

#include "../myUtil/myUtil.h"
#include "util.h"

namespace myGame
{
    class ActorBase : public ChildBase<ActorBase>
    {
    public:
        explicit ActorBase(IChildrenPool<ActorBase>* parentPool);
        ~ActorBase() override;
        virtual void Init();
        virtual void Update(IAppState* appState);
    private:
        void operator=(const ActorBase &) = delete;
    };
}


#endif //FILL_TILES_ACTORBASE_H
