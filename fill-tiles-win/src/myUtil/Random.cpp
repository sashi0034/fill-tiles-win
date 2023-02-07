//
// Created by sashi0034 on 2022/09/06.
//

#include <climits>
#include "Random.h"

namespace myUtil
{
    Random* const Random::Instance = new Random();

    Random::Random() : engine(device()), distribution(0, INT_MAX - 1)
    {}

    Random::Random(int seed) : engine(seed), distribution(0, INT_MAX - 1)
    {}

    int Random::Get(int max)
    {
        return distribution(engine) % max;
    }
    int Random::Get(int min, int max)
    {
        return min + (distribution(engine) % (max - min));
    }
} // myUtil