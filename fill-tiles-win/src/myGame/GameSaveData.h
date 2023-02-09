#pragma once
namespace myGame {
    struct StageClearData
    {
        int PassedTime{};
        int PassedSteps{};

        bool IsCleared() const;
    };

    struct GameSaveData
    {
        StageClearData StageClear[64];

        bool ReadData(const char* fileName);
        bool WriteData(const char* fileName);
    };
}
