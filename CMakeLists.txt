cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES
        vars/stable.cpp
        vars/stable.h
        exp/exp.h
        exp/expression_types.h
        main.cpp
        exceptions.h
        algorithms/shunting_yard_algorithm.h
        algorithms/shunting_yard_algorithm.cpp)

add_executable(Project ${SOURCES} vars/data_reader_server.cpp vars/data_reader_server.h algorithms/lexer.cpp algorithms/lexer.h algorithms/definitions.h)