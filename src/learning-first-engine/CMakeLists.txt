cmake_minimum_required(VERSION 3.16.3)
project(engine)

set(target_name ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_library(${target_name} INTERFACE)
add_library(lf::${target_name} ALIAS ${target_name})
target_include_directories(${target_name}
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/engine>
        )
