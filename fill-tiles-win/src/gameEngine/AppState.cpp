//
// Created by sashi0034 on 2022/05/16.
//

#include "AppState.h"
#include "SpriteTexture.h"
#include <memory>
#include <iostream>

namespace gameEngine
{

    AppState::AppState()
    {}

    AppState::AppState(const Vec2<int> &screenSize, const int pixelPerUnit, SDL_Window* window) :
        m_ScreenSize(screenSize),
        m_PixelPerUnit(pixelPerUnit)
    {
        m_Time = std::make_unique<Time>();
        m_Window = window;
        m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }

    int AppState::GetPixelPerUnit() const
    {
        return m_PixelPerUnit;
    }

    Vec2<int> AppState::GetScreenSize() const
    {
        return m_ScreenSize;
    }

    const Time &AppState::GetTime() const
    {
        return *m_Time;
    }
    Time& AppState::GetTimeMutable()
    {
        return *m_Time;
    }
    SDL_Window *AppState::GetWindow() const
    {
        return m_Window;
    }

    SDL_Renderer *AppState::GetRenderer() const
    {
        return m_Renderer;
    }

    void AppState::UpdateFrame()
    {
        pollEvent();

        checkChangeWindowSize();

        m_KeyboardState = SDL_GetKeyboardState(NULL);
        m_Time->Update(true);
        SpriteTextureContext::Global()->UpdateAll(this);
    }

    constexpr int maxPixelInScreen = 1920 * 1080;

    void AppState::checkChangeWindowSize()
    {
        int w, h;
        SDL_GetWindowSize(m_Window, &w, &h);
        if (m_LiteralRealScreenSize.X == w && m_LiteralRealScreenSize.Y == h) return;

        m_LiteralRealScreenSize = Vec2{w, h};;

        // 解像度が最大値を超えないようにする
        const double smallerRate = std::sqrt(
                std::min(1.0, double(maxPixelInScreen) / (w * h)));

        m_RealScreenSize = Vec2{int(w * smallerRate), int(h * smallerRate)};

        //resetRenderingBuffer(m_RealScreenSize);

        m_ScreenSize = m_RealScreenSize / m_PixelPerUnit;
    }

    void AppState::RenderFrame()
    {
        SpriteTextureContext::Global()->RenderAll(this);

        SDL_SetRenderTarget(m_Renderer, nullptr);
        SDL_RenderClear(m_Renderer);

        auto destRect = SDL_Rect{0, 0, m_LiteralRealScreenSize.X, m_LiteralRealScreenSize.Y};
        SDL_RenderCopy(
            m_Renderer,
            SpriteTextureContext::Global()->GetRenderingBuffer()->GetSdlTexture(),
            nullptr, &destRect);

        SDL_RenderPresent(m_Renderer);
    }

    const Uint8 *AppState::GetKeyboardState() const
    {
        return m_KeyboardState;
    }

    void AppState::pollEvent()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
            processEvent(e);
    }

    void AppState::processEvent(SDL_Event &e)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            m_CanQuitApp = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_Mouse.SetPushed(e.button.button, true);
            break;
        case SDL_MOUSEBUTTONUP:
            m_Mouse.SetPushed(e.button.button, false);
            break;
        case SDL_MOUSEMOTION:
            m_Mouse.SetPosition(Vec2<double>(double(e.motion.x), double(e.motion.y)) / m_PixelPerUnit);
            break;
        case SDL_KEYDOWN:
            // m_KeyboardStateはSDL_GetKeyboardState(NULL)で外で入れている
            // ここではもっとプリミティブなキー操作を扱う
            handleKeyDown(e.key.keysym.scancode);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            // SDL2に動作しないバグがあるかも
            std::cout << e.window.data1 << ", " << e.window.data2 << std::endl;
            assert(false);
            break;
        default:
            break;
        }
    }

    void AppState::handleKeyDown(const SDL_Scancode& keyCode)
    {
        if (keyCode == SDL_SCANCODE_F11) {
            m_IsWindowFullScreen = !m_IsWindowFullScreen;
            SDL_SetWindowFullscreen(m_Window, m_IsWindowFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
        }
    }

    bool AppState::CanQuitApp() const
    {
        return m_CanQuitApp;
    }

    const IMouseState *AppState::GetMouseState() const
    {
        return &m_Mouse;
    }

    Vec2<int> AppState::GetRealScreenSize() const
    {
        return m_RealScreenSize;
    }

}
