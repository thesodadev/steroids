#include <gtest/gtest.h>
#include <st/common.h>
#include <array>

TEST(FIND_NEXT, General)
{
    const std::array<char, 10> values = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'
    };
    
    {
        const char* n = ST::Common::findNext(values.data(), values.size(), 'b');
        EXPECT_EQ(n, &values[1]);
    }

    {
        const char* n = ST::Common::findNext(values.data(), values.size(), 'z');
        EXPECT_EQ(n, nullptr);
    }
}

TEST(COUNT, General)
{
    const std::array<char, 10> values = {
        'a', 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'b', 'b'
    };
    
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'e'), 1);
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'a'), 2);
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'b'), 3);
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'z'), 0);
}

TEST(DISTANCE, General)
{
    const std::array<char, 10> values = {
        'a', 'a', 'b', 'd', 'e', 'f', 'g', 'h', 'b', 'b'
    };
    
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'e'), 1);
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'a'), 2);
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'b'), 3);
    EXPECT_EQ(ST::Common::count(values.data(), values.size(), 'z'), 0);
}