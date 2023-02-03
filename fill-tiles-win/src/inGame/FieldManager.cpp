//
// Created by sashi0034 on 2022/06/11.
//

#include "FieldManager.h"
#include "GameRoot.h"
#include "field/FieldRenderer.h"
#include "MainScene.h"
#include "ZIndex.h"
#include "RemainingMineUi.h"
#include "MineFlowerManager.h"
#include "Player.h"
#include "field/renderBackmostGrass.h"

namespace inGame
{
    using namespace field;

    FieldManager::FieldManager(IChildrenPool<ActorBase> *belonging, IMainScene *parentalScene) :
            ActorBase(belonging),
            m_ParentalScene(parentalScene), m_TileMap(parentalScene)
    {
        ZIndexBackGround(&m_BackmostTexture).GoFront(0).ApplyZ();
        m_BackmostTexture.SetRenderingProcess([&](auto&& app) { renderBackmostGrass(app, m_ParentalScene); });

        ZIndexBackGround(&m_TileMapTexture).GoFront(1).ApplyZ();
        m_ParentalScene->GetScrollManager()->RegisterSprite(m_TileMapTexture);

        m_MineFlowerManager = std::make_unique<MineFlowerManager>(parentalScene);

        m_SwitchAcornManager = std::make_unique<SwitchAcornManager>(parentalScene);
    }

    void FieldManager::Init()
    {
        m_TileMap.LoadMapFile(getCurrentMapFileName());

        createRenderedTileMapToBuffer(m_ParentalScene->GetRoot()->GetAppState());
        m_TileMapTexture.SetGraph(m_BufferGraph.get());
        m_TileMapTexture.SetSrcRect(Rect<int>{Vec2{0, 0}, m_BufferGraphSize});

        m_MineFlowerManager->Init();

        initFieldByLevel(m_MineFlowerManager->GetCurrMineFlowerClass()->GetClassLevel());
    }

    std::string FieldManager::getCurrentMapFileName()
    {
        const std::string head{"field_"};
        const std::string extension{".tmx"};

        int index = 0;
#if INGAME_DEBUG_MAP_INDEX
        index = INGAME_DEBUG_MAP_INDEX;
#else
        index = 0;
#endif
        std::stringstream stream;
        stream << head << index / 10 << index % 10 << extension;

        auto result = stream.str();
        LOG_INFO << "loading map target: " << result << std::endl;
        return result;
    }


    void FieldManager::createRenderedTileMapToBuffer(IAppState *appState)
    {
        const Vec2<int> matSize = m_TileMap.GetMatSize();

        const auto renderingChipStartingPoint = Vec2<int>{0, 0};
        const auto renderingChipEndPoint = Vec2<int>{matSize.X-1, matSize.Y-1};

        m_BufferGraphSize = Vec2{matSize.X * PixelPerMat, matSize.Y * PixelPerMat};
        const auto sdlRenderer = appState->GetRenderer();
        SDL_Texture *renderingTarget = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888,
                                                         SDL_TEXTUREACCESS_TARGET, m_BufferGraphSize.X, m_BufferGraphSize.Y);
        assert(renderingTarget);
        renderTileMapUnsafely(renderingChipStartingPoint, renderingChipEndPoint, sdlRenderer, renderingTarget);

