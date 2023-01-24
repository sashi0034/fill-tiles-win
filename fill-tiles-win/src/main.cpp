

#include "GameProcess.h"
#include "SDL.h"


int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    int res = GameProcess::RunGame();

    return res;
}
