PROJECT(TestCasesGenerator)

# 设置构建类型
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    message(STATUS "Configuring Generator for DBUG")
	#    add_compile_definitions(_DEBUG)
	#    target_compile_options(ClientExecutable PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
    message(STATUS "Configuring Generator for RELEASE")
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


# C++ 标准设置为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建客户端的可执行文件
add_executable(Generator ./main.cpp)
