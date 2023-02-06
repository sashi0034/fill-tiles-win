//
// Created by sashi0034 on 2022/06/17.
//

#include "ZIndex.h"
#include "CharacterViewModel.h"

namespace inGame{


    ZIndexBackGround::ZIndexBackGround(SpriteTexture *texture)
    : m_Texture(texture)
    {}

    void ZIndexBackGround::ApplyZ()
    {
        m_Texture->SetZ(baseBackGroundZ - m_Index);
    }

    ZIndexBackGround &ZIndexBackGround::GoFront(int frontLargerIndex)
    {
        assert(Range<int>(0, baseRange).IsBetween(frontLargerIndex));
        m_Index = frontLargerIndex;
        return *this;
    }

    ZIndexCharacter::ZIndexCharacter(CharacterViewModel &character)
    : m_Character(character)
    {}

    void ZIndexCharacter::ApplyZ()
    {
        double modelY = m_Character.GetModel().GetPosition().Y;

        double normalizedZ = Range(infinityMinus, infinity)
                .Normalize(-modelY, Range(baseCharacterZ, baseCharacterZ + baseRange));

        m_Character.GetView().SetZ(normalizedZ);
    }

    ZIndexUi::ZIndexUi(SpriteTexture *texture)
    : m_Texture(texture)
    {}

    void ZIndexUi::ApplyZ()
    {
        m_Texture->SetZ(baseUiZ - m_Index);
    }

    ZIndexUi &ZIndexUi::SetIndex(int frontLargerIndex)
    {
        assert(Range<int>(0, baseRange).IsBetween(frontLargerIndex));
        m_Index = frontLargerIndex;
        return *this;
    }

    ZIndexForeground::ZIndexForeground(SpriteTexture* texture)
        : m_Texture(texture)
    {}

    void ZIndexForeground::ApplyZ()
    {
        m_Texture->SetZ(baseForegroundZ - m_Index);
    }

    ZIndexForeground& ZIndexForeground::SetIndex(int frontLargerIndex)
    {
        assert(Range<int>(0, baseRange).IsBetween(frontLargerIndex));
        m_Index = frontLargerIndex;
        return *this;
    }

    ZIndexEffect::ZIndexEffect(SpriteTexture *texture)
    : m_Texture(texture)
    {}

    ZIndexEffect &ZIndexEffect::SetIndex(int frontLargerIndex)
    {
        assert(Range<int>(0, baseRange).IsBetween(frontLargerIndex));
        m_Index = frontLargerIndex;
        return *this;
    }

    void ZIndexEffect::ApplyZ()
    {
        m_Texture->SetZ(baseEffect - m_Index);
    }
}
