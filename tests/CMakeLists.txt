# testscmake_minimum_required(VERSION 3.10)
project(GoogleTestExample)

# �ҵ� Google Test
find_package(GTest REQUIRED)

# ���Ӳ��Կ�ִ���ļ�
add_executable(test_example main.cc)

# ���� Google Test ��
target_link_libraries(test_example PRIVATE GTest::GTest GTest::Main)

# ���ò���
enable_testing()
add_test(NAME test_example COMMAND test_example)
