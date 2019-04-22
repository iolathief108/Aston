
project(Aston_tests CXX)

link_libraries(googletest Aston)

file(GLOB SRC basic.cpp)

add_executable(${PROJECT_NAME} ${SRC})
