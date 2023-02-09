#include "stdafx.h"
#include "GameSaveData.h"
#include "../myUtil/myUtil.h"

namespace myGame {
    bool GameSaveData::ReadData(const char* fileName)
    {
        FILE* file;
        fopen_s(&file, fileName, "rb");
        if (file == nullptr) return false;

        fread(this, sizeof(this), 1, file);
        LOG_INFO << "read save file: " << fileName;

        fclose(file);

        return true;
    }

    bool GameSaveData::WriteData(const char* fileName)
    {
        FILE* file;
        fopen_s(&file, fileName, "wb");
        if (file == nullptr) return false;

        auto size = sizeof(this);
        fwrite(this, size, 1, file);
        LOG_INFO << "write " << size << " bytes to save file: " << fileName;

        fclose(file);
        return true;
    }
}
