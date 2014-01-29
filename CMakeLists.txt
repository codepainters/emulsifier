project(emulsifier)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_subdirectory(core)
add_subdirectory(cli)
add_subdirectory(gui)
