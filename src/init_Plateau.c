//
// Created by Utilisateur on 09/11/2022.
//

#include "init_Plateau.h"
#include <stdlib.h>
#include <stdio.h>

int init_Plateau(){
    int N,i,k;
    printf("Dimension:");
    scanf("%d",&N);
    int king;
    king=N/2+(N/2)*9;
    // création plateau
    int nbCase = N*N;
    int* plateau = (int*) malloc(sizeof (int)*nbCase );
    for (i=0; i<nbCase; i++)
    {
        plateau[i] = i;
    }

    int nbPieceBlanche = N-1;
    int nbPieceNoire = (N-1)*2;
    //création coordonné piece blanche : on part du haut puis sens aiguille d'une montre
    int nbBlancheCote = nbPieceBlanche/4;
    int* pieceBlanche = (int*) malloc(sizeof (int)*nbPieceBlanche );
    int pos = 0;
    for (i=0; i< nbPieceBlanche; i++){
        if (pos == 0){
            for (k=1;k<=nbBlancheCote;k++){
                pieceBlanche[i] = king-k*9;
            }
            pos = 1;
        }
        if (pos == 1){
            for (k=1;k<nbBlancheCote;k++){
                pieceBlanche[i] = king+k;
            }
            pos = 2;
        }
        if (pos == 2){
            for (k=1;k<nbBlancheCote;k++){
                pieceBlanche[i] = king+k*9;
            }
            pos = 3;
        }
        else{
            for (k=1;k<nbBlancheCote;k++){
                pieceBlanche[i] = king-k;
            }
        }

    }

    //création coordonné piece noire
    /*int* pieceNoire = (int*) malloc(sizeof (int)*nbPieceNoire );
    for (i=0; i<nbPieceNoire; i++)
    {
        pieceNoire[i] = (int*) malloc (2 * sizeof (int) );
    }*/




}
