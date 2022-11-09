//#include <stdint.h>
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

int windowCreation(){

}

int update(SDL_Renderer* renderer, SDL_Rect squareRect) {
    SDL_Event e;
    SDL_WaitEvent(&e);

    if (e.type == SDL_QUIT) {
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &squareRect);
    SDL_RenderPresent(renderer);
    return 0;
}

int main(int argc, char* argv[]) {
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not be initialized!\n"
                   "SDL_Error: %s\n", SDL_GetError());
            return 0;
        }

        SDL_Window *window = SDL_CreateWindow("Tablut",
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              WIDTH, HEIGHT,
                                              SDL_WINDOW_SHOWN);

        if (!window) {
            printf("La fenêtre ne peut pas être créé !\n"
                   "SDL_Error: %s\n", SDL_GetError());
        } else {
            SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                printf("Le moteur de rendu ne peut pes être initialisé\n"
                       "SDL_Error: %s\n", SDL_GetError());
            } else {
                SDL_Rect squareRect;

                squareRect.w = (WIDTH, HEIGHT) / 1.5;
                squareRect.h = (WIDTH, HEIGHT) / 1.5;

                squareRect.x = WIDTH / 2 - squareRect.w / 2;
                squareRect.y = HEIGHT / 2 - squareRect.h / 2;

                bool quit = false;

                while (!quit) {
                    if(update(renderer, squareRect) == 1){
                        quit = true;
                    }
                }
                SDL_DestroyRenderer(renderer);
            }
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
        return 0;
    }
}