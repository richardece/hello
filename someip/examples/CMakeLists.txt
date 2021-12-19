# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required (VERSION 2.8)
project (helloworld)

set(EXAMPLE_CONFIG_FILES
    "../config/vsomeip.json"
    "../config/vsomeip-local.json"
    "../config/vsomeip-tcp-client.json"
    "../config/vsomeip-tcp-service.json"
    "../config/vsomeip-udp-client.json"
    "../config/vsomeip-udp-service.json"
)

find_package (vsomeip 2.6.0 REQUIRED)
find_package( Boost 1.55 EXACT COMPONENTS system thread log REQUIRED )

if (NOT vsomeip_FOUND)
    message("vsomeip was not found. Please specify vsomeip_DIR")
endif()

#find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${VSOMEIP_INCLUDE_DIRS})

# Examples
message (status " Boost_LIBRARIES: ${Boost_LIBRARIES}")
add_executable(request-sample request-sample.cpp ${EXAMPLE_CONFIG_FILES})
target_link_libraries(request-sample vsomeip ${Boost_LIBRARIES} ${DL_LIBRARY})

add_executable(response-sample response-sample.cpp ${EXAMPLE_CONFIG_FILES})
target_link_libraries(response-sample vsomeip ${Boost_LIBRARIES} ${DL_LIBRARY} ${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(subscribe-sample subscribe-sample.cpp ${EXAMPLE_CONFIG_FILES})
target_link_libraries(subscribe-sample vsomeip ${Boost_LIBRARIES} ${DL_LIBRARY})

add_executable(notify-sample notify-sample.cpp ${EXAMPLE_CONFIG_FILES})
target_link_libraries(notify-sample vsomeip ${Boost_LIBRARIES} ${DL_LIBRARY})

#add_dependencies(examples request-sample response-sample subscribe-sample notify-sample)

#install (
#    TARGETS request-sample response-sample subscribe-sample notify-sample
#    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
#)

###################################################################################################
