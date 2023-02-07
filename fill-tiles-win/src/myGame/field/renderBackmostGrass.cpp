#include "stdafx.h"
#include "renderBackmostGrass.h"
#include "../pixel.h"


using namespace myGame;
static inline const int cellStep = pixel::PixelPerMat * 4;
static inline const int cellSpace = 1;
static inline const int cellLength = cellStep - cellSpace;

void myGame::field::renderBackmostGrass(IAppState* app, MainScene* mainScene)
{
    auto&& root = mainScene->GetRoot();
    auto&& scroll = mainScene->GetScrollManager()->GetScroll();

    // 背景色で塗りつぶし
    SDL_SetRenderDrawColor(app->GetRenderer(), 40, 177, 124, 255);
    SDL_RenderClear(app->GetRenderer());

    auto&& screenSize = app->GetScreenSize();

    //bool isOddRow = true;
    for (double y = -cellStep + util::ModDouble2(scroll.Y, cellStep); y <= screenSize.Y; y += cellStep) {
        //isOddRow = !isOddRow;
        for (double x = -cellStep + util::ModDouble2(scroll.X, cellStep) ; x <= screenSize.X; x += cellStep) {
            //const int startX = (x - int(isOddRow) * cellStep / 2) * pixel::PixelPerUnit;
            const int startX = x * pixel::PixelPerUnit;
            const int startY = y * pixel::PixelPerUnit;

            SDL_Rect dest = SDL_Rect{ startX, startY, cellLength * pixel::PixelPerUnit, cellLength * pixel::PixelPerUnit };
            auto&& tex = root->RscImage->grass_texture_01->GetSdlTexture();
            SDL_RenderCopy(app->GetRenderer(), tex, nullptr, &dest);
        }
    }
}
