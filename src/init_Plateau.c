//
// Created by Utilisateur on 09/11/2022.
//

#include "init_Plateau.h"
#include <stdlib.h>
#include <stdio.h>

int init_Plateau(){
    int N,i;
    printf("Dimension:");
    scanf("%d",&N);
    // création plateau
    int** plateau = (int**) malloc(N * sizeof (int*) );
    for (i=0; i<N; i++)
    {
        plateau[i] = (int*) malloc (N * sizeof (int) );
    }
    int nbPieceBlanche = N-1;
    int nbPieceNoire = (N-1)*2;
    //création coordonné piece blanche
    int** pieceBlanche = (int**) malloc(nbPieceBlanche * sizeof (int*) );
    for (i=0; i<N; i++)
    {
        pieceBlanche[i] = (int*) malloc (2 * sizeof (int) );
    }
    //création coordonné piece blanche
    int** pieceNoire = (int**) malloc(nbPieceNoire * sizeof (int*) );
    for (i=0; i<N; i++)
    {
        pieceNoire[i] = (int*) malloc (2 * sizeof (int) );
    }
    // Libération mémoire : tableau dynamique à 2 dimensions
    /*for (i=0; i<N; i++)
    {
        free (plateau[i]);
    }
    free(plateau);
    for (i=0; i<nbPieceBlanche; i++)
    {
        free (pieceBlanche[i]);
    }
    free(pieceBlanche);
    for (i=0; i<nbPieceNoire; i++)
    {
        free (pieceNoire[i]);
    }
    free(pieceNoire);*/
}
