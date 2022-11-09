#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "window.h"

#define WIN_SIZE 800

int update(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, 84, 44, 12, 255);
    SDL_RenderClear(renderer);

    int taille = 9;
    int nb_cases = taille*taille;
    SDL_Rect cases[nb_cases];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(int i=0; i<taille; i++){
        for(int j=0; j<taille; j++){
            cases[(taille*i)+j].y = i*(WIN_SIZE/taille);
            cases[(taille*i)+j].x = j*(WIN_SIZE/taille);
            cases[(taille*i)+j].w = cases[(taille*i)+j].h = WIN_SIZE/taille;
            if((i+j)%2 == 0){
                SDL_RenderFillRects(renderer,&cases[(taille*i)+j],1);
            }
        }
    }
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    return 0;
}

int windowCreation() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'est pas reconnu !\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window *window = SDL_CreateWindow("Tablut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_SIZE, WIN_SIZE, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("La fenêtre ne peut pas être créé !\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Le moteur de rendu ne peut pes être initialisé\n"
               "SDL_Error: %s\n", SDL_GetError());
    }

    bool quit = false;

    while (!quit) {
        SDL_Event e;
        SDL_WaitEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
        update(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}