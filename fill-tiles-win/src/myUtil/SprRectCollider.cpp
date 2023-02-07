//
// Created by sashi0034 on 2022/06/19.
//


#include "SprRectCollider.h"
#include "Range.h"


namespace myUtil{
    SprRectCollider::SprRectCollider(ISprRectColliderOwner *owner, SpriteTexture *parentalLinkingPos,
                                     const Rect<int> &colliderRect)
            : m_ColliderStartingPoint(colliderRect.GetStartingPoint().CastTo<double>()),
              m_ColliderSize(colliderRect.GetSize().CastTo<double>()),
              m_LinkingPosSpr(parentalLinkingPos),
              m_Owner(owner)
    {}

    bool SprRectCollider::IsIntersectWith(const Rect<double> &checkingRect) const
    {
        const auto selfTexturePos = m_LinkingPosSpr->GetPosition();
        const auto selfColliderPos = selfTexturePos + m_ColliderStartingPoint;
        const auto selfRect = Rect<double>(selfColliderPos, m_ColliderSize);

        bool isIntersect = selfRect.IsIntersectWith(checkingRect);
        return isIntersect;
    }

    bool SprRectCollider::IsIntersectWith(const Vec2<double> &checkingPoint) const
    {
        const auto selfTexturePos = m_LinkingPosSpr->GetPosition();
        const auto selfColliderPos = selfTexturePos + m_ColliderStartingPoint;

        bool isIntersect = Range(selfColliderPos.X, selfColliderPos.X + m_ColliderSize.X).IsBetween(checkingPoint.X)
                           && Range(selfColliderPos.Y, selfColliderPos.Y + m_ColliderSize.Y).IsBetween(checkingPoint.Y);
        return isIntersect;
    }

    ISprRectColliderOwner* SprRectCollider::GetOwner() const
    {
        return m_Owner;
    }

    unique_ptr<SprRectCollider> SprRectCollider::Create(ISprRectColliderOwner *owner, SpriteTexture *parentalLinkingPos,
                                                        const Rect<int> &colliderRect)
    {
        assert(owner);
        assert(parentalLinkingPos);

        auto product = unique_ptr<SprRectCollider>(new SprRectCollider(owner, parentalLinkingPos,
                                                                       colliderRect));
        return product;
    }


}