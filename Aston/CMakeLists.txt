project(Aston)

#variables
file(GLOB SRC
        include/aston.cpp)

#linking library's
link_libraries(bitsery)

#include directory
include_directories(include)

#linking files
add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include)



