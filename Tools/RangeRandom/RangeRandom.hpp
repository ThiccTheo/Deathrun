#pragma once

#include <iostream>
#include <random>

inline const int rangeRandom(const int min, const int max)
{
    std::random_device seed;
    std::mt19937 rng{ seed() };
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(rng);
}

inline const float rangeRandom(const float min, const float max)
{
    std::random_device seed;
    std::mt19937 rng{ seed() };
    std::uniform_real_distribution<> distribution(min, max);
    return static_cast<float>(distribution(rng));
}

inline const double rangeRandom(const double min, const double max)
{
    std::random_device seed;
    std::mt19937 rng{ seed() };
    std::uniform_real_distribution<> distribution(min, max);
    return distribution(rng);
}