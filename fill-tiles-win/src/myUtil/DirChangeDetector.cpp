//
// Created by sashi0034 on 2022/06/20.
//

#include "DirChangeDetector.h"

#include <utility>
#include "log.h"

namespace fs = std::filesystem;

namespace myUtil
{
    DirChangeDetector::DirChangeDetector(std::string dirPath)
            : m_DirPath(std::move(dirPath))
    {
        const auto fileType = fs::status(m_DirPath).type();
        assert(fileType==fs::file_type::directory);
        
        update();
    }

    bool DirChangeDetector::CheckChanged()
    {
        return update();
    }

    bool DirChangeDetector::update()
    {
        bool result = false;

        const int numOldFiles = m_FileInfo.size();
        int numCurrFiles = 0;

        for (const fs::directory_entry& file : fs::recursive_directory_iterator(m_DirPath)) {
            ++numCurrFiles;

            const auto filePath = file.path().string();
            const auto lastWriteTime = fs::last_write_time(filePath);

            if (m_FileInfo.count(filePath)==0) {
                m_FileInfo[filePath] = lastWriteTime;
            }
            else if (m_FileInfo[filePath] != lastWriteTime)
            {
                m_FileInfo[filePath] = lastWriteTime;
                result = true;
            }
        }

        if (numCurrFiles!=numOldFiles) result = true;

        return result;
    }
}
