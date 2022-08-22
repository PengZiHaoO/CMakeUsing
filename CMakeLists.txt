cmake_minimum_required(VERSION 3.16.3)

project(hello)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(adder)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC adder
    PUBLIC 
)

target_link_directories(${PROJECT_NAME} PRIVATE adder)

target_link_libraries(${PROJECT_NAME} adder)


