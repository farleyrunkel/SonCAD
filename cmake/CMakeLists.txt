# 查找符合模式的 CMake 文件
file(GLOB HELPER_CMAKE_FILES Setup*.cmake)

# 需要跳过的文件列表
set(_SKIP_FILES "")

# 遍历找到的文件
foreach(_CMAKE_FILE ${HELPER_CMAKE_FILES})
    # 提取文件名
    get_filename_component(_FILENAME ${_CMAKE_FILE} NAME)

    # 调试输出找到的文件
    message(STATUS "Found CMake file: ${_FILENAME}")

    # 检查文件是否在跳过列表中
    if (NOT _FILENAME IN_LIST _SKIP_FILES)
        if (EXISTS ${_CMAKE_FILE})
            # 包含文件并输出调试信息
            message(STATUS "Including CMake file: ${_CMAKE_FILE}")
            include(${_CMAKE_FILE})
        else()
            # 打印文件不存在的警告
            message(WARNING "File not found: ${_CMAKE_FILE}")
        endif()
    else()
        # 打印跳过文件信息
        message(STATUS "Skipping file: ${_FILENAME}")
    endif()
endforeach()
