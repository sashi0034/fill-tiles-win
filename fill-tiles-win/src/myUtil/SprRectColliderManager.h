//
// Created by sashi0034 on 2022/06/18.
//

#ifndef FILL_TILES_SPRRECTCOLLIDERMANAGER_H
#define FILL_TILES_SPRRECTCOLLIDERMANAGER_H

#include "SprRectCollider.h"

namespace myUtil
{

    class SprRectColliderManager
    {
    public:
        SprRectColliderManager();
        void AddCollider(SprRectCollider &collider);
        bool IsHitWith(const Rect<double> &checkingRect, ISprRectColliderOwner **ownerOut = nullptr);
        bool IsHitWith(const Vec2<double> &checkingPoint, ISprRectColliderOwner **ownerOut = nullptr);
    private:
        std::vector<WeakPtr<SprRectCollider>> m_ColliderList;
        void collectGarbage(const std::vector<int>& upwardIndexes);
        template <typename T>
        bool isHitWith(const T &checkingOther, ISprRectColliderOwner **ownerOut);
    };

}


#endif //FILL_TILES_SPRRECTCOLLIDERMANAGER_H
