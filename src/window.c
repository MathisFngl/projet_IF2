#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "window.h"
#include "init_Plateau.h"
#include "parsing.h"
#include "play.h"
#include "menu.h"

#define WIN_SIZE 800

int Update(SDL_Renderer *renderer, int taille, SDL_Rect cases[], int couleur) { //créé le fond de la fenêtre (la grille)
    int reste = WIN_SIZE%taille ; // sert pour centrer correctement le plateau de jeu
    couleur == 1 ? SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) : SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
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

 // Passe en revue toutes les pièces du tableau et vérifie si un index correspond pour les trois tableaux ou le Roi.
void PlacePieces(SDL_Renderer *renderer, SDL_Rect cases[], int TableauNoir[], int TableauBlanc[], int TableauForteresses[], int TableauPiege[] , int Roi, int taille){
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
        color.r = 0; color.g = 0; color.b = 210;
        for(int m=0; m<2; m++){
            if(i==TableauPiege[m]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }
        color.r = 210; color.g = 189; color.b = 41;
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

int windowCreation(int taille, bool difficile, bool restart) {
    // Fonction Principale : Créé la fenêtre en premier lieu, initialise les tableaux d'index des blancs, noirs et des forteresses
    int nb_cases = taille*taille;
    SDL_Rect cases[nb_cases];

    //Initialise SDL, la librairie graphique.
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Tablut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_SIZE, WIN_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int *TableauNoir = (int*) malloc(((taille-1)*2)*sizeof(int));
    int *TableauBlanc;

    if(taille == 11){
        TableauBlanc = (int*) malloc(8*sizeof(int));
    }
    else{
        TableauBlanc = (int*) malloc((taille-1)*sizeof(int));
    }
    int TableauForteresses[4];
    int TableauPieges[2];
    int Roi;
   if(restart == false) {
        Roi = init_Plateau(taille, TableauBlanc, TableauNoir, TableauForteresses, TableauPieges, difficile);
        printf("[DEBUG] : Commence a %d\n", taille);
    }
    else{
        //... Ou il les place comme ça l'était dans la partie précédente (charge les positions sauvegardées)
        Roi = parsing_open(TableauBlanc, TableauNoir, TableauForteresses, TableauPieges, &difficile);
    }
    int couleur = 0;
    int* pCouleur = &couleur;
    //Boucle principale

    bool quit = false;
    Update(renderer, taille, cases, couleur);
    PlacePieces(renderer, cases, TableauNoir, TableauBlanc, TableauForteresses,TableauPieges, Roi, taille);
    SDL_RenderPresent(renderer);
    int DepartQuad = -1;
    while(quit != true) {
        SDL_Event e;
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_QUIT:
                QuitEvent(0, renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, difficile, Roi, taille);
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                DepartQuad = GetQuadrant(cases, nb_cases);
                break;
            case SDL_MOUSEBUTTONUP:
                MouseInteraction(DepartQuad, window, cases, nb_cases, renderer, taille, TableauBlanc, TableauNoir, TableauForteresses, TableauPieges, difficile, &Roi, &couleur);

                SDL_RenderClear(renderer);
                Update(renderer,taille,cases, couleur);
                PlacePieces(renderer, cases, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, Roi, taille);
                SDL_RenderPresent(renderer);
                isWin(renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, difficile, Roi, taille);
                break;
        }
    }
    return 0;
}

void isWin(SDL_Renderer *renderer, SDL_Window *window, int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int TableauPieges[], bool difficile, int Roi, int taille){
    bool restePiecesNoires = false;
    bool roiSurForteresse = false;
    for(int i = 0; i<((taille-1)/2)*4; i++){
        if(TableauNoir[i] != -1){
            restePiecesNoires = true;
        }
    }
    for(int i = 0; i<4; i++){
        if(Roi == TableauForteresses[i]){
            roiSurForteresse = true;
        }
    }
    if(Roi == -1){
        QuitEvent(2, renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, difficile, Roi, taille);
        printf("\n======================\n");
        printf("Victoire des Noirs !\n");
        printf("======================\n\n");
    }
    if(restePiecesNoires == false || roiSurForteresse == true){
        if(roiSurForteresse == true){ printf("Oui");}
        if(restePiecesNoires == false){ printf("Oui noir");}
        printf("\n======================\n");
        printf("Victoire des Blancs !\n");
        printf("======================\n\n");
        QuitEvent(1, renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, difficile, Roi, taille);
    }
}

void QuitEvent(int EndState, SDL_Renderer *renderer, SDL_Window *window, int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int TableauPieges[],bool difficile, int Roi, int taille) {
    switch (EndState) {
        case 0:
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            parsing_write(TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, difficile, Roi ,taille);
            free(TableauNoir);
            free(TableauBlanc);
            printf("[DEBUG] : Closed Window\n");
            SDL_Quit();
            break;
        case 1:
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            free(TableauBlanc);
            free(TableauNoir);
            SDL_Quit();
            parsing_write_stats(1);
            StatsMenu();
            printf("[DEBUG] : Closed Window\n");
            break;
        case 2:
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            free(TableauBlanc);
            free(TableauNoir);
            SDL_Quit();
            printf("[DEBUG] : Closed Window\n");
            parsing_write_stats(2);
            StatsMenu();
            break;
        default:
            break;
    }
}

// Lorsque l'on clique sur une case dans un quadrant.
void OnButtonClick(SDL_Rect cases[], int nb_cases){
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

// Regarde si l'intéraction de la souris est un click ou un click maintenu (dans le cas échéant, jusqu'à quand et où ?
void MouseInteraction(int IndexDepart, SDL_Window *window, SDL_Rect cases[], int nb_cases, SDL_Renderer *renderer, int taille, int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int* TableauPieges, bool difficile, int* Roi, int* pCouleur){
    int IndexArrive;
    IndexArrive = GetQuadrant(cases, nb_cases);
    if(IndexDepart != IndexArrive) {
        DragPiece(IndexDepart, IndexArrive, taille, TableauBlanc, TableauNoir, TableauForteresses, Roi, pCouleur);
    }
    else{
        OnButtonClick(cases, nb_cases);
    }
}

int DragPiece(int IndexDepart, int IndexArrive, int taille, int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int* Roi, int* pCouleur) {
    printf("[DEBUG] : Dragged From %d to %d th quadrant\n", IndexDepart, IndexArrive);
    int returned_value = play(IndexArrive, IndexDepart, taille, TableauNoir, TableauBlanc, TableauForteresses, *Roi, pCouleur);
    if(returned_value != -2){
        *Roi = returned_value;
        if(*pCouleur == 0){
            *pCouleur = 1;
        }
        else{
            *pCouleur = 0;
        }
    }
}