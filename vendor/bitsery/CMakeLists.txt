project(bitsery)

file(GLOB SRC
        include/bitsery.cpp)

add_library(${PROJECT_NAME} ${SRC})


target_include_directories(${PROJECT_NAME} PUBLIC include/)
