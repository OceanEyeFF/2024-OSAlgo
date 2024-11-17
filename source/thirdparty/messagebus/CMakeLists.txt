Project(messagebus)

# C++ 标准设置为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建库
add_library(messagebus STATIC tricky.cpp MessageBus.hpp)

# 指定库的头文件目录
target_include_directories(messagebus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 针对MSVC取消4819warnings
set_global_compile_options(messagebus)

