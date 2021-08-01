#pragma once
#include <cinttypes>

namespace ST
{
namespace Common
{
    template<typename T>
    inline const T* findNext(const T* begin, const T* end, const T target) noexcept
    {
        const T* p = begin;
        while (*p != target && p < end) p++;
        return p != end ? p : nullptr;
    }

    template<typename T>
    inline const T* findNext(const T* begin, const uint32_t len, const T target) noexcept
    {
        return findNext<T>(begin, begin + len, target);
    }

    template<typename T>
    inline uint32_t distance(const T* begin, const T* end) noexcept
    {
        return (end - begin) / sizeof(T);
    }

    template<typename T>
    inline uint32_t count(const T* begin, const T* end, const T target) noexcept
    {
        const T* p = begin;

        uint32_t c = 0;
        while (p <= end)
        {
            if (*p == target) c++;
            p++;
        }

        return c;
    }

    template<typename T>
    inline uint32_t count(const T* begin, uint32_t len, const T target) noexcept
    {
        return count<T>(begin, begin + len, target);
    }

    template<typename T>
    inline bool isInBounds(const T* p, const T* end, const uint32_t offset = 0) noexcept
    { 
        return p + offset <= end; 
    }
}
}