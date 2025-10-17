cmake_minimum_required(VERSION 4.0)
project(cat C)

set(CMAKE_C_STANDARD 11)

add_executable(

        cat main.c
        game.c
        game.h
        console_utils.h
        console_utils.c
        art_renderer.c
        art_renderer.h
)
