file(GLOB SOURCES "*.cpp")
 
add_executable(hello ${SOURCES})

target_link_libraries(hello PRIVATE math)