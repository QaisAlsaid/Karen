cmake_minimum_required(VERSION 3.10)
Project(stb)
add_library(${PROJECT_NAME} stb.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

