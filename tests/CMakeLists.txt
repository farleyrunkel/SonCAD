# testscmake_minimum_required(VERSION 3.10)
project(GoogleTestExample)

# 找到 Google Test
find_package(GTest REQUIRED)

# 添加测试可执行文件
add_executable(test_example main.cc)

# 链接 Google Test 库
target_link_libraries(test_example PRIVATE GTest::GTest GTest::Main)

# 启用测试
enable_testing()
add_test(NAME test_example COMMAND test_example)
