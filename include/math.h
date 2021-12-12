#pragma once
#include "common.h"

namespace ST
{
namespace Math
{
    template<typename T>
    inline T abs(const T value) noexcept
    {
        return value < 0 ? value * -1 : value;
    }

    template<typename T>
    inline T pow(const T value, const int16_t n) noexcept
    {
        if (n == 0) return 1;
        if (value == 0) return 0;

        T result = value;
        for (uint16_t i = 2; i <= abs(n); i++)
        {
            result *= value;
        }

        return n > 0 ? result : 1.0f / result;
    }

    // allowed double or float
    template<typename T>
    inline bool equalsWithPrecision(const T value_1, const T value_2, const T epsilon) noexcept
    {
        return abs(value_2 - value_1) < epsilon;
    }
}
}