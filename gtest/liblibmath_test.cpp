#include <gtest/gtest.h>
// C 言語のライブラリの関数を C++ で使うために extern "C" を指定
extern "C" {
    #include <lib_math.h>
}

// // テスト対象の関数
// int add(int a, int b) {
//     return a + b;
// }

// テストケース
TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(add(1, 2), 3);
}

TEST(AdditionTest, NegativeNumbers) {
    EXPECT_EQ(add(-1, -1), -2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}