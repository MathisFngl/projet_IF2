cmake_minimum_required(VERSION 3.20)
project(projet_IF2 C)

set(CMAKE_C_STANDARD 11)

set(SDL2_INCLUDE_DIR        SDL/include)
set(SDL2_LIB_DIR            SDL/lib/x64)
set(SDL2_TTF_INCLUDE_DIR    SDL/sdl2-ttf-include)
set(SDL2_TTF_LIB_DIR        SDL/sdl2-ttf-lib)

set(SDL2_FLAGS   "-mwindows -Wl,--no-undefined -static-libgcc")

add_library(SDL2_TTF_DLL    STATIC IMPORTED)
add_library(SDL2_TTF        STATIC IMPORTED)

set_property(TARGET SDL2_TTF_DLL    PROPERTY IMPORTED_LOCATION "${SDL2_TTF_LIB_DIR}/libSDL2_ttf.dll.a")
set_property(TARGET SDL2_TTF        PROPERTY IMPORTED_LOCATION "${SDL2_TTF_LIB_DIR}/libSDL2_ttf.a")

link_directories(${SDL2_LIB_DIR} ${SDL2_LIB_DIR} ${SDL2_TTF_LIB_DIR} ${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
find_library(libSDL2_ttf SDL2_TTF ${SDL2_TTF_INCLUDE_DIR})

add_executable(projet_IF2 src/main.c src/main.h src/init_Plateau.c src/init_Plateau.h src/window.c src/window.h src/main_menu.c src/main_menu.h)
target_link_libraries(projet_IF2 mingw32 SDL2main SDL2 SDL2test SDL2_TTF_DLL SDL2_TTF)