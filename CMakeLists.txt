cmake_minimum_required(VERSION 3.31)
project(text_editor C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_executable(text_editor procedural/main.c
        procedural/command_funcs.c
        procedural/header.h
        procedural/memory_handling.c)

add_executable(text_editor_cpp oop/main.cpp
        oop/TextEditor.cpp
        oop/TextEditor.h
        oop/utils.cpp
        oop/utils.h
        oop/CharArray.cpp
        oop/CharArray.h
        oop/CharPointerArray.cpp
        oop/CharPointerArray.h
        oop/Commands.cpp
        oop/Commands.h
)
