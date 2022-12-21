cmake_minimum_required(VERSION 3.17)
project(hw2)

set(CMAKE_CXX_STANDARD 17)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(./Eigen)
include_directories(./imgui)
aux_source_directory(./imgui ImgUI)

add_executable(hw2 main.cpp src/glad.c ${ImgUI} Utils.h Utils.cpp)
target_link_libraries(hw2 ${PROJECT_SOURCE_DIR}/lib/glfw3.dll)