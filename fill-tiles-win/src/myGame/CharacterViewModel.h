//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_CHARACTERVIEWMODEL_H
#define FILL_TILES_CHARACTERVIEWMODEL_H

#include "../myUtil/myUtil.h"
#include "ScrollManager.h"
#include "MatPos.h"
#include "FieldManager.h"

namespace myGame
{
    class CharacterViewModel
    {
    public:
        CharacterViewModel() = default;
        CharacterViewModel(ScrollManager* scrollManager, Graph* graph);
        void SetModelPos(const Vec2<double>& pos);
        void SetModelPos(const MatPos& pos);
        void SetCollider(ISprRectColliderOwner *owner, FieldManager *field, const Rect<int> &collider);
        MatPos GetMatPos() const;
        Vec2<double> GetViewModelPos() const;

        SpriteTexture& GetModel();
        SpriteTexture& GetView();

    private:
        SpriteTexture m_ViewModel= SpriteTexture::Create();
        SpriteTexture m_View = SpriteTexture::Create();
        unique_ptr<SprRectCollider> m_Collider{};
    };
}


#endif //FILL_TILES_CHARACTERVIEWMODEL_H
