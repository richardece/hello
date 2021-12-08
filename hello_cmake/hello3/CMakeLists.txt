# The output files (exe and lib) are located in separate build folder
# Folder is further subdivided into rel and dbg folders
# This might help conan so that it can seach the files in just one location

# to build, create and cd to build folder
# cmake .. -DCMAKE_BUILD_TYEP=Debug
# make

cmake_minimum_required(VERSION 2.8.9)
project (hello)

# Default build mode is Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#Compiler flags
set(CMAKE_CXX_FLAGS         "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Cmake will place the binary and library to the path specified
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dbg/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dbg/lib)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/rel/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/rel/lib)
endif()

# must add all folders that contain CMakeLists.txt
add_subdirectory(main)
add_subdirectory(lib/math)