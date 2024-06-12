cmake_minimum_required(VERSION 3.10)
project(my_encrypt_tool)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
add_subdirectory(tests)

include_directories(include)
