This is a basic example of conan usage, based from https://kubasejdak.com/introduction-to-conan-package-manager
It's a cpp project that has dependency on json and fmt libraries.
The dependencies are specified inside conanfile.txt


Steps to build
1. install dependencies with Conan,
    This will download the dependencies from conan-center and will create a file called conanbuildinfo.cmake. Dependencies are described inside either conanfile.txt or conanfile.py. txt is simpler, but not as robust as py. By default, conan uses the py file.
    If you want to use the txt file, use command "conan install ../conanfile.txt"
2. generate build system with CMake,
    CMake will call conan_basic_setup() defined in conanbuildinfo.cmake. A variable called CONAN_LIBS will be created, which groups all the CMake targets that represent installed dependencies. target_link_libraries() will link the dependencies.
3. compile project with make (on Linux machine).

Commands:
$ mkdir build && cd build
$ conan install .. -pr=../profile
$ cmake ..

