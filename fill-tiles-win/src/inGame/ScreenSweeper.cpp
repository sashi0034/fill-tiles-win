#include "stdafx.h"
#include "ScreenSweeper.h"
#include "ZIndex.h"

namespace inGame {
    ScreenSweeper::ScreenSweeper(
        IChildrenPool<ActorBase>* parent,
        IAppState* app,
        ITextureAnimator* animator,
        SpriteTextureContext* screen) :
        ActorBase(parent)
    {
        auto&& rendererdScreen = screen->GetRenderingBuffer();
        auto&& rendererdSize = rendererdScreen->GetSize();

        // スクリーンと同じサイズのテクスチャを作成
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        SDL_Texture* renderingTarget = SDL_CreateTexture(
            app->GetRenderer(),
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            rendererdSize.X, rendererdSize.Y);

        // 描画対象変更
        auto renderChange = TempRenderTargetChanger(app->GetRenderer());
        renderChange.ChangeInScope(renderingTarget)->RenderClearTransparent();

        // スクリーンをスクリーンショットとしてコピー
        SDL_RenderCopy(app->GetRenderer(), rendererdScreen->GetSdlTexture(), nullptr, nullptr);
        _screenshot = std::make_unique<Graph>(renderingTarget);

        // スプライト設定
        _spr.SetGraph(_screenshot.get());
        _spr.SetSrcRect(RectInt{ VecZero<int>(), rendererdSize });
        _spr.SetRenderingProcess(renderingProcess::WrapRenderSpriteDotByDot(&_spr));
        ZIndexForeground(&_spr).ApplyZ();

        // アニメーション
        animator->TargetTo(_spr)
            ->AnimScale(VecDouble2{ 0, 1 }, 0.3)->SetEase(EAnimEase::InBack)
            ->Then()
            // 終わったら削除
            ->DelayVirtual([this, parent]() {
                parent->Destroy(this);
            }, 0);
    }
}
