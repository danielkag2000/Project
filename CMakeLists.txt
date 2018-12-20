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
        algorithms/shunting_yard_algorithm.cpp
        algorithms/parsing.h
        algorithms/parsing.cpp
        exp/command_expression.h
        command/command.h
        definitions.h
        exp/command_expression.h
        command/simple_commands.h
        command/complicate_commands.h
        exp/expression_map.h
        command/server_command.h
        command/server_command.cpp)

add_executable(Project ${SOURCES} vars/data_reader_server.cpp vars/data_reader_server.h algorithms/lexer.cpp algorithms/lexer.h definitions.h)