//
// Created by sashi0034 on 2022/07/02.
//

#include "Font.h"

namespace myGame::resource
{

    Font::Font(IAppState *appState)
    : m_AppStatePtr(appState)
    {
        LOG_INFO << "Loaded Font Resources." << std::endl;
    }
}