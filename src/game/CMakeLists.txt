cmake_minimum_required(VERSION 3.17)

set(module_name ${PROJECT_NAME}-game)
set(driver_target_name ${module_name}-driver)
set(engine_target_name ${module_name}-engine)
set(environment_target_name ${module_name}-environment)

add_library(${environment_target_name} INTERFACE)
target_include_directories(${environment_target_name}
        INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )
target_link_libraries(${environment_target_name}
        INTERFACE
        ${PROJECT_NAME}-physics-models
        )

add_library(${driver_target_name}
        src/driver/KeyboardInput.cpp
        )
target_include_directories(${driver_target_name}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/game>
        PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/game/driver>
        )
target_link_libraries(${driver_target_name}
        PRIVATE
        sfml-system
        ${environment_target_name}
        )

add_library(${engine_target_name}
        src/engine/Engine.cpp
        )
target_include_directories(${engine_target_name}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/game>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/game/engine>
)
target_link_libraries(${engine_target_name}
    PRIVATE
        sfml-system
        sfml-graphics
        ${PROJECT_NAME}-helpers
        ${environment_target_name}
        ${driver_target_name}
)

add_library(${module_name} INTERFACE)
target_link_libraries(${module_name}
        INTERFACE
        ${engine_target_name}
        ${environment_target_name}
        ${driver_target_name}
        )
