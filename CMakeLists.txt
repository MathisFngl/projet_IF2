cmake_minimum_required(VERSION 3.20)
project(projet_IF2 C)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR SDL/include)
set(SDL2_LIB_DIR SDL/lib/x64)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${SDL2_LIB_DIR} )

add_executable(projet_IF2 src/main.c src/main.h src/init_Plateau.c src/init_Plateau.h src/window.c src/window.h src/play.c src/play.h src/menu.c src/menu.h src/parsing.c src/parsing.h)

target_link_libraries(projet_IF2 SDL2main SDL2 SDL2test)