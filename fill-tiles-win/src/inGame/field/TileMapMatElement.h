//
// Created by sashi0034 on 2022/06/13.
//

#ifndef FILL_TILES_TILEMAPMATELEMENT_H
#define FILL_TILES_TILEMAPMATELEMENT_H

#include "../ActorBase.h"
#include "../character/CharacterBase.h"
#include "../Angle.h"

namespace inGame::character
{
    class GlassFloor;
}

namespace inGame::field
{
    enum class ETileKind
    {
        none,
        fines,
        low_basin,
        low_basin_shade_face,
        low_basin_shade_edge,
        normal_plain,
        normal_plain_cliff,
        normal_plain_shade_face,
        normal_plain_shade_edge,
        high_plateau,
        high_plateau_cliff,
        small_tree,
        big_tree,
        stairs,
        mine_flower_1,
        mine_flower_2,
        mine_flower_3,
        mine_flower_4,
        checkpoint_block_1,
        checkpoint_block_2,
        checkpoint_block_3,
        checkpoint_block_4,
        glass,
        ice,
        switch_button,
        switch_red,
        switch_blue,
        carrot,

        max,
    };

    struct TilePropertyChip
    {
        ETileKind Kind = ETileKind::none;
        bool IsWall = false;
        Vec2<int> SrcPoint{};

        // 実装したが今のところ未使用
        //std::map<std::string, std::string> DetailProps{};
        //std::string GetDetailPropOf(const std::string& key) const;
    };

    class ITileMapMatElement
    {
    public:
        [[nodiscard]] virtual const std::vector<const TilePropertyChip *> &GetChipList() const = 0;
        [[nodiscard]] virtual bool IsWall() const = 0;
        [[nodiscard]] virtual bool IsBloomedMineFlower() const = 0;
        virtual bool GetCliffFlag(EAngle aspect) = 0;
        virtual character::GlassFloor* GetGlassFloor() = 0;
        virtual bool IsIceFloor() = 0;
    };

    class ITileMapMatElementWritable
    {
    public:
        virtual void AddChip(const TilePropertyChip *chip) = 0;
        virtual bool InsertChip(const TilePropertyChip *frontChip, const TilePropertyChip *newBackChip) = 0;
        virtual bool ReplaceChip(const TilePropertyChip *oldChip, const TilePropertyChip *newChip) = 0;
        virtual bool RemoveChip(const TilePropertyChip *chip) = 0;
        virtual bool RemoveChip(ETileKind kind)= 0;
        virtual void SetWallByTopTile() = 0;

        virtual void OverwriteIsWall(bool isWall) = 0;
        virtual void SetIsBloomedMineFlower(bool flag) = 0;
        virtual void SetGlassFloor(character::GlassFloor* glassFloor) = 0;
    };

    class TileMapMatElement final: public ITileMapMatElement, public ITileMapMatElementWritable
    {
    public:
        TileMapMatElement();

        bool IsBloomedMineFlower() const override;

        void SetIsBloomedMineFlower(bool flag) override;

        void AddChip(const TilePropertyChip *chip) override;
        bool InsertChip(const TilePropertyChip *frontChip, const TilePropertyChip *newBackChip) override;
        bool ReplaceChip(const TilePropertyChip *oldChip, const TilePropertyChip *newChip) override;
        bool RemoveChip(const TilePropertyChip *chip) override;
        bool RemoveChip(ETileKind kind) override;

        void SetWallByTopTile() override;

        bool HasChip(ETileKind kind);

        [[nodiscard]] const std::vector<const TilePropertyChip *> &GetChipList() const override;

        bool GetCliffFlag(EAngle aspect) override;

        [[nodiscard]] bool IsWall() const override;

        void SetCliffFlag(EAngle aspect, bool flag);

        character::GlassFloor *GetGlassFloor() override;

        void SetGlassFloor(character::GlassFloor *glassFloor) override;

        void OverwriteIsWall(bool isWall) override;

        bool IsIceFloor() override;
    private:
        std::vector<const TilePropertyChip *> m_ChipList;

        std::bitset<int(ETileKind::max)> m_HasChip{};

        bool m_IsWall = false;
        bool m_IsBloomedMineFlower = false;
        WeakPtr<character::GlassFloor> m_GlassFloor{};

        std::bitset<4> m_CliffAspect{};
    };
}


#endif //FILL_TILES_TILEMAPMATELEMENT_H
