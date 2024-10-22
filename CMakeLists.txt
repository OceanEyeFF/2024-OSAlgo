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


ADD_SUBDIRECTORY(source)
