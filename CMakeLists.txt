cmake_minimum_required(VERSION 3.15)

PROJECT(2024-OS)

MESSAGE(STATUS "PROJECT_BINARY_DIR= " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "PROJECT_SOURCE_DIR= " ${PROJECT_SOURCE_DIR})

MESSAGE("CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME} ")
MESSAGE("CMAKE_HOST_SYSTEM: ${CMAKE_HOST_SYSTEM} ")
 
MESSAGE("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME} ")
MESSAGE("CMAKE_SYSTEM: ${CMAKE_SYSTEM} ")
 
MESSAGE("CMAKE_HOST_UNIX: ${CMAKE_HOST_UNIX} ")
MESSAGE("CMAKE_HOST_WIN32: ${CMAKE_HOST_WIN32} ")


if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("current platform: Linux ")
	message("generating Linux makefile")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("current platform: Windows")
	message("generating Windows Visual Studio Solution")
else()
	message("current platform: unknown")
endif()

# 设置默认构建类型为 Release
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RELEASE CACHE STRING "Default to Release build type" FORCE)
endif()

# 取消CMAKE_BUILD_TYPE 的大小写
string(TOUPPER "${CMAKE_BUILD_TYPE}" UPPER_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${UPPER_BUILD_TYPE})
message( "current build type: " ${CMAKE_BUILD_TYPE} )

# 设置调试版本的编译参数
# Visual Studio会在Release版本中添加-DNDEBUG的编译选项 
# 作用是禁用assert断言
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
# 设置发布版本的编译优化参数
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DRELEASE") # 例如使用-O3进行优化


ADD_SUBDIRECTORY(source)
