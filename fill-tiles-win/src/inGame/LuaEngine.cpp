//
// Created by sashi0034 on 2022/07/28.
//

#include "stdafx.h"

#include "LuaEngine.h"
#include "GameRoot.h"


namespace inGame
{

    LuaEngine::LuaEngine(GameRoot* gameRoot) : m_GameRoot(gameRoot)
    {
        m_Lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::string, sol::lib::os, sol::lib::math,
                             sol::lib::table, sol::lib::debug, sol::lib::bit32, sol::lib::io, sol::lib::ffi, sol::lib::utf8);

        bool result = tryInit();
        assert(result);
    }

    bool LuaEngine::tryInit()
    {
        bool isSuccess = true;
        namespace  fs = std::filesystem;

        std::string packagePath = m_Lua["package"]["path"];
        m_Lua["package"]["path"] = packagePath + ";" + directoryPath + "/util/?.lua";

        for (const auto& file : fs::recursive_directory_iterator(directoryPath))
        {
            if (!file.is_regular_file()) continue;

            const auto& filePath = file.path().string();
            isSuccess = isSuccess && loadFile(filePath);
        }

        m_Lua["NotImplementation"] = [](){ LOG_ASSERT(false, "Not Implementation."); };
        m_Lua["Println"] = [](const std::string& str){std::cout << str << "\n"; };

        initYieldFunc();

        return isSuccess;
    }

    bool LuaEngine::loadFile(const std::string &filePath)
    {
        sol::protected_function_result result = m_Lua.safe_script_file(filePath, &sol::script_pass_on_error);

        if (!result.valid())
        {
            sol::error error = result;
            LOG_ERR << filePath  << ": " << error.what() << std::endl;
            return false;
        }
        return true;
    }

    void LuaEngine::initYieldFunc()
    {
        sol::function yieldGetter = m_Lua.script_file(yieldGetterPath);
        m_YieldFunc = yieldGetter([&](){return getDeltaTime(); });
    }

    sol::state &LuaEngine::GetState()
    {
        return m_Lua;
    }

    void LuaEngine::ReloadAllFiles()
    {
        tryInit();
    }

    double LuaEngine::getDeltaTime()
    {
        return m_GameRoot->GetAppState()->GetTime().GetDeltaSec();
    }

} // inGame
