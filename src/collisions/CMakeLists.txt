cmake_minimum_required(VERSION 3.17)

set(target_name collisions)

add_library(${target_name}
    src/Collision.cpp
)

add_library(${PROJECT_NAME}::${target_name} ALIAS ${target_name})

target_include_directories(${target_name}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${target_name}>
)

target_link_libraries(${target_name}
    sfml-graphics
)