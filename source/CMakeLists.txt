PROJECT(MemoryControllerAndPRA)


# 设置默认构建类型为 Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Default to Release build type" FORCE)
endif()

# 设置调试版本的编译参数
# Visual Studio会在Release版本中添加-DNDEBUG的编译选项 
# 作用是禁用assert断言
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# 设置发布版本的编译优化参数
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG") # 例如使用-O3进行优化

# 根据系统指定编译参数
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("for Linux : Generating Makefile")
	add_definitions( "-DPLATFORM_LINUX" )

elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("for Win : Generating Makefile")
	add_definitions( "-DPLATFORM_WIN" )

else()
	message("for unknown platform: Generating Makefile")
	add_definitions( "-DPLATFORM_SAFECODE" )

endif()

# C++ 标准设置为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 如果需要链接第三方库，可以在这里添加
# target_link_libraries(MyExecutable some_library)

# 设置include文件目录
include_directories(public thirdparty)

# 查找所有CPP源文件并存放到PRIVATE_SOURCES
# 查找所有.h头文件并存放到PUBLIC_HEADERS
# 第三方文件分类存放到THIRD_PARTY_HEADERS,THIRD_PARTY_SOURCES
file(GLOB PUBLIC_HEADERS public/*.h public/*.hpp)
file(GLOB PRIVATE_SOURCES private/*.cpp)
file(GLOB THIRD_PARTY_HEADERS thirdparty/*.h)
file(GLOB THIRD_PARTY_SOURCES thirdparty/*.cc thirdparty/*.cpp)

# 创建第三方静态库
add_library(ThirdPartyLib STATIC ${THIRD_PARTY_SOURCES} ${THIRD_PARTY_HEADERS})

# 添加可执行文件

add_executable(${PROJECT_NAME} main.cpp ${PRIVATE_SOURCES} ${PUBLIC_HEADERS} )

# 链接第三方库
target_link_libraries(${PROJECT_NAME} ThirdPartyLib)

