#include <gtest/gtest.h>

// 测试一个简单函数
int add(int a, int b) {
    return a + b;
}

// 测试用例
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(add(2, 3), 5);  // 2 + 3 = 5
}

TEST(AdditionTest, HandlesNegativeInput) {
    EXPECT_EQ(add(-2, -3), -5);  // -2 + -3 = -5
}

TEST(AdditionTest, HandlesMixedInput) {
    EXPECT_EQ(add(-2, 3), 1);  // -2 + 3 = 1
}

// 主函数运行测试
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
