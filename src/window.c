#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "window.h"
#include "init_Plateau.h"
#include "parsing.h"
#include "play.h"

#define WIN_SIZE 800

int Update(SDL_Renderer *renderer, int taille, SDL_Rect cases[]) { //créé le fond de la fenêtre (la grille)
    int reste = WIN_SIZE%taille; // sert pour centrer correctement le plateau de jeu
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);
    for(int i=0; i<taille; i++){
        for(int j=0; j<taille; j++){ // Si la case est paire, dessiner d'une couleur, si la case est impaire, le dessiner d'une couleur différente.
            cases[(taille*i)+j].y = i*(WIN_SIZE/taille)+reste/2;
            cases[(taille*i)+j].x = j*(WIN_SIZE/taille)+reste/2;
            cases[(taille*i)+j].w = cases[(taille*i)+j].h = WIN_SIZE/taille;
            if((i+j)%2 == 0){
                SDL_SetRenderDrawColor(renderer, 176, 95, 40, 255);
                SDL_RenderFillRect(renderer,&cases[(taille*i)+j]);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 224, 156, 110, 255);
                SDL_RenderFillRect(renderer,&cases[(taille*i)+j]);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

/*
int FrameUpdate(SDL_Event e, SDL_Renderer *renderer, int nb_cases, SDL_Rect cases[], SDL_Surface* King, SDL_Surface* WhitePawn, SDL_Surface* BlackPawn){
    int x, y;
    SDL_GetMouseState(&x,&y);
    SDL_Point mouse_point;
    mouse_point.x = x;
    mouse_point.y = y;
    HoverEffect(renderer, mouse_point, cases, nb_cases);
}
*/
 // Passe en revue toute les pièces du tableau et vérifie si un index correspond pour les trois tableaux ou le Roi.
void PlacePieces(SDL_Renderer *renderer, SDL_Rect cases[], int TableauNoir[], int TableauBlanc[], int TableauForteresses[], int Roi, int taille){
    int nbPieceBlanche = taille-1;
    int nbPieceNoire = (taille-1)*2;
    int nb_cases = taille*taille;
    SDL_Color color;

    for(int i=0; i<nb_cases; i++){
        color.r = 255; color.g = 255; color.b = 255;
        for(int j=0; j<nbPieceBlanche; j++) {
            if(i==TableauBlanc[j]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }
        color.r = 0; color.g = 0; color.b =0;
        for(int k=0; k<nbPieceNoire; k++){
            if(i==TableauNoir[k]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }
        color.r = 150; color.g = 150; color.b = 150;
        for(int l=0; l<4; l++){
            if(i==TableauForteresses[l]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }
        color.r = 255; color.g = 220; color.b = 125;
        if(i==Roi){
            DrawPiece(renderer, cases[i], color, taille);
        }
    }
    SDL_RenderPresent(renderer);
}

void DrawPiece(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color, int taille){
    // Place une pièce (Un petit carré) à l'emplacement d'une pièce (appelé par PlacePieces)
    if(color.r == 150){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_Rect fillRect;
        fillRect.x = rect.x;
        fillRect.y = rect.y;
        fillRect.w = fillRect.h = (WIN_SIZE/taille);
        SDL_RenderFillRect(renderer,&fillRect);
    }
    else{
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_Rect fillRect;
        fillRect.x = rect.x + (WIN_SIZE/taille)*0.1;
        fillRect.y = rect.y + (WIN_SIZE/taille)*0.1;
        fillRect.w = fillRect.h = (WIN_SIZE/taille)*0.8;
        SDL_RenderFillRect(renderer,&fillRect);
    }
}

int windowCreation(int taille, bool restart) {
    // Fonction Principale : Créé la fenêtre en premier lieu, initialise les tableaux d'index des blancs, noirs et des forteresses
    int nb_cases = taille*taille;
    SDL_Rect cases[nb_cases];

    //Initialise SDL, la librairie graphique.
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Tablut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_SIZE, WIN_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int *TableauNoir = (int*) malloc(((taille-1)*2)*sizeof(int));
    int *TableauBlanc = (int*) malloc((taille-1)*sizeof(int));
    int TableauForteresses[4];
    int tableauPiege[2];
    int Roi;
    int mode=0;
    if(restart == false){
        // Selon le mode de restart, il place les pièces selon les positions de départ...
        Roi = init_Plateau(taille, TableauBlanc, TableauNoir, TableauForteresses,tableauPiege,mode);
        printf("[DEBUG] : Commence a %d\n", taille);
    }
    else{
        //... Ou il les place comme ça l'était dans la partie précédente (charge les positions sauvegardées)
        Roi = parsing_open(TableauBlanc, TableauNoir, TableauForteresses);
    }
    Update(renderer, taille, cases);
    PlacePieces(renderer, cases, TableauNoir, TableauBlanc, TableauForteresses, Roi, taille);
    SDL_RenderPresent(renderer);

    //Boucle principale
    bool quit = false;
    Update(renderer, taille, cases);
    PlacePieces(renderer, cases, TableauNoir, TableauBlanc, TableauForteresses, Roi, taille);
    SDL_RenderPresent(renderer);
    int DepartQuad = -1;
    int couleur = 0;
    while(quit != true) {
        SDL_Event e;
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_QUIT:
                QuitEvent(renderer, window, TableauNoir, TableauBlanc, TableauForteresses, Roi, taille);
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                DepartQuad = GetQuadrant(cases, nb_cases);
                break;
            case SDL_MOUSEBUTTONUP:
                MouseInteraction(DepartQuad, cases, nb_cases, renderer, taille, TableauBlanc, TableauNoir, TableauForteresses, Roi, couleur);

                SDL_RenderClear(renderer);
                Update(renderer,taille,cases);
                PlacePieces(renderer, cases, TableauNoir, TableauBlanc, TableauForteresses, Roi, taille);
                SDL_RenderPresent(renderer);
                break;
        }
        //FrameUpdate(e, renderer, nb_cases, cases, King, White, Black);
    }
    return 0;
}
/*
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
}*/

void QuitEvent(SDL_Renderer *renderer, SDL_Window *window, int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int Roi, int taille) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    parsing_write(TableauNoir, TableauBlanc, TableauForteresses, Roi, taille);
    free(TableauNoir);
    free(TableauBlanc);
    printf("[DEBUG] : Closed Window");
    SDL_Quit();
}

// Lorsque l'on clique sur une case dans un quadrant.
void OnButtonClick(SDL_Rect cases[], int nb_cases, SDL_Renderer *renderer){
    int quadrant = GetQuadrant(cases, nb_cases);
    if(quadrant != -1){
        printf("[DEBUG] : Clicked on the %dth Quadrant\n", quadrant);
    }
}

// Retourne le quadrant sur lequel est la sourie.
int GetQuadrant(SDL_Rect cases[], int nb_cases){
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
    return quadrant;
}

// Regarde si l'intéraction de la sourie est un click ou un click maintenu (dans le cas échéant, jusqu'à quand et où ?
void MouseInteraction(int IndexDepart, SDL_Rect cases[], int nb_cases, SDL_Renderer *renderer, int taille, int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int Roi, int couleur){
    int IndexArrive;
    IndexArrive = GetQuadrant(cases, nb_cases);
    if(IndexDepart != IndexArrive){
        DragPiece(IndexDepart, IndexArrive, taille, TableauBlanc, TableauNoir, TableauForteresses, Roi, couleur);
    }
    else{
        OnButtonClick(cases, nb_cases, renderer);
    }
}

int DragPiece(int IndexDepart, int IndexArrive, int taille, int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int Roi, int couleur) {
    printf("[DEBUG] : Dragged From %d to %d th quadrant\n", IndexDepart, IndexArrive);
    play(IndexArrive, IndexDepart, taille, TableauNoir, TableauBlanc, TableauForteresses, Roi, couleur);
}