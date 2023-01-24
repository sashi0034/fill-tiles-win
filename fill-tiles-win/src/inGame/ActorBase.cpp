//
// Created by sashi0034 on 2022/06/12.
//

#include "ActorBase.h"

namespace inGame{
    ActorBase::ActorBase(IChildrenPool<ActorBase> *parentPool) : ChildBase<ActorBase>(parentPool)
    {}

    void ActorBase::Update(IAppState *appState)
    {
        (void)appState;
    }

    void ActorBase::Init()
    {}

    ActorBase::~ActorBase()
    = default;
}
