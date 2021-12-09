cmake_minimum_required(VERSION 3.15)

project(basic LANGUAGES CXX)

add_compile_options(-std=c++11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)   # created via "conan install .."
conan_basic_setup()

add_executable(basic        # executable
    main.cpp                # cpp files
)

target_link_libraries(basic # executable
    PRIVATE ${CONAN_LIBS}   # libraries
)
message("CMAKE_BINARY_DIR:      ${CMAKE_BINARY_DIR}")
message("CONAN_LIBS:            ${CONAN_LIBS}")
