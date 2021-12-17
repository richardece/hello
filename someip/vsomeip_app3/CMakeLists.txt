cmake_minimum_required (VERSION 2.8)
project (vsomeip_app1)
set (CMAKE_CXX_FLAGS "-g -std=c++0x")
set(LD_LIBRARY_PATH /home/ric/cmake/vsomeip/build)

find_package (vsomeip 2.6.0 REQUIRED)
find_package( Boost 1.55 EXACT COMPONENTS system thread log REQUIRED )

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(service-example ../src/service-example.cpp)
target_link_libraries(service-example vsomeip ${Boost_LIBRARIES})

add_executable(client-example ../src/client-example.cpp)
target_link_libraries(client-example vsomeip ${Boost_LIBRARIES})