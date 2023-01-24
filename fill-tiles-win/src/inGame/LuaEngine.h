//
// Created by sashi0034 on 2022/07/28.
//

#ifndef FILL_TILES_LUAENGINE_H
#define FILL_TILES_LUAENGINE_H

#include <sol.hpp>
#include "../gameEngine/gameEngine.h"

namespace inGame
{
    class GameRoot;

    class LuaEngine
    {
    public:
        explicit LuaEngine(GameRoot* gameRoot);
        sol::state& GetState();
        void ReloadAllFiles();

    private:
        GameRoot* m_GameRoot;
        const std::string  directoryPath = "./assets/lua";
        static const inline std::string yieldGetterPath = "./assets/lua/getYield.lua";
        sol::state m_Lua{};
        bool tryInit();
        double getDeltaTime();
        sol::function m_YieldFunc{};

        void initYieldFunc();
    public:
        template <class... Args> void RunCoroutine(CoroTaskYield& yield, sol::function function, Args... args)
        {
            sol::coroutine task = m_Lua["coroutine"]["create"](function);

            while (true)
            {
                m_Lua["coroutine"]["resume"](
                        task,
                        m_YieldFunc,
                        args...
                );

                std::string status = m_Lua["coroutine"]["status"](task);
                if (status == "dead") break;

                yield();
            }
        }

        bool loadFile(const std::string &filePath);
    };

} // gameEngine

#endif //FILL_TILES_LUAENGINE_H
