cmake_minimum_required(VERSION 3.20)
project(projet_IF2 C)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR SDL/include)
set(SDL2_LIB_DIR SDL/lib/x64)

set(SDL2_TTF_INCLUDE_DIR SDL/sdl2-ttf-include)
set(SDL2_TTF_LIB_DIR SDL/sdl2-ttf-lib)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_TTF_LIB_DIR} ${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${SDL2_LIB_DIR} )

add_executable(projet_IF2 src/main.c src/main.h src/init_Plateau.c src/init_Plateau.h src/window.c src/window.h src/main_menu.c src/main_menu.h)

target_link_libraries(projet_IF2 SDL2main SDL2 SDL2test libSDL2_ttf)