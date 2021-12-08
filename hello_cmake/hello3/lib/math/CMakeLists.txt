
#Bring the headers inside the folder, such as operations.hpp into the project
include_directories(inc)

#Compile all cpp files
file(GLOB SOURCES "src/*.cpp")

# Another way is to list the files individually
# set(SOURCES 
#       src/operations.cpp 
#       inc/operations.cpp)
# This is good if we want to exclude some files during compilation
 

add_library(math SHARED ${SOURCES})

# With this line, we need not to specify the full path of hte inlude like so:
# #include "../lib/math/inc/operations.hpp"
# Instead, we just say
# #include "operations.hpp"
target_include_directories(math PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")

target_compile_definitions(math PRIVATE SAY_HELLO_VERSION=5)