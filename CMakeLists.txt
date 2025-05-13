cmake_minimum_required(VERSION 3.31)
project(text_editor C)

set(CMAKE_C_STANDARD 11)

add_executable(text_editor main.c
        command_funcs.c
        header.h
        memory_handling.c)
