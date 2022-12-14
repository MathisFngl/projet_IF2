//
// Created by Utilisateur on 20/11/2022.
//

#include <stdbool.h>

#ifndef PROJET_IF2_PLAY_H
#define PROJET_IF2_PLAY_H
bool sameCase(int king, int *pieceBlanche, int *pieceNoire, int *forteresse,int nbPieceBlanche, int nbPieceNoire,int IndexArrive, int IndexDepart, int *pieges);
bool mouvement(int IndexArrive, int IndexDepart,int taille,int *pieceBlanche,int *pieceNoire,int nbPieceBlanche, int nbPieceNoire, int *forteresse,int king,int *pieges);
int pionMange(int IndexArrive,int IndexDepart, int c, int* pieceBlanche, int* pieceNoire, int nbPieceBlanche, int nbPieceNoire,int *pieges,int taille,int king);
int movPieces(int IndexDepart,int IndexArrive, int *pieceNoire, int *pieceBlanche, int king,int c, int nbPieceBlanche, int nbPieceNoire);
int play(int IndexArrive,int IndexDepart,int taille,int *pieceNoire, int *pieceBlanche,int *forteresse, int *pieges, int king, int* c);

#endif //PROJET_IF2_PLAY_H

