#CMaeke powered build system for data structures.
#Create by JungJin Park
#First draft is 21. Sep. 2019


message("Using CMake version ${CMAKE_VERSION}")
message("Before 'project':")
message("  C: '${CMAKE_C_COMPILER}'")
message("  C++: '${CMAKE_CXX_COMPILER}'")
message("  Source: ${PROJECT_SOURCE_DIR}")
message("  Binary: ${PROJECT_BINARY_DIR}")
message("  Version: ${PROJECT_VERSION}")
message("  Version (alt): ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
cmake_minimum_required(VERSION 3.0)

project(Week_5_Assignment_3 CXX )
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -o -Wall -std=c++17 ")
set ( CMAKE_EXE_LINKER_FLAGS "-Wl" )

set(SOURCE_FILES
        main.cpp
        ../complex_jin/complex_jin.cpp ../complex_jin/complex_jin.hpp)

set(CMKAE_VERBOSE_MAKEFILE ON)



set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
add_executable(main ${SOURCE_FILES} )

target_link_libraries(main)
