
#include "stdafx.h"
#include "GameProcess.h"


int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONIN$", "r", stdin);
    freopen_s(&stream, "CONOUT$", "w", stdout);
    freopen_s(&stream, "CONOUT$", "w", stderr);

    int result = GameProcess::RunGame();

    return result;
}
