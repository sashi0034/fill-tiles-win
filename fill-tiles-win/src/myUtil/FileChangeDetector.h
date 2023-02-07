//
// Created by sashi0034 on 2022/08/03.
//

#ifndef FILL_TILES_FILECHANGEDETECTOR_H
#define FILL_TILES_FILECHANGEDETECTOR_H

#include <stdafx.h>

namespace myUtil
{
    class FileChangeDetector
    {
    public:
        explicit FileChangeDetector(std::string  path);
        bool CheckChanged();
    private:
        bool update();
        std::string m_FilePath;
        std::filesystem::file_time_type m_LastWroteTime;
    };

} // myUtil

#endif //FILL_TILES_FILECHANGEDETECTOR_H
