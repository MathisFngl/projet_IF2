cmake_minimum_required(VERSION 3.23)
project(projet_IF2 C)

set(CMAKE_C_STANDARD 11)
set(SDL2_INCLUDE_DIR projet_IF2/SDL/include)
set(SDL2_LIB_DIR projet_IF2/SDL/lib/x64)

include_directories(.)

add_executable(projet_IF2
        main.c main.h)
