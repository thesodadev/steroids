#pragma once
#include "common.h"
#include "math.h"

namespace ST
{
namespace String
{
    inline bool isSpace(char c) { return c == ' ' || c == '\t'; }
    
    inline bool isNewline(char c) { return c == '\r' || c == '\n'; }
    
    inline bool isNum(char c) { return c >= '0' && c <= '9'; }
    
    inline bool isLetter(char c) { return (c >= 'a' && c <= 'z') || 
                                          (c >= 'A' && c <= 'Z'); }
    
    inline uint8_t toInt(char c) { return isNum(c) ? c - '0' : c; }

    inline bool toFloat(const char* str, uint32_t len, float& out_value)
    {
        if (len == 0) return false;

        // scan for trailing spaces
        int32_t start_pos = 0;
        for (int32_t i = 0; i < len; i++)
        {
            if (!isSpace(str[i]))
            {
                start_pos = i;
                break;
            }
        }

        // check for a sign
        bool is_negative = false;

        if (str[start_pos] == '-' || str[start_pos] == '+')
        {
            is_negative = (str[start_pos] == '-');
            start_pos++;
        }

        // check bounds, also catch case when it's only sign in string
        //if (start_pos > stop_pos) return false;

        // in case of "  0.1  " payload size is 3
        //uint32_t payload_len = (stop_pos - start_pos) + 1;

        // check if every char is a digit and by the way find dot position
        int32_t dot_pos = -1; // use this value as a mark for not found dot

        int32_t stop_pos = len - 1;
        for (int32_t i = start_pos; i < len; i++)
        {
            if (!isNum(str[i]))
            {
                if (str[i] == '.' && dot_pos == -1)
                {
                    dot_pos = i;
                    continue;
                }

                stop_pos = i - 1;
                break;
            }
        }

        // if dot was found, check if it's not on first or last char
        if ((dot_pos != -1) &&
            (dot_pos == start_pos || dot_pos == stop_pos))
        {
            return false;
        }


        // iterate all digits before dot and multiply by 10^n
        float result = 0.0f;

        uint32_t n = 0; // index of current digit
        for (int32_t i = (dot_pos == -1 ? stop_pos : dot_pos - 1); i >= start_pos; i--)
        {
            result += toInt(str[i]) * ST::Math::pow(10, n);
            n++;
        }

        // if we have a dot
        if (dot_pos != -1)
        {
            // the same but in reverse for remaining part
            n = 1;
            for (int32_t i = dot_pos + 1; i <= stop_pos; i++)
            {
                result += (float)toInt(str[i]) / ST::Math::pow(10, n);
                n++;
            }
        }

        out_value = is_negative ? result * -1.0f : result;
        return true;
    }
}
}