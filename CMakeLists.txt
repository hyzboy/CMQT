cmake_minimum_required(VERSION 3.28)

project(CMQT)

include(path_config.cmake)
CMQTSetup(${CMAKE_CURRENT_SOURCE_DIR})

option(CMQT_EXAMPLES "Build CMQT examples" ON)

add_subdirectory(${CMQT_ROOT_SOURCE_PATH})

if(CMQT_EXAMPLES)
    add_subdirectory(examples)
endif()
