cmake_minimum_required(VERSION 3.16.3)

project(HELLO VERSION 1.0)

# add adder logic
option(USE_ADDER "A simple lib for adding 2 doubles." ON)
if(USE_ADDER)
    add_subdirectory(adder)

    list(APPEND EXTRA_LIB_DIR "adder")
    list(APPEND EXTRA_INCLUSE_DIR "adder")
    list(APPEND EXTRA_LINKS adder)
endif()


configure_file(Config.h.in Config.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


#download all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
#check all the submodules
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${EXTRA_INCLUSE_DIR}
    PUBLIC external/glfw/include
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE ${EXTRA_LIB_DIR}
    PRIVATE external/glfw/src    
)

target_link_libraries(${PROJECT_NAME} ${EXTRA_LINKS} glfw )