        m_BufferGraph = std::make_unique<Graph>(renderingTarget);
    }

    void
    FieldManager::renderTileMapUnsafely(const Vec2<int> &renderingChipStartingPoint,
                                        const Vec2<int> &renderingChipEndPoint,
                                        SDL_Renderer *const sdlRenderer, SDL_Texture *renderingTarget)
    {
        auto renderChange = TempRenderTargetChanger(sdlRenderer);
        renderChange.ChangeInScope(renderingTarget)->RenderClearTransparent();

        for (int chipY = renderingChipStartingPoint.Y; chipY<=renderingChipEndPoint.Y; ++chipY)
            for (int chipX = renderingChipStartingPoint.X; chipX<=renderingChipEndPoint.X; ++chipX)
            {
                const auto chipPos = Vec2{chipX, chipY};
                const Vec2<int> renderingPos = (Vec2<int>{chipX, chipY} * PixelPerMat);
                const auto mapElement = m_TileMap.GetElementAt(chipPos);
                const auto chipList = mapElement->GetChipList();

                const auto srcSize = Vec2{PixelPerMat, PixelPerMat};
                const auto renderingSize = Vec2<double>{1, 1};

                FieldRenderer fieldRenderer = FieldRenderer(
                        GameRoot::GetInstance().RscImage.get(),
                        chipPos,
                        renderingPos,
                        sdlRenderer,
                        srcSize,
                        renderingSize,
                        &m_TileMap);

                for (const auto chip : chipList)
                    renderChip(chip, fieldRenderer, sdlRenderer, renderingPos, renderingSize);
            }
    }

    void
    FieldManager::renderChip(const field::TilePropertyChip *chip, field::FieldRenderer &fieldRenderer, SDL_Renderer *sdlRenderer,
                             const Vec2<int> &screenPos, const Vec2<double> &renderingSize)
    {
        auto srcStarting = chip->SrcPoint;
        const auto srcSize = Vec2{PixelPerMat, PixelPerMat};

        bool hasRendered = fieldRenderer.RenderChip(chip->Kind);
        if (!hasRendered)
            m_TileMap.GetTilesetImage().RenderGraph(
                    sdlRenderer,
                    screenPos, Rect<int>(srcStarting, srcSize),
                    renderingSize);
    }

    FieldCheckMoveResult FieldManager::CheckMoveTo(const MatPos &currMatPos, EAngle goingAngle)
    {
        const auto diffVec = Angle(goingAngle).ToXY();
        const auto currPos = currMatPos.GetVec();
        const auto nextPos = currPos + diffVec;
        if (!m_TileMap.IsInRange(nextPos)) return FieldCheckMoveResult(false, nullptr);

        const auto currPosEle = m_TileMap.GetElementAt(currPos);
        const auto nextPosEle = m_TileMap.GetElementAt(nextPos);

        ISprRectColliderOwner* collidedObject = nullptr;
        bool canMove =
                !currPosEle->GetCliffFlag(goingAngle) &&
                !nextPosEle->IsWall() &&
                !m_DynamicCharacterCollider.IsHitWith((nextPos * PixelPerMat + MatPixelSize / 2).CastTo<double>(),
                                                      &collidedObject);

        return FieldCheckMoveResult(canMove, collidedObject);
    }



    IChildrenPool<character::CharacterBase> *FieldManager::GetCharacterPool()
    {
        return &m_ChildrenPool;
    }

    ITextureAnimator* FieldManager::GetAnimator()
    {
        return &m_Animator;
    }

    void FieldManager::Update(IAppState* app)
    {
        m_ChildrenPool.ProcessEach([&](character::CharacterBase& child){child.Update(app); });
        m_Animator.Update(app->GetTime().GetDeltaSec());
        m_CoroutineManager.UpdateEach();
    }

    SprRectColliderManager *FieldManager::GetCharacterCollider()
    {
        return &m_DynamicCharacterCollider;
    }

    void FieldManager::OverwriteWallFlag(const MatPos &pos, const Vec2<int> &fillSize, bool isWall)
    {
        Vec2<int> startPos = pos.GetVec();
        Vec2<int> nonNegativeSize = fillSize;

        if (nonNegativeSize.X < 0)
        {
            nonNegativeSize.X *= -1;
            startPos.X = startPos.X - nonNegativeSize.X + 1;
        }
        if (nonNegativeSize.Y < 0)
        {
            nonNegativeSize.Y *= -1;
            startPos.Y = startPos.Y - nonNegativeSize.Y + 1;
        }

        for (int x=0; x < nonNegativeSize.X; ++x)
            for (int y=0; y<nonNegativeSize.Y; ++y)
            {
                auto targetPos = startPos + Vec2<int>{x, y};
                if (m_TileMap.IsInRange(targetPos))
                    m_TileMap.GetElementWritableAt(targetPos)->OverwriteIsWall(isWall);
            }
    }

    void FieldManager::OverwriteWallFlag(const MatPos &pos, bool isWall)
    {
        OverwriteWallFlag(pos, Vec2<int>{1, 1}, isWall);
    }

    field::ITileMap* FieldManager::GetTileMap()
    {
        return &m_TileMap;
    }

    FieldManager::~FieldManager()
    {
        m_ChildrenPool.Release();
    }

    ICoroutineManager* FieldManager::GetCoroutine()
    {
        return &m_CoroutineManager;
    }

    WeakCollection<character::CheckpointBlock> & FieldManager::GetCheckpointBlockList(field::ETileKind blockKind)
    {
        switch (blockKind)
        {
            case ETileKind::checkpoint_block_1:
            case ETileKind::checkpoint_block_2:
            case ETileKind::checkpoint_block_3:
            case ETileKind::checkpoint_block_4:
                return m_CheckpointBlockList[blockKind];
            default:
                assert(false);
        }
    }

    Vec2<int> FieldManager::GetScreenMatSize() const
    {
        return (GameRoot::GetInstance().GetAppState()->GetScreenSize() / PixelPerMat);
    }

    MineFlowerManager *FieldManager::GetMineFlowerManager()
    {
        return m_MineFlowerManager.get();
    }

    SwitchAcornManager *FieldManager::GetSwitchAcornManager()
    {
        return m_SwitchAcornManager.get();
    }

    bool FieldManager::CanMovableObjectMoveTo(const MatPos &currPos, EAngle goingAngle)
    {
        auto const nextPos = currPos + MatPos(Angle(goingAngle).ToXY());
        return CheckMoveTo(currPos, goingAngle).CanMove &&
            !m_MineFlowerManager->IsMineFlowerMat(nextPos) &&
            !m_TileMap.GetElementAt(nextPos.GetVec())->IsIceFloor();
    }


    void FieldManager::initFieldByLevel(int level)
    {
        const auto pos = m_MineFlowerManager->GetMineFlowerClassByLevel(level)->GetRespawnMatPos().GetVec() * PixelPerMat;

        auto player = m_ParentalScene->GetPlayer();
        if (player!= nullptr) player->SetPos(pos.CastTo<double>());
    }

    WarpManager *FieldManager::GetWarpManager()
    {
        return &m_WarpManager;
    }


    FieldCheckMoveResult::FieldCheckMoveResult(const bool canMove, ISprRectColliderOwner *const collidedObject)
            : CanMove(canMove), CollidedObject(collidedObject)
    {}
}
