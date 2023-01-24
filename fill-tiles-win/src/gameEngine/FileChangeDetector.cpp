//
// Created by sashi0034 on 2022/08/03.
//

#include "FileChangeDetector.h"

#include <utility>
#include <cassert>

namespace fs = std::filesystem;

namespace gameEngine
{
    FileChangeDetector::FileChangeDetector(std::string path)
    : m_FilePath(std::move(path))
    {
        const auto fileType = fs::status(m_FilePath).type();
        assert(fileType==fs::file_type::regular);

        update();
    }

    bool FileChangeDetector::CheckChanged()
    {
        return update();
    }

    bool FileChangeDetector::update()
    {
        const auto lastWroteTime = fs::last_write_time(m_FilePath);

        if (m_LastWroteTime != lastWroteTime)
        {
            m_LastWroteTime = lastWroteTime;
            return true;
        }

        return false;
    }
} // gameEngine