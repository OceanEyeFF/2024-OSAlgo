PROJECT(MemoryControllerAndPRA)

# C++ 标准设置为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置include文件目录
include_directories(public)

# 查找所有CPP源文件并存放到PRIVATE_SOURCES
file(GLOB PRIVATE_SOURCES private/*.cpp )

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp ${PRIVATE_SOURCES})

# To Do
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("for Linux : Generating Makefile")
	add_definitions( "-DPLATFORM_LINUX" )

elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("for Win : Generating Makefile")
	add_definitions( "-DPLATFORM_WIN" )

else()
	message("for unknown platform: Generating Makefile")

endif()
