#pragma once
namespace myGame {
    struct GameSaveData
    {
        int MyData;
        int MyNum;

        bool ReadData(const char* fileName);
        bool WriteData(const char* fileName);
    };
}
