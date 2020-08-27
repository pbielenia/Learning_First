cmake_minimum_required(VERSION 3.17)

set(module_name ${PROJECT_NAME}-game)
set(engine_target_name ${module_name}-engine)
set(objects_target_name ${module_name}-objects)

add_library(${objects_target_name} INTERFACE)
target_include_directories(${objects_target_name}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${objects_target_name}
INTERFACE
    ${PROJECT_NAME}-physics-models
)

add_library(${engine_target_name}
    src/engine/Core.cpp
)
target_include_directories(${engine_target_name}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/game/engine>
)
target_link_libraries(${engine_target_name}
    PRIVATE
        sfml-system
        sfml-graphics
        ${PROJECT_NAME}-helpers
        ${objects_target_name}
)

add_library(${module_name} INTERFACE)
target_link_libraries(${module_name}
    INTERFACE
        ${engine_target_name}
        ${objects_target_name}
)
