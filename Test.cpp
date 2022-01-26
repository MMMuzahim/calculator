//g++ Test.cpp -lgtest -lpthread
#include <iostream>
#include <gtest/gtest.h>
#include "calculator.cpp"

using namespace std;

TEST(Test_1, Subtest_1) {
    ASSERT_EQ(calculator("2+3*5"), "17");
}

TEST(Test_2, Subtest_2) {
    ASSERT_EQ(calculator("( 2 +3)*   5"), "25");
}

TEST(Test_3, Subtest_3) {
    ASSERT_EQ(calculator("2+3*(-5)"), "-13");
}

TEST(Test_4, Subtest_4) {
    ASSERT_EQ(calculator("2.4+3,7"), "6.1");
}

TEST(Test_5, Subtest_5) {
    ASSERT_EQ(calculator("-1 + 5 - 3"), "1");
}

TEST(Test_6, Subtest_6) {
    ASSERT_EQ(calculator("-10 + (8 * 2.5) - (3 / 1,5)"), "8");
}

TEST(Test_7, Subtest_7) {
    ASSERT_EQ(calculator("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)"), "11");
}

TEST(Test_8, Subtest_8) {
    ASSERT_EQ(calculator("1.1 + 2.1 + abc"), "некорректный ввод, строка содержит недопустимое выражение abc");
}

TEST(Test_9, Subtest_9) {
    ASSERT_EQ(calculator("2 / (-3)"), "-0.67");
}

TEST(Test_10, Subtest_10) {
    ASSERT_EQ(calculator("(2 / (-3)"), "некорректный ввод");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
