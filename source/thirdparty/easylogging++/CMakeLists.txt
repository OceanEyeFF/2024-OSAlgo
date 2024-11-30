Project(easylogging++)

# 创建库
add_library(easylogging++ STATIC easylogging++.cc easylogging++.h)

# 指定库的头文件目录
target_include_directories(easylogging++ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
