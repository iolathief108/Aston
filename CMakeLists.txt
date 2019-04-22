cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 14)
project(Aston
        VERSION 0.1.0
        LANGUAGES CXX)

add_subdirectory(Aston)
add_subdirectory(vendor/bitsery)
add_subdirectory(vendor/googletest)
add_subdirectory(tests)