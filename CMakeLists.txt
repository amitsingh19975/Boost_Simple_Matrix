project (Simple_Matrix)
cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "bin"
) 
add_executable(Simple_Matrix main.cpp) 