#include <gtest/gtest.h>
#include <st/math.h>

TEST(Pow, Integer)
{
    EXPECT_EQ(ST::Math::pow(0, 2), 0);
    EXPECT_EQ(ST::Math::pow(2, 0), 1);
    EXPECT_EQ(ST::Math::pow(2, 2), 4);
    EXPECT_EQ(ST::Math::pow(-2, 2), 4);
    EXPECT_EQ(ST::Math::pow(2, -2), 0); // need a float to use negative power
    EXPECT_EQ(ST::Math::pow(-2, 3), -8);
}

TEST(Pow, Float)
{
    EXPECT_FLOAT_EQ(ST::Math::pow(0.2f, 0), 1.0f);

    EXPECT_FLOAT_EQ(ST::Math::pow(0.0f, 2), 0.0f);
    EXPECT_FLOAT_EQ(ST::Math::pow(0.2f, 2), 0.04f);
    EXPECT_FLOAT_EQ(ST::Math::pow(-0.2f, 2), 0.04f);
    EXPECT_FLOAT_EQ(ST::Math::pow(-0.2f, 3), -0.008f);

    EXPECT_FLOAT_EQ(ST::Math::pow(0.0f, -2), 0.0f);
    EXPECT_FLOAT_EQ(ST::Math::pow(0.2f, -2), 1.0f/0.04f);
    EXPECT_FLOAT_EQ(ST::Math::pow(-0.2f, -2), 1.0f/0.04f);
    EXPECT_FLOAT_EQ(ST::Math::pow(-0.2f, -3), -1.0f/0.008f);
}

TEST(ABS, Integer)
{
    EXPECT_EQ(ST::Math::abs(0), 0);
    EXPECT_EQ(ST::Math::abs(2), 2);
    EXPECT_EQ(ST::Math::abs(-2), 2);
}

TEST(ABS, Float)
{
    EXPECT_FLOAT_EQ(ST::Math::abs(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(ST::Math::abs(0.2f), 0.2f);
    EXPECT_FLOAT_EQ(ST::Math::abs(-0.2f), 0.2f);
}

TEST(EQUALS_WITH_PRECISION, General)
{
    EXPECT_TRUE(ST::Math::equalsWithPrecision(0.00001f, 0.00002f, 0.0001f));
    EXPECT_TRUE(ST::Math::equalsWithPrecision(0.04f, 0.12f, 0.1f));
    EXPECT_FALSE(ST::Math::equalsWithPrecision(0.0001f, 0.0002f, 0.0001f));
}
