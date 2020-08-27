cmake_minimum_required(VERSION 3.17)

set(module_name ${PROJECT_NAME}-physics)
set(models_target_name ${module_name}-models)
set(processing_target_name ${module_name}-processing)

add_library(${models_target_name} INTERFACE)
target_include_directories(${models_target_name}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(${models_target_name}
    INTERFACE
        sfml-system
        ${PROJECT_NAME}-helpers
)

add_library(${processing_target_name} INTERFACE)
target_include_directories(${processing_target_name}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(${module_name} INTERFACE)
target_link_libraries(${module_name}
    INTERFACE
        ${models_target_name}
        ${processing_target_name}
)
