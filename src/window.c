#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "window.h"

#define WIDTH 600
#define HEIGHT 600

SDL_Rect renduRectangle(){
    SDL_Rect squareRect;
    squareRect.w = (WIDTH, HEIGHT) / 1.1;
    squareRect.h = (WIDTH, HEIGHT) / 1.1;
    squareRect.x = WIDTH / 2 - squareRect.w / 2;
    squareRect.y = HEIGHT / 2 - squareRect.h / 2;
    return squareRect;
}

int update(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0x0F, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderPresent(renderer);
    return 0;
}

int windowCreation() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'est pas reconnu !\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *window = SDL_CreateWindow("Tablut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

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
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
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