cmake_minimum_required(VERSION 3.16)
project(Speedye)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)
include_directories(src)

add_executable(Speedye
        .idea/workspace.xml
        src/DESIGNER.cpp
        src/Window.h
        README.md)
