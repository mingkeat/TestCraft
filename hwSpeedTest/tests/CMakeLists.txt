cmake_minimum_required(VERSION 3.15)

include(FetchContent)
include(GoogleTest)
include(CTest)

enable_testing()

# Force GoogleTest to use the shared (DLL) runtime library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  if(MSVC)
    add_compile_options(/MD$<$<CONFIG:Debug>:d>)
  endif()   # MSVC
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()     # NOT googletest_POPULATED

#The following optional code will keep the CACHE cleaner
mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

#The following optional code will group the targets in IDEs like Visual Studio  that support folders clean
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

# Use a relative path from the project root directory
set(HWSPEEDUNITTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/tests")

# Optionally, use an environment variable if it's set
# Replace 'HWSPEED_DIR' with the name of your environment variable
if(DEFINED ENV{HWSPEED_UNITTEST_DIR})
  set(HWSPEEDUNITTEST_INCLUDE_DIR "$ENV{HWSPEED_UNITTEST_DIR}")
endif()

# Add the include directory
include_directories(${HWSPEED_INCLUDE_DIR})

#The following include and macro allows us to quickly add tests with libraries to the project
macro(package_add_test_with_libraries TESTEXECUTABLE FILES LIBRARIES TEST_WORKING_DIRECTORY)
    add_executable(${TESTEXECUTABLE} ${FILES})
    target_link_libraries(${TESTEXECUTABLE} gtest gmock gtest_main ${LIBRARIES})
    gtest_discover_tests(${TESTEXECUTABLE}
        WORKING_DIRECTORY ${TEST_WORKING_DIRECTORY}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
    )
    set_target_properties(${TESTEXECUTABLE} PROPERTIES FOLDER tests)
endmacro()

package_add_test_with_libraries(HwSpeedReportTests HwSpeedReportTests.cpp hwSpeed "${PROJECT_DIR}")