cmake_minimum_required(VERSION 3.17)
project(sfml-app)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_subdirectory(src/collisions)
add_subdirectory(src/physics)
add_subdirectory(src/models)

add_executable(sfml-app src/main.cpp)
set_property(TARGET sfml-app PROPERTY CXX_STANDARD 17)

target_link_libraries(sfml-app
    sfml-graphics
    sfml-app::models
    sfml-app::collisions
)
