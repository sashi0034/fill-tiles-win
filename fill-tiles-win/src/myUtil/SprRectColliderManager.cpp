//
// Created by sashi0034 on 2022/06/18.
//

#include "SprRectColliderManager.h"
#include "Range.h"
#include "arrayUtil.h"

namespace myUtil
{


    SprRectColliderManager::SprRectColliderManager()
    = default;

    void SprRectColliderManager::AddCollider(SprRectCollider &collider)
    {
        m_ColliderList.push_back(collider.GetWeakPtr());
    }

    bool SprRectColliderManager::IsHitWith(const Rect<double> &checkingRect, ISprRectColliderOwner **ownerOut)
    {
        return isHitWith<Rect<double>>(checkingRect, ownerOut);
    }

    bool SprRectColliderManager::IsHitWith(const Vec2<double> &checkingPoint, ISprRectColliderOwner **ownerOut)
    {
        return isHitWith<Vec2<double>>(checkingPoint, ownerOut);
    }

    template<typename T>
    bool SprRectColliderManager::isHitWith(const T &checkingOther, ISprRectColliderOwner **ownerOut)
    {
        int size = m_ColliderList.size();
        std::vector<int> garbageIndexes{};
        bool result = false;

        for (int i = 0; i < size; ++i)
            if (auto collider = m_ColliderList[i].GetPtr())
            {
                if (collider->IsIntersectWith(checkingOther))
                {
                    result = true;
                    if (ownerOut!= nullptr) *ownerOut = collider->GetOwner();
                }
            }
            else
                garbageIndexes.push_back(i);

        collectGarbage(garbageIndexes);

        return result;
    }

    void SprRectColliderManager::collectGarbage(const std::vector<int> &upwardIndexes)
    {
        for (int i= upwardIndexes.size() - 1; i >= 0; --i)
        {
            int index = upwardIndexes[i];
            m_ColliderList.erase(m_ColliderList.begin() + index);
        }
    }



}