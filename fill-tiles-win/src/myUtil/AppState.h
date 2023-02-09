//
// Created by sashi0034 on 2022/05/16.
//

#ifndef FILL_TILES_APPSTATE_H
#define FILL_TILES_APPSTATE_H

#include <stdafx.h>
#include "Time.h"
#include "Vec2.h"
#include "MouseState.h"
#include "Graph.h"

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;


namespace myUtil
{
    class IAppState
    {
    public:
        [[nodiscard]] virtual Vec2<int> GetScreenSize() const = 0;
        [[nodiscard]] virtual Vec2<int> GetRealScreenSize() const = 0;
        [[nodiscard]] virtual int GetPixelPerUnit() const = 0;
        [[nodiscard]] virtual const Time& GetTime() const = 0;
        [[nodiscard]] virtual Time& MutTime() = 0;
        [[nodiscard]] virtual SDL_Window* GetWindow() const = 0;
        [[nodiscard]] virtual SDL_Renderer* GetRenderer() const = 0;
        [[nodiscard]] virtual const Uint8* GetKeyboardState() const = 0;
        virtual const IMouseState* GetMouseState() const = 0;
    };


    class AppState final: public IAppState
    {
    public:
        AppState();
        AppState(const Vec2<int> &screenSize, const int pixelPerUnit, SDL_Window* window);

        void UpdateFrame();
        void RenderFrame();

        [[nodiscard]] bool CanQuitApp() const;
    private:
        Vec2<int> m_ScreenSize{};
        Vec2<int> m_RealScreenSize{};
        Vec2<int> m_LiteralRealScreenSize{};
        const int m_PixelPerUnit=0;
        unique_ptr<Time> m_Time{};
        SDL_Window* m_Window{};
        SDL_Renderer* m_Renderer{};
        const Uint8* m_KeyboardState{};
        bool m_CanQuitApp = false;
        bool m_IsWindowFullScreen = false;
        void pollEvent();
        void processEvent(SDL_Event &e);
        void handleKeyDown(const SDL_Scancode& keyCode);
        MouseState m_Mouse{};
    public:
        [[nodiscard]] int GetPixelPerUnit() const override;
        [[nodiscard]] Vec2<int> GetScreenSize() const override;
        Vec2<int> GetRealScreenSize() const override;
        [[nodiscard]] const Time & GetTime() const override;
        [[nodiscard]] Time& MutTime() override;
        [[nodiscard]] SDL_Window* GetWindow() const override;
        [[nodiscard]] SDL_Renderer* GetRenderer() const override;
        [[nodiscard]] const Uint8* GetKeyboardState() const override;
        const IMouseState *GetMouseState() const override;

        void checkChangeWindowSize();
    };
}


#endif //FILL_TILES_APPSTATE_H
