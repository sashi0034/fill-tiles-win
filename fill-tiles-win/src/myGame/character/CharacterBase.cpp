//
// Created by sashi0034 on 2022/06/17.
//

#include "CharacterBase.h"
#include "../FieldManager.h"

namespace myGame::character
{
    CharacterBase::CharacterBase(FieldManager *parentField)
        : ChildBase<CharacterBase>(parentField->GetCharacterPool()),
        m_ParentalField(parentField)
    {}

    void CharacterBase::Destroy()
    {
        this->getBelongingPool()->Destroy(this);
    }

    FieldManager *CharacterBase::getParentField()
    {
        return m_ParentalField;
    }

    void CharacterBase::Update(IAppState *app)
    {
        (void)app;
    }
}
