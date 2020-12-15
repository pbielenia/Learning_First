cmake_minimum_required(VERSION 3.16.3)
project(learning_first)

set(target_name ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/learning-first-engine)

add_executable(${target_name} main.cpp)
target_link_libraries(${target_name} PRIVATE lf::engine)
