file(GLOB SOURCES "*.cpp")
 
add_executable(hello ${SOURCES})

target_link_libraries(hello PRIVATE math)

# Add support for external packages
find_package(Boost 1.66.0)  # will search within /usr/lib;/usr/local/lib with the minimum version
# Check for libray, if found print message, include dirs and link libraries.
if(Boost_FOUND)
    message("Boost Found")
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(hello ${Boost_LIBRARIES})
elseif(NOT Boost_FOUND)
    error("Boost Not Found")
endif()