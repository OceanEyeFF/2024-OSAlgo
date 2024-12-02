PROJECT(MemControllerAndPageRepSystem)

# Below deprecated
# 设置调试版本的编译参数
# Visual Studio会在Release版本中添加-DNDEBUG的编译选项 
# 作用是禁用assert断言
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
# 设置发布版本的编译优化参数
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DRELEASE") # 例如使用-O3进行优化



# 根据系统指定编译参数
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
	message("MAIN : Generating Makefile")
	add_definitions( "-DPLATFORM_LINUX" )
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	message("MAIN: generating Windows Visual Studio Solution")
	add_definitions( "-DPLATFORM_WIN" )
endif()

# Libgo 配置
# set(DISABLE_HOOK)
option(DISABLE_HOOK "Disable hook functionality" ON)
# 添加 Libgo 作为子目录
add_subdirectory(thirdparty/libgo)
# easylogging 配置
# 添加 easylogging++ 作为子目录
add_subdirectory(thirdparty/easylogging++)
# 添加 messagebus
add_subdirectory(thirdparty/messagebus)
# file(GLOB MESSAGEBUS thirdparty/libgo/messagebus/MessageBus.hpp)

# C++ 标准设置为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找所有CPP源文件并存放到PRIVATE_SOURCES
# 查找所有.h头文件并存放到PUBLIC_HEADERS
# 第三方文件分类存放到THIRD_PARTY_HEADERS,THIRD_PARTY_SOURCES
file(GLOB PUBLIC_HEADERS public/*.h public/*.hpp)
file(GLOB PRIVATE_SOURCES private/*.cpp)
# file(GLOB LIBGO_HEADERS thirdparty/libgo/libgo/*.h)
# message(${LIBGO_HEADERS})

# 添加可执行文件
add_executable(Main main.cpp ${PRIVATE_SOURCES} ${PUBLIC_HEADERS} ${MESSAGEBUS} )

# 根据构建类型设置编译参数
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
	message(STATUS "Configuring Main for DEBUG")
	if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
		#add_compile_definitions(_DEBUG)
		target_compile_options(Main PRIVATE -g)
	endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
	message(STATUS "Configuring Main for RELEASE")
	if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
		add_compile_definitions(NDEBUG)
		target_compile_options(Main PRIVATE -O3)
	endif()
endif()

# 针对MSVC取消4819warnings
set_global_compile_options(Main)

# 添加主程序头文件目录
target_include_directories(Main PUBLIC public)
target_include_directories(Main PRIVATE thirdparty/messagebus)

# 链接第三方库
target_link_libraries(Main PRIVATE easylogging++ libgo_static messagebus)

# TestGenerator 配置
add_executable(TestGenerator ./TestGenerator/main.cpp)
target_link_libraries(TestGenerator PRIVATE libgo_static)

# Test配置
add_executable(TestModules ./Test/test.cpp)
target_link_libraries(TestModules PRIVATE libgo_static)
