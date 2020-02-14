#pragma once
#include <random>

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::default_random_engine e;
    return distribution(e);
}

inline vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.0f * vec3(random_double(), random_double(), random_double()) - 1;
    } while (p.squared_length() >= 1.0f);
    return p;
}