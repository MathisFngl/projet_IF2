#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "window.h"

#define WIN_SIZE 684

int InitUpdate(SDL_Renderer *renderer, int taille, SDL_Rect cases[]) {
    SDL_SetRenderDrawColor(renderer, 224, 156, 110, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 176, 95, 40, 255);
    for(int i=0; i<taille; i++){
        for(int j=0; j<taille; j++){
            cases[(taille*i)+j].y = i*(WIN_SIZE/taille);
            cases[(taille*i)+j].x = j*(WIN_SIZE/taille);
            cases[(taille*i)+j].w = cases[(taille*i)+j].h = WIN_SIZE/taille;
            if((i+j)%2 == 0){
                SDL_RenderFillRect(renderer,&cases[(taille*i)+j]);
            }
        }
    }
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

int FrameUpdate(SDL_Event e, SDL_Renderer *renderer, int nb_cases, SDL_Rect cases[], SDL_Surface* King, SDL_Surface* WhitePawn, SDL_Surface* BlackPawn){
    int x, y;
    SDL_GetMouseState(&x,&y);
    SDL_Point mouse_point;
    mouse_point.x = x;
    mouse_point.y = y;
    HoverEffect(renderer, mouse_point, cases, nb_cases);
}

void PlacePieces(SDL_Renderer *renderer, int nb_cases, SDL_Rect rect, SDL_Texture *texture){
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    SDL_RenderPresent(renderer);
    printf("[DEBUG] : Surface placed \n");
}

void LoadTextures(SDL_Surface *White, SDL_Surface *Black, SDL_Surface *King){

    King = SDL_LoadBMP("assets/textures/king.bmp");
    if(King == NULL){ printf("[DEBUG] : King failed to load : %s\n",  SDL_GetError());}

    White = SDL_LoadBMP("assets/textures/whitepawn.bmp");
    if(King == NULL){ printf("[DEBUG] : White failed to load : %s\n",  SDL_GetError());}

    White = SDL_LoadBMP("src/assets/textures/blackpawn.bmp");
    if(King == NULL){ printf("[DEBUG] : Black failed to load : %s\n",  SDL_GetError());}
}

int windowCreation() {
    int taille = 9;
    int nb_cases = taille*taille;
    SDL_Rect cases[nb_cases];

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Tablut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_SIZE, WIN_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *White = NULL;
    SDL_Texture *KingTexture = NULL;
    SDL_Surface *Black = NULL;
    SDL_Texture *WhiteTexture = NULL;
    SDL_Surface *King = NULL;
    SDL_Texture *BlackTexture = NULL;
    LoadTextures(White, Black, King);

    //Boucle principale
    bool quit = false;
    SDL_RenderCopy(renderer,InitUpdate(renderer, taille, cases), NULL, NULL);
    SDL_RenderPresent(renderer);
    while(quit != true) {
        SDL_Event e;
        SDL_WaitEvent(&e);
        FrameUpdate(e, renderer, nb_cases, cases, King, White, Black);
        switch (e.type) {
            case SDL_QUIT: QuitEvent(renderer, window); quit = true; break;
            case SDL_MOUSEBUTTONDOWN: OnButtonClick(cases, nb_cases, King, White, Black, renderer);
        }
    }
    return 0;
}

void HoverEffect(SDL_Renderer* renderer, SDL_Point mouse_point, SDL_Rect cases[], int nb_cases){
    for (int i=0; i<nb_cases; i++) {
        if (SDL_PointInRect(&mouse_point, &cases[i]) == true) {
            if((i)%2 == 0){
                SDL_SetRenderDrawColor(renderer, 196, 115, 60, 255);
                SDL_RenderFillRect(renderer,&cases[i]);
                SDL_RenderPresent(renderer);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 244, 176, 130, 255);
                SDL_RenderFillRect(renderer,&cases[i]);
                SDL_RenderPresent(renderer);
            }
        }
        else{
            if((i)%2 == 0){
                SDL_SetRenderDrawColor(renderer, 176, 95, 40, 255);
                SDL_RenderFillRect(renderer,&cases[i]);
                SDL_RenderPresent(renderer);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 224, 156, 110, 255);
                SDL_RenderFillRect(renderer,&cases[i]);
                SDL_RenderPresent(renderer);
            }
        }
    }
}

void QuitEvent(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("[DEBUG] : Closed Window");
    SDL_Quit();
}

int OnButtonClick(SDL_Rect cases[], int nb_cases, SDL_Surface *King, SDL_Surface *WhitePawn, SDL_Surface *BlackPawn, SDL_Renderer *renderer){
    int x, y, quadrant = -1;
    SDL_GetMouseState(&x,&y);
    SDL_Point mouse_point;
    mouse_point.x = x;
    mouse_point.y = y;
    for(int i = 0; i<nb_cases; i++){
        if(SDL_PointInRect(&mouse_point, &cases[i])){
            quadrant = i;
        }
    }
    if(quadrant != -1){
        printf("[DEBUG] : Left Mouse Button clicked at x = %d, y = %d in the %d th quadrant\n", x, y, quadrant);
        PlacePieces(renderer, nb_cases, cases[quadrant], King);
        return quadrant;
    }
    else{
        printf("[DEBUG] : Left Mouse Button clicked at x = %d, y = %d and was outside the grid\n", x, y);
    }
}