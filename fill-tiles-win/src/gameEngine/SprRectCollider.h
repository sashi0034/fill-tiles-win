//
// Created by sashi0034 on 2022/06/19.
//

#ifndef FILL_TILES_SPRRECTCOLLIDER_H
#define FILL_TILES_SPRRECTCOLLIDER_H

#include <stdafx.h>
#include "WeakPtr.h"
#include "SpriteTexture.h"
#include "ChildrenPool.h"

namespace gameEngine
{
    // This is marker interface.
    class ISprRectColliderOwner
    {
    public:
        virtual ~ISprRectColliderOwner() = default;
    };

    class SprRectCollider
    {
        DEF_WEAK_CONTROLLER(SprRectCollider);
    private:
        SprRectCollider(ISprRectColliderOwner *owner, SpriteTexture *parentalLinkingPos, const Rect<int> &colliderRect);
    public:
        static unique_ptr<SprRectCollider>
        Create(ISprRectColliderOwner *owner, SpriteTexture *parentalLinkingPos, const Rect<int> &colliderRect);

        bool IsIntersectWith(const Rect<double> &checkingRect) const;

        bool IsIntersectWith(const Vec2<double> &checkingPoint) const;

        ISprRectColliderOwner* GetOwner() const;
    private:
        Vec2<double> m_ColliderStartingPoint;
        Vec2<double> m_ColliderSize;
        SpriteTexture *m_LinkingPosSpr;
        ISprRectColliderOwner* m_Owner;
    };
}

#endif //FILL_TILES_SPRRECTCOLLIDER_H
