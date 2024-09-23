#pragma once

#include <random>
#include <chrono>

namespace select
{
    inline std::mt19937 new_generator()
    {
        std::random_device rd{};

        std::seed_seq ss
        {
            static_cast<std::seed_seq::result_type>
            (std::chrono::steady_clock::now().time_since_epoch().count()),
            rd(), rd(), rd(), rd(), rd(), rd(), rd()
        };

        return std::mt19937{ ss };
    }

    inline std::mt19937 mt{ new_generator() };

    inline int from_range(int min, int max)
    {
        return std::uniform_int_distribution{min, max} (mt);
    }

    inline float from_range(float min, float max)
    {
        return std::uniform_real_distribution{min, max} (mt);
    }
}
