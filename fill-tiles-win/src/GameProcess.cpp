//
// Created by sashi0034 on 2022/05/04.
//

#include "gameEngine/gameEngine.h"
#include "GameProcess.h"
#include "inGame/GameLooper.h"

int GameProcess::RunGame()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() < 0)
    {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Fill Tiles (Debug)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          screenWidth * pixelPerUnit, screenHeight * pixelPerUnit, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    unique_ptr<AppState> appState = std::make_unique<AppState>(Vec2<int>{screenWidth, screenHeight}, int(pixelPerUnit), window);

    auto renderer = appState->GetRenderer();
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);

    inGame::GameLooper::Loop(appState);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
