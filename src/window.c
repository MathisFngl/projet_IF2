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
    //Génère la grille dans le renderer
    // (x, y) : Origine du carré
    // (w, h) : width (largeur) height (longeur) qui sont les même puisque c'est un carré
    for(int i=0; i<taille; i++){
        for(int j=0; j<taille; j++){
            cases[(taille*i)+j].y = i*(WIN_SIZE/taille)+reste/2;
            cases[(taille*i)+j].x = j*(WIN_SIZE/taille)+reste/2;
            cases[(taille*i)+j].w = cases[(taille*i)+j].h = WIN_SIZE/taille;

            // Si la case est paire, dessiner d'une couleur, si la case est impaire, le dessiner d'une couleur différente.
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
    int nbPieceBlanche = ((taille-1)/4)*4;
    int nbPieceNoire = (taille-1)*2;
    int nb_cases = taille*taille;
    SDL_Color color;


    for(int i=0; i<nb_cases; i++){

        // Si l'index du tableau principal correspond a un emplacement dans le tableau des ...

        //Blancs
        color.r = 255; color.g = 255; color.b = 255;
        for(int j=0; j<nbPieceBlanche; j++) {
            if(i==TableauBlanc[j]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }

        //Noirs
        color.r = 0; color.g = 0; color.b =0;
        for(int k=0; k<nbPieceNoire; k++){
            if(i==TableauNoir[k]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }

        //Forteresses
        color.r = 150; color.g = 150; color.b = 150;
        for(int l=0; l<4; l++){
            if(i==TableauForteresses[l]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }

        //Pieges
        color.r = 0; color.g = 0; color.b = 210;
        for(int m=0; m<2; m++){
            if(i==TableauPiege[m]){
                DrawPiece(renderer, cases[i], color, taille);
            }
        }

        //Roi
        color.r = 210; color.g = 189; color.b = 41;
        if(i==Roi){
            DrawPiece(renderer, cases[i], color, taille);
        }
    }
    SDL_RenderPresent(renderer);
}

void DrawPiece(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color, int taille){
    // Place une pièce (Un petit carré) à l'emplacement d'une pièce (appelé par PlacePieces)

    // Si la pièce est spécifiquement une forteresse alors la case entière sera coloriée (La forteresse est la seule pièce ayant une valeur de rouge de 150) :
    if(color.r == 150){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_Rect fillRect;
        fillRect.x = rect.x;
        fillRect.y = rect.y;
        fillRect.w = fillRect.h = (WIN_SIZE/taille);
        SDL_RenderFillRect(renderer,&fillRect);
    }
    // Sinon remplir de la couleur choisie avec un carré plus petit centré dans la case :
    else{
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_Rect fillRect;
        fillRect.x = rect.x + (WIN_SIZE/taille)*0.1;
        fillRect.y = rect.y + (WIN_SIZE/taille)*0.1;
        fillRect.w = fillRect.h = (WIN_SIZE/taille)*0.8;
        SDL_RenderFillRect(renderer,&fillRect);
    }
}

int windowCreation(int taille, bool difficile, bool restart, int couleur) {
    // Fonction Principale : Créé la fenêtre en premier lieu, initialise les tableaux d'index des blancs, noirs et des forteresses
    int nb_cases = taille*taille;
    SDL_Rect cases[nb_cases];

    //Initialise SDL, la librairie graphique.
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Tablut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_SIZE, WIN_SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialise tous les tableaux dont nous nous servirons
    int *TableauNoir = (int*) malloc(((taille-1)*2)*sizeof(int));
    int *TableauBlanc = (int*) malloc(((taille-1)/4)*4*sizeof(int));
    int TableauForteresses[4];
    int TableauPieges[2];
    int Roi;

    // Si une partie est reprise alors nous lisons ce qui est dans la sauvegarde, sinon nous générons un tableau comme en début de partie.
   if(restart == false) {
        Roi = init_Plateau(taille, TableauBlanc, TableauNoir, TableauForteresses, TableauPieges, difficile);
        printf("[DEBUG] : Commence a %d\n", taille);
    }
   else{
        //... Ou il les place comme ça l'était dans la partie précédente (charge les positions sauvegardées)
        Roi = parsing_open(TableauBlanc, TableauNoir, TableauForteresses, TableauPieges, &couleur);
   }


    bool quit = false;

   // Initialisation de la première frame
    Update(renderer, taille, cases, couleur);
    PlacePieces(renderer, cases, TableauNoir, TableauBlanc, TableauForteresses,TableauPieges, Roi, taille);
    SDL_RenderPresent(renderer);

    int DepartQuad = -1;

    //Boucle principale
    while(quit != true) {
        SDL_Event e;
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_QUIT: // Si le Joueur quitte avec le bouton de l'UI de la fenêtre :
                QuitEvent(0, renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, Roi,
                          taille, couleur);
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN: // Si le Joueur PRESSE le bouton gauche de la sourie :
                DepartQuad = GetQuadrant(cases, nb_cases);
                break;
            case SDL_MOUSEBUTTONUP: // Si le joueur RELACHE le bouton gauche de la sourie :
                MouseInteraction(DepartQuad, cases, nb_cases, taille, TableauBlanc, TableauNoir, TableauForteresses,
                                 TableauPieges, &Roi, &couleur);

                SDL_RenderClear(renderer);
                Update(renderer, taille, cases, couleur);
                PlacePieces(renderer, cases, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, Roi, taille);
                SDL_RenderPresent(renderer);

                // Si une condition de victoire est respectée, alors la boule de jeu est brisée
                if (isWin(renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, Roi, taille,
                          couleur) == -1) {
                    quit = true;
                }
        }
    }
    return 0;
}

int isWin(SDL_Renderer *renderer, SDL_Window *window, int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int TableauPieges[], int Roi, int taille, int couleur){
    bool restePiecesNoires = false;
    bool roiSurForteresse = false;

    //Vérifie s'il reste des pièces noires dans le jeu (Si au moins une pièce n'est pas en position -1)
    for(int i = 0; i<((taille-1)/2)*4; i++){
        if(TableauNoir[i] != -1){
            restePiecesNoires = true;
        }
    }
    //Vérifie si le roi est sur une forteresse (si sa position n'est pas la même que celle d'une forteresse)
    for(int i = 0; i<4; i++){
        if(Roi == TableauForteresses[i]){
            roiSurForteresse = true;
        }
    }

    // Si le roi est mangé (= à -1) :
    if(Roi == -1){
        printf("\n======================\n");
        printf("Victoire des Noirs !\n");
        printf("======================\n\n");
        QuitEvent(2, renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges,  Roi, taille, couleur);
        return -1;
    }

    // Si soit le roi est sur une forteresse, soit il n'y a plus de pions noirs :
    if(restePiecesNoires == false || roiSurForteresse == true){
        printf("\n======================\n");
        printf("Victoire des Blancs !\n");
        printf("======================\n\n");
        QuitEvent(1, renderer, window, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges,  Roi, taille, couleur);
        return -1;
    }
    return 0;
}

void QuitEvent(int EndState, SDL_Renderer *renderer, SDL_Window *window, int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int TableauPieges[], int Roi, int taille, int couleur) {

    // Les Endstates définissent toute les possibilités de fin de partie
    // Enstate = 0 : Partie non terminée, à sauvegarder
    // Enstate = 1 : Victoire des Blancs
    // Enstate = 2 : Victoire des Noirs

    switch (EndState) {
        case 0:
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            parsing_write(TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, Roi ,taille, couleur);
            free(TableauNoir);
            free(TableauBlanc);
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
            break;
        case 2:
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            free(TableauBlanc);
            free(TableauNoir);
            SDL_Quit();
            parsing_write_stats(2);
            StatsMenu();
            break;
        default:
            break;
    }
}

// Lorsque l'on clique sur une case dans un quadrant.
// Cette fonction sert uniquement au debug
void OnButtonClick(SDL_Rect cases[], int nb_cases){
    int quadrant = GetQuadrant(cases, nb_cases);
    if(quadrant != -1){
        //printf("[DEBUG] : Clicked on the %dth Quadrant\n", quadrant);
    }
}

// Retourne le quadrant sur lequel est la sourie.
int GetQuadrant(SDL_Rect cases[], int nb_cases){
    int x, y, quadrant = -1;
    SDL_GetMouseState(&x,&y);
    SDL_Point mouse_point;
    mouse_point.x = x;
    mouse_point.y = y;
    // Passe en revue toute les cases jusqu'à trouver celle sur laquelle se situe la sourie
    for(int i = 0; i<nb_cases; i++){
        if(SDL_PointInRect(&mouse_point, &cases[i])){
            quadrant = i;
        }
    }
    return quadrant;
}

// Regarde si l'intéraction de la souris est un click ou un click maintenu sur une autre case (dans le cas échéant, jusqu'où)
void MouseInteraction(int IndexDepart, SDL_Rect cases[], int nb_cases, int taille, int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int* TableauPieges, int* Roi, int* pCouleur){
    int IndexArrive;
    IndexArrive = GetQuadrant(cases, nb_cases);
    if(IndexDepart != IndexArrive) {
        DragPiece(IndexDepart, IndexArrive, taille, TableauBlanc, TableauNoir, TableauForteresses, TableauPieges, Roi, pCouleur);
    }
    else{
        OnButtonClick(cases, nb_cases);
    }
}

// Vérifie si le coup est faisable, dans ce cas, le tableau est modifié pour refléter les changements et la couleur change (donc le tour est au joueur suivant)
int DragPiece(int IndexDepart, int IndexArrive, int taille, int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int* TableauPieges, int* Roi, int* pCouleur) {
    printf("[DEBUG] : Dragged From %d to %d th quadrant\n", IndexDepart, IndexArrive);
    int returned_value = play(IndexArrive, IndexDepart, taille, TableauNoir, TableauBlanc, TableauForteresses, TableauPieges, *Roi, pCouleur);
    if(returned_value != -2){
        *Roi = returned_value;
        *pCouleur == 0 ? (*pCouleur = 1) : (*pCouleur = 0);
    }
}