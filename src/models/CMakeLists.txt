cmake_minimum_required(VERSION 3.17)

set(target_name models)

add_library(${target_name}
    src/Drawable.cpp
    src/Vehicle.cpp
    src/Track.cpp
)

add_library(${PROJECT_NAME}::${target_name} ALIAS ${target_name})

target_include_directories(${target_name}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${target_name}>
)

set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 20)

target_link_libraries(${target_name}
    ${PROJECT_NAME}::physics
    ${PROJECT_NAME}::collisions
    helpers
    sfml-graphics
)