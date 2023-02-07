//
// Created by sashi0034 on 2022/06/20.
//

#ifndef FILL_TILES_DIRCHANGEDETECTOR_H
#define FILL_TILES_DIRCHANGEDETECTOR_H

#include <stdafx.h>

namespace myUtil
{
    class DirChangeDetector
    {
    public:
        explicit DirChangeDetector(std::string dirPath);
        bool CheckChanged();
    private:
        bool update();
        std::string m_DirPath;
        std::unordered_map<std::string, std::filesystem::file_time_type> m_FileInfo{};
    };
}


#endif //FILL_TILES_DIRCHANGEDETECTOR_H
