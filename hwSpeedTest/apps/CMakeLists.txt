# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(main)

add_executable(main main.cpp)
# We need hello.h and the hello library
target_link_libraries(main
    PRIVATE hwSpeed)


# Use a relative path from the project root directory
set(HWSPEED_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/hwSpeed/include")

# Optionally, use an environment variable if it's set
# Replace 'HWSPEED_DIR' with the name of your environment variable
if(DEFINED ENV{HWSPEED_DIR})
  set(HWSPEED_INCLUDE_DIR "$ENV{HWSPEED_DIR}/include")
endif()

# Add the include directory
include_directories(${HWSPEED_INCLUDE_DIR})
    

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features(main PUBLIC cxx_std_20)