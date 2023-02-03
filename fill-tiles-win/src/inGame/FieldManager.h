//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_FIELDMANAGER_H
#define FILL_TILES_FIELDMANAGER_H

#include "ActorBase.h"
#include "field/TileMap.h"
#include "field/TileMapMatElement.h"
#include "resource/Image.h"
#include "field/FieldRenderer.h"
#include "MatPos.h"
#include "character/CharacterBase.h"
#include "rx.h"
#include "../gameEngine/WeakCollection.h"
#include "MineFlowerManager.h"
#include "./SwitchAcornManager.h"
#include "WarpManager.h"
#include "pixel.h"

namespace inGame
{
    namespace character{
        class CharacterBase;
        class CheckpointBlock;
    }

    class IMainScene;

    struct FieldCheckMoveResult{
        const bool CanMove;
        ISprRectColliderOwner* const CollidedObject;

        FieldCheckMoveResult(const bool canMove, ISprRectColliderOwner *const collidedObject);
    };

    class FieldManager : public ActorBase
    {
    public:
        IChildrenPool<character::CharacterBase> *GetCharacterPool();

        WeakCollection<character::CheckpointBlock> &GetCheckpointBlockList(field::ETileKind blockKind);

        SprRectColliderManager *GetCharacterCollider();

        explicit FieldManager(IChildrenPool<ActorBase> *belonging, IMainScene *parentalScene);
        ~FieldManager();

        ITextureAnimator* GetAnimator();

        ICoroutineManager* GetCoroutine();

        void Init() override;
        void Update(IAppState* app);

        FieldCheckMoveResult CheckMoveTo(const MatPos &currMatPos, EAngle goingAngle);

        bool CanMovableObjectMoveTo(const MatPos &currPos, EAngle goingAngle);

        void OverwriteWallFlag(const MatPos &pos, bool isWall);
        void OverwriteWallFlag(const MatPos &pos, const Vec2<int> &fillSize, bool isWall);

        field::ITileMap* GetTileMap();

        static inline const int PixelPerMat = pixel::PixelPerMat;
        static inline const Vec2<int> MatPixelSize = {PixelPerMat, PixelPerMat};
        static inline const Vec2<double> CharacterPadding{0, -PixelPerMat/4};
        Vec2<int> GetScreenMatSize() const;

        MineFlowerManager *GetMineFlowerManager();
        SwitchAcornManager* GetSwitchAcornManager();
        WarpManager* GetWarpManager();
    private:
        void createRenderedTileMapToBuffer(IAppState *appState);
        void renderChip(const field::TilePropertyChip *chip, field::FieldRenderer &fieldRenderer, SDL_Renderer *sdlRenderer,
                        const Vec2<int> &screenPos, const Vec2<double> &renderingSize);
        IMainScene* m_ParentalScene;
        field::TileMap m_TileMap;
        SpriteTexture m_Texture = SpriteTexture::Create(nullptr);
        ChildrenPool<character::CharacterBase> m_ChildrenPool{};
        TextureAnimator m_Animator{};
        SprRectColliderManager m_DynamicCharacterCollider{};
        CoroutineManager m_CoroutineManager{};
        unique_ptr<Graph> m_BufferGraph;
        WarpManager m_WarpManager{};
        Vec2<int> m_BufferGraphSize{};
        unique_ptr<MineFlowerManager> m_MineFlowerManager{};
        unique_ptr<SwitchAcornManager> m_SwitchAcornManager{};

        std::unordered_map<field::ETileKind, WeakCollection<character::CheckpointBlock>> m_CheckpointBlockList{};

        void initFieldByLevel(int level);

        void renderTileMapUnsafely(const Vec2<int> &renderingChipStartingPoint, const Vec2<int> &renderingChipEndPoint,
                                   SDL_Renderer *const sdlRenderer, SDL_Texture *renderingTarget);

        static std::string getCurrentMapFileName() ;
    };
}


#endif //FILL_TILES_FIELDMANAGER_H
