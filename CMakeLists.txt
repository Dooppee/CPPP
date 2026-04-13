cmake_minimum_required(VERSION 3.15)
project(CppLearning)

# 设置C++20标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(Main Main.cpp)

# 平台特定设置
if(WIN32)
    message(STATUS "配置Windows平台编译")
    # Windows特定编译选项
    target_compile_options(Main PRIVATE
        -Wall
        -Wextra
    )
elseif(APPLE)
    message(STATUS "配置Mac平台编译")
    # Mac特定编译选项
    target_compile_options(Main PRIVATE
        -Wall
        -Wextra
    )
elseif(UNIX)
    message(STATUS "配置Linux平台编译")
    # Linux特定编译选项
    target_compile_options(Main PRIVATE
        -Wall
        -Wextra
    )
endif()

# 输出编译信息
message(STATUS "C++标准: ${CMAKE_CXX_STANDARD}")
message(STATUS "编译器: ${CMAKE_CXX_COMPILER_ID}")
