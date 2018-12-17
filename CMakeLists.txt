cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES
        vars/stable.cpp
        vars/stable.h
        main.cpp
        exceptions.h)

add_executable(Project ${SOURCES})