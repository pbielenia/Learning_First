cmake_minimum_required(VERSION 3.17)
project(learningfirst)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/helpers)
add_subdirectory(src/physics)
add_subdirectory(src/game)

set(target_name ${PROJECT_NAME})

add_executable(${target_name} src/main.cpp)
set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 20)

target_link_libraries(${target_name}
    ${PROJECT_NAME}-physics
    ${PROJECT_NAME}-game
)
