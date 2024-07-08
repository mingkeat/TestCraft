# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(hwSpeed)

add_library(hwSpeed SHARED src/HwSpeedReport.cpp src/AbstractHwSpeedTest.cpp)

# PUBLIC needed to make both HwSpeedReport.h and HwSpeedReport library available elsewhere in project
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_custom_command(TARGET hwSpeed POST_BUILD 
COMMAND "${CMAKE_COMMAND}" -E copy 
    "$<TARGET_FILE:hwSpeed>"
    "../apps/$<CONFIGURATION>/$<TARGET_FILE_NAME:hwSpeed>" 
COMMENT "Copying to output directory")

add_custom_command(TARGET hwSpeed POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:hwSpeed>"
     "../tests/$<CONFIGURATION>/$<TARGET_FILE_NAME:hwSpeed>" 
  COMMENT "Copying to tests directory")

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(hwSpeed PUBLIC cxx_std_20)