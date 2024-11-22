#include <gtest/gtest.h>

// ����һ���򵥺���
int add(int a, int b) {
    return a + b;
}

// ��������
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(add(2, 3), 5);  // 2 + 3 = 5
}

TEST(AdditionTest, HandlesNegativeInput) {
    EXPECT_EQ(add(-2, -3), -5);  // -2 + -3 = -5
}

TEST(AdditionTest, HandlesMixedInput) {
    EXPECT_EQ(add(-2, 3), 1);  // -2 + 3 = 1
}

// ���������в���
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
