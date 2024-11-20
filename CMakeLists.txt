cmake_minimum_required(VERSION 3.26)
project(projet_TDC C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(projet_TDC
        head.h
        main.c
        menu.c
        sous.c)
