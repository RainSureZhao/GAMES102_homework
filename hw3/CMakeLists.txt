cmake_minimum_required(VERSION 3.17)
project(hw3)

set(CMAKE_CXX_STANDARD 17)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(./Eigen)
include_directories(./imgui)
aux_source_directory(./imgui ImgUI)


add_executable(hw3 main.cpp src/glad.c ${ImgUI} Utils.h Utils.cpp Utils.cpp Utils.h)
target_link_libraries(hw3 ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)
