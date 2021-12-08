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
# set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH     ${CMAKE_BINARY_DIR}/lib)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dbg/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dbg/lib)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/rel/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/rel/lib)
endif()

add_executable(hello helloworld.cpp)

message("CMAKE_BINARY_DIR:      ${CMAKE_BINARY_DIR}")
message("CMAKE_HOME_DIRECTORY:  ${CMAKE_HOME_DIRECTORY}")
message("CMAKE_SOURCE_DIR:      ${CMAKE_SOURCE_DIR}")
message("CMAKE_INCLUDE_PATH:    ${CMAKE_INCLUDE_PATH}")
message("CXXFLAGS:              ${CXXFLAGS}")
message("CMAKE_CXX_STANDARD:    ${CMAKE_CXX_STANDARD}")
message("CMAKE_BUILD_TYPE:      ${CMAKE_BUILD_TYPE}")

message("CMAKE_SYSTEM:          ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_NAME:     ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_VERSION:  ${CMAKE_SYSTEM_VERSION}")
message("CMAKE_SYSTEM_PROCESSOR:${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_HOST_SYSTEM_NAME:${CMAKE_HOST_SYSTEM_NAME}")
 
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY:    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY:    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

