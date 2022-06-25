cmake_minimum_required(VERSION 3.0)

project(CMQT)

include(path_config.cmake)
CMQTSetup(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMQT_ROOT_SOURCE_PATH})
