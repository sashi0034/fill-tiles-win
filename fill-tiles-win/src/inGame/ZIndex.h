//
// Created by sashi0034 on 2022/06/17.
//

#ifndef FILL_TILES_ZINDEX_H
#define FILL_TILES_ZINDEX_H

#include "../gameEngine/gameEngine.h"

namespace inGame
{
    class CharacterViewModel;

    class ZIndex
    {
    public:
        virtual void ApplyZ() = 0;
    protected:
        const double baseRange = 1000;
        const double baseBackGroundZ = baseRange * 1;
        const double baseCharacterZ = baseRange * 0;
        const double baseEffect = baseRange * -1;
        const double baseUiZ = baseRange * -2;
    };

    class ZIndexBackGround : public ZIndex
    {
    public:
        ZIndexBackGround(SpriteTexture *texture);
        ZIndexBackGround& GoFront(int frontLargerIndex);
        void ApplyZ() override;
    private:
        SpriteTexture* m_Texture;
        int m_Index{};
    };

    class ZIndexCharacter : public ZIndex
    {
    public:
        explicit ZIndexCharacter(CharacterViewModel& character);
        void ApplyZ() override;
    private:
        const double infinity = 32768;
        const double infinityMinus = -infinity;
        CharacterViewModel& m_Character;
    };

    class ZIndexEffect : public ZIndex
    {
    public:
        explicit ZIndexEffect(SpriteTexture *texture);
        ZIndexEffect& SetIndex(int frontLargerIndex);
        void ApplyZ() override;
    private:
        SpriteTexture* m_Texture;
        int m_Index{};
    };

    class ZIndexUi : public ZIndex
    {
    public:
        ZIndexUi(SpriteTexture *texture);
        ZIndexUi& SetIndex(int frontLargerIndex);
        void ApplyZ() override;
    private:
        SpriteTexture* m_Texture;
        int m_Index{};
    };

}


#endif //FILL_TILES_ZINDEX_H
