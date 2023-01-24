//
// Created by sashi0034 on 2022/09/06.
//

#ifndef FILL_TILES_RANDOM_H
#define FILL_TILES_RANDOM_H

#include <random>

namespace gameEngine
{

    class Random
    {
    public:
        Random();
        explicit Random(int seed);
        int Get(int max);
        int Get(int min, int max);
        static Random* const Instance;
    private:
        std::random_device device;
        std::default_random_engine engine;
        std::uniform_int_distribution<int> distribution;
    };

} // gameEngine

#endif //FILL_TILES_RANDOM_H
