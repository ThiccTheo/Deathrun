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