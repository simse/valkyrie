cmake_minimum_required(VERSION 3.7.2)
include(./PrecompiledHeader.cmake)
project(valkyrie)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/**/*.cpp")
add_executable(valkyrie valkyrie.cpp pch.cpp valkyrie.hpp ${SOURCES})

target_include_directories(valkyrie 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
