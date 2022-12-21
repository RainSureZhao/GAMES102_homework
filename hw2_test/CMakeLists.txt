cmake_minimum_required(VERSION 3.17)
project(hw2_test)

set(CMAKE_CXX_STANDARD 17)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(./Eigen)
include_directories(./imgui)
include_directories(./Python)
aux_source_directory(./imgui ImgUI)
# aux_source_directory(./Python/include Python)
add_executable(hw2_test main.cpp src/glad.c RbfNetwork.h RbfNetwork.cpp MathUtil.cpp  ${ImgUI} rbf_nn.py)
add_executable(test test.cpp)


target_link_libraries(hw2_test ${PROJECT_SOURCE_DIR}/lib/glfw3.dll ${PROJECT_SOURCE_DIR}/lib/python36.dll)

target_link_libraries(test ${PROJECT_SOURCE_DIR}/lib/python36.dll)

