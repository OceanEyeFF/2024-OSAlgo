PROJECT(MemControllerAndPageRepSystem)

# 设置构建类型
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
	message(STATUS "Configuring Main for DEBUG")
	#    add_compile_definitions(_DEBUG)
	#    target_compile_options(ClientExecutable PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
	message(STATUS "Configuring Main for RELEASE")
	#    add_compile_definitions(_RELEASE)
	#    target_compile_options(ClientExecutable PRIVATE -O3)
endif()

# 根据系统指定编译参数
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("MAIN : Generating Makefile")
	add_definitions( "-DPLATFORM_LINUX" )
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("MAIN: generating Windows Visual Studio Solution")
	add_definitions( "-DPLATFORM_WIN" )
else()
	message("MAIN : Generating Makefile")
	add_definitions( "-DPLATFORM_SAFECODE" )
endif()

# Libgo 配置
# set(DISABLE_HOOK ON)
# 添加 Libgo 作为子目录
add_subdirectory(thirdparty/libgo)
# easylogging 配置
# 添加 Libgo 作为子目录
add_subdirectory(thirdparty/easylogging++)

# C++ 标准设置为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找所有CPP源文件并存放到PRIVATE_SOURCES
# 查找所有.h头文件并存放到PUBLIC_HEADERS
# 第三方文件分类存放到THIRD_PARTY_HEADERS,THIRD_PARTY_SOURCES
file(GLOB PUBLIC_HEADERS public/*.h public/*.hpp)
file(GLOB PRIVATE_SOURCES private/*.cpp)
file(GLOB LIBGO_HEADERS thirdparty/libgo/libgo/*.h)

message(${LIBGO_HEADERS})

# 添加可执行文件
add_executable(Main PRIVATE main.cpp ${PRIVATE_SOURCES} ${PUBLIC_HEADERS} )
# 添加主程序头文件目录
target_include_directories(Main PUBLIC public)

target_include_directories(Main PRIVATE thirdparty/libgo)
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("LIBGO : Configure for Linux")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("LIBGO : Configue for Windows Visual Studio Solution")
	target_include_directories(Main PRIVATE thirdparty/libgo/lingo/netio/windows)
endif()


# 链接第三方库
target_link_libraries(Main PRIVATE easylogging++ libgo_static)

