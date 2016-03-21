cmake_minimum_required(VERSION 2.8)
project(schedulerUT)

# General
###############################################################################
# Activate C++0x support
add_definitions(-std=c++14)

# Google Mock & Test
###############################################################################
set(GMOCK_HOME "$ENV{GMOCK_HOME}") 
include_directories("${GMOCK_HOME}/googletest/include")
link_directories("${GMOCK_HOME}/lib")

# Unit Tests executable
###############################################################################
set(UT_EXECUTABLE_NAME "unittests")
file(GLOB TEST_FILES "../src/*.cpp")
list(REMOVE_ITEM TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/Simulator.cpp)
list(APPEND TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/QueueTests.cpp)
list(APPEND TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ProcessTests.cpp)
list(APPEND TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_executable("${UT_EXECUTABLE_NAME}" ${TEST_FILES})
target_link_libraries("${UT_EXECUTABLE_NAME}" gtest pthread)
