#pragma once
#include "common.h"
#include "math.h"

namespace ST
{
namespace String
{
    inline bool isSpace(char c) noexcept { return c == ' ' || c == '\t'; }
    
    inline bool isNewline(char c) noexcept { return c == '\r' || c == '\n'; }
    
    inline bool isNum(char c) noexcept { return c >= '0' && c <= '9'; }
    
    inline bool isLetter(char c) noexcept { return (c >= 'a' && c <= 'z') || 
                                          (c >= 'A' && c <= 'Z'); }
    
    inline uint8_t toInt(char c) noexcept { return isNum(c) ? c - '0' : c; }

    inline bool toFloat(const char* const begin, const char* const end, float& out_value) noexcept
    {
        if (begin >= end) return false;

        // scan for trailing spaces
        const char* start_pos = 0;

        for (const char* p = begin; p <= end; p++)
        {
            if (!isSpace(*p))
            {
                start_pos = p;
                break;
            }
        }

        // check for a sign
        bool is_negative = false;

        if (*start_pos == '-' || *start_pos == '+')
        {
            is_negative = (*start_pos == '-');
            start_pos++;
        }

        // check bounds, also catch case when it's only sign in string
        //if (start_pos > stop_pos) return false;

        // in case of "  0.1  " payload size is 3
        //uint32_t payload_len = (stop_pos - start_pos) + 1;

        // check if every char is a digit and by the way find dot position
        const char* dot_pos = nullptr; // use this value as a mark for not found dot

        const char* stop_pos = nullptr;
        for (const char* p = start_pos; p <= end; p++)
        {
            if (!isNum(*p))
            {
                if (*p == '.' && dot_pos == nullptr)
                {
                    dot_pos = p;
                    continue;
                }

                stop_pos = p - 1;
                break;
            }
        }

        // if dot was found, check if it's not on first or last char
        if ((dot_pos != nullptr) &&
            (dot_pos == start_pos || dot_pos == stop_pos))
        {
            return false;
        }


        // iterate all digits before dot and multiply by 10^n
        float result = 0.0f;

        uint32_t n = 0; // index of current digit
        for (const char* p = (dot_pos ? dot_pos - 1 : stop_pos); 
             p >= start_pos; p--)
        {
            result += toInt(*p) * ST::Math::pow(10, n);
            n++;
        }

        // if we have a dot
        if (dot_pos)
        {
            // the same but in reverse for remaining part
            n = 1;
            for (const char* p = dot_pos + 1; p <= stop_pos; p++)
            {
                result += (float)toInt(*p) / ST::Math::pow(10, n);
                n++;
            }
        }

        out_value = is_negative ? result * -1.0f : result;
        return true;
    }

    
    inline bool toFloat(const char* const str, const uint32_t len, float& out_value) noexcept
    {
        return toFloat(str, str + len, out_value);
    }
}
}