cmake_minimum_required(VERSION 3.17)

set(target_name ${PROJECT_NAME}-helpers)

add_library(${target_name} src/Collision.cpp)

target_include_directories(${target_name}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/helpers>
)
