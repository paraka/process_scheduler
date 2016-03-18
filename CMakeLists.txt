cmake_minimum_required (VERSION 2.8.11)
project(Scheduler)
find_package (Threads)

# We need C++ 14
if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.0)
  # CMake 3.1 has built-in CXX standard checks.
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED on)
else ()
  if (CMAKE_COMPILER_IS_GNUCXX)
    message ("Assuming that GNU CXX uses -std=c++14 flag for C++14 compatibility.")
    list(APPEND CMAKE_CXX_FLAGS "-std=c++14")
  else()
    message ("No CMAKE C++14 check. If the build breaks, you're on your own.")
  endif()
endif ()

set(SCHEDULER_SRCS 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/Process.cpp 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/Simulator.cpp)

add_executable(ProcessSchedulerSimulator ${SCHEDULER_SRCS})
target_link_libraries(ProcessSchedulerSimulator ${CMAKE_THREAD_LIBS_INIT})
