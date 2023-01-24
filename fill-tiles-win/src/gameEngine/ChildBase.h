//
// Created by sashi0034 on 2022/05/23.
//

#ifndef FILL_TILES_CHILDBASE_H
#define FILL_TILES_CHILDBASE_H

#include "WeakPtr.h"
#include "ChildrenPool.h"

namespace gameEngine
{
    template <typename T>
    class ChildBase
    {
        DEF_WEAK_CONTROLLER(ChildBase);
    private:
        IChildrenPool<T>* m_BelongingPool{};
    public:
        explicit ChildBase(IChildrenPool<T>* belongingPool) : m_BelongingPool(belongingPool){};
        virtual ~ChildBase() = default;
    protected:
        [[nodiscard]] IChildrenPool<T>* getBelongingPool() const{
            return m_BelongingPool;
        }
    };
}


#endif //FILL_TILES_CHILDBASE_H
