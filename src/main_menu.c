// MAIN MENU OF TABLUT
#include <stdio.h>
#include <stdbool.h>
#include "init_Plateau.h"
#include "window.h"
#include <SDL.h>
#include <SDL_ttf.h>

int showMenu(SDL_Surface* screen, TTF_Font* font){
    Uint32 time;
    int x,y;
    const int numberOfMenu = 2;
    const char* label[2] = {"Continue", "Exit"};
    SDL_Surface* menus[2];
    bool selected[2] = {0,0};
    SDL_Color color[2] = {{255,255,255}, {255,0,0}};

    menus[0] = TTF_RenderText_Solid(font, label[0], color[0]);
    menus[1] = TTF_RenderText_Solid(font, label[1], color[1]);
    SDL_Rect pos[numberOfMenu];

    pos[0].x=screen -> clip_rect.w/2 - menus[0] -> clip_rect.w/2;
    pos[0].y=screen -> clip_rect.h/2 - menus[0] -> clip_rect.h;
    pos[1].x=screen -> clip_rect.w/2 - menus[1] -> clip_rect.w/2;
    pos[1].y=screen -> clip_rect.h/2 - menus[1] -> clip_rect.h;

    SDL_Event event;
    SDL_WaitEvent(&event);
    bool menuRun = true;
    while(menuRun == true){
        time = SDL_GetTicks();
        switch (event.type) {
            case SDL_QUIT:
                for(int i=0; i<numberOfMenu; i++) {
                    SDL_FreeSurface(menus[i]);
                }
                return 0;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for(int i=0; i<numberOfMenu; i++){

                }
        }
    }
}