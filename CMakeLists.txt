cmake_minimum_required(VERSION 3.7.2)
include(./PrecompiledHeader.cmake)
project(valkyrie)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(valkyrie valkyrie.cpp pch.cpp valkyrie.hpp ${SOURCES})

target_include_directories(valkyrie 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)



add_precompiled_header(valkyrie pch.hpp SOURCE_CXX pch.cpp FORCEINCLUDE)