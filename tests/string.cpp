#include <gtest/gtest.h>
#include <st/string.h>
#include <functional>
#include <array>
#include <utility>
#include <set>
#include <string>
#include <map>

void negativeProbeAllCharsExcept(std::function<bool(char)> predicate, 
                                 std::function<bool(char)> filter)
{
    for (char c=0; c<127; c++)
    {
        if (filter(c))
        {
            EXPECT_TRUE(predicate(c));
            continue;
        }

        EXPECT_FALSE(predicate(c));
    }
}

TEST(IS_SPACE, General)
{
    const std::set<char> values { ' ', '\t' };
    negativeProbeAllCharsExcept(ST::String::isSpace, [&](char c) {return values.contains(c);});
}

TEST(IS_NEWLINE, General)
{
    const std::set<char> values { '\r', '\n' };
    negativeProbeAllCharsExcept(ST::String::isNewline, [&](char c) {return values.contains(c);});
}

TEST(IS_NUM, General)
{
    const std::set<char> values { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    negativeProbeAllCharsExcept(ST::String::isNum, [&](char c) {return values.contains(c);});
}

TEST(CHAR_TO_INT, General)
{
    std::map<char, uint8_t> values {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
        {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}
    };

    for (auto [c, i]: values)
    {
        EXPECT_EQ(ST::String::toInt(c), i);
    }
}

TEST(IS_LETTER, General)
{
    const std::set<char> values {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    negativeProbeAllCharsExcept(ST::String::isLetter, [&](char c) {return values.contains(c);});
}

TEST(TO_FLOAT, PureFloat)
{
    std::map<std::string, float> values {
        {"0.1", 0.1f}, {"+0.1", 0.1f}, {"-0.1", -0.1f}
    };

    for (auto [s, v]: values)
    {
        float f = 0.0f;
        ST::String::toFloat(s.c_str(), s.size(), f);
        EXPECT_FLOAT_EQ(v, f);
    }
}

TEST(TO_FLOAT, FloatSurroundedWithSpace)
{
    std::map<std::string, float> values {
        {"   0.1", 0.1f}, {"   +0.1", 0.1f}, {"   -0.1", -0.1f},
        {"0.1   ", 0.1f}, {"+0.1   ", 0.1f}, {"-0.1   ", -0.1f},
        {"   0.1   ", 0.1f}, {"   +0.1   ", 0.1f}, {"   -0.1   ", -0.1f}, 
        
        {"\t0.1", 0.1f}, {"\t+0.1", 0.1f}, {"\t-0.1", -0.1f},
        {"0.1\t", 0.1f}, {"+0.1\t", 0.1f}, {"-0.1\t", -0.1f},
        {"\t0.1\t", 0.1f}, {"\t+0.1\t", 0.1f}, {"\t-0.1\t", -0.1f},

        {"   0.1\t", 0.1f}, {"   +0.1\t", 0.1f}, {"   -0.1\t", -0.1f},
        {"\t0.1   ", 0.1f}, {"\t+0.1   ", 0.1f}, {"\t-0.1   ", -0.1f} 
    };

    for (auto [s, v]: values)
    {
        float f = 0.0f;
        ST::String::toFloat(s.c_str(), s.size(), f);
        EXPECT_FLOAT_EQ(v, f);
    }
}