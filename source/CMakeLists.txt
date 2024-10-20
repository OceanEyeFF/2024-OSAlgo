PROJECT(MemoryControllerAndPRA)

# C++ 标准设置为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置include文件目录
include_directories(public)

# 查找所有CPP源文件并存放到PRIVATE_SOURCES
file(GLOB PRIVATE_SOURCES private/*.cpp )

# 添加可执行文件
add_executable(main main.cpp ${PRIVATE_SOURCES})
