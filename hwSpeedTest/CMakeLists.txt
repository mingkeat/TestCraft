# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    HwSpeedTest
    VERSION 0.1
    DESCRIPTION "Small CMake example built with VSCode")


add_subdirectory(hwSpeed)   # look in hwSpeed subdirectory for CMakeLists.txt to process
add_subdirectory(apps)    # look in apps subdirectory for CMakeLists.txt to process

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    add_subdirectory(tests)   # look in tests subdirectory for CMakeLists.txt to process
endif() # PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME