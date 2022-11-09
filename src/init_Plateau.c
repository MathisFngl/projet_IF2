//
// Created by Utilisateur on 09/11/2022.
//

#include "init_Plateau.h"
#include <stdlib.h>
#include <stdio.h>

int* init_Plateau(){
    int N,i,k;
    printf("Dimension:");
    scanf("%d",&N);
    int king;
    king=N/2+(N/2)*N;
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
    i = 0;
    while (i < nbPieceBlanche){
        switch (pos){ // position haut droite bas gauche
            case 0:
                for (k=1;k<=nbBlancheCote;k++){
                    pieceBlanche[i] = king-k*N;
                    i++;
                }
                pos = 1;
            case 1:
                for (k=1;k<nbBlancheCote;k++){
                    pieceBlanche[i] = king+k;
                    i++;
                }
                pos = 2;
            case 2:
                for (k=1;k<nbBlancheCote;k++){
                pieceBlanche[i] = king+k*N;
                i++;
                }
                pos = 3;
            case 3:
                for (k=1;k<nbBlancheCote;k++){
                pieceBlanche[i] = king-k;
                i++;
                }
            default:
                printf("erreur positionnement des pieces blanches");
                break;
        }
    }

    //création coordonné piece noire
    int nbNoireCote = nbPieceNoire/4;
    int* pieceNoire = (int*) malloc(sizeof (int)*nbPieceNoire );
    pos = 0;
    i = 0;
    int nbNoirePose=0;
    int nbNoireRest,pos2,j,l;
    while (i<nbPieceNoire){
        switch (pos){ // pareil que pour les pieces blanches
            case 0:
                for (k=1;k<=nbNoireCote;k++){
                    l=1;
                    while((king-(nbBlancheCote+l)*N)%N !=0){// tant qu'on n'a pas atteind le bord du haut
                        pieceNoire[i] = king-(nbBlancheCote+l)*N;
                        nbNoirePose ++;
                        l++;
                        i++;
                    }
                    nbNoireRest = nbNoireCote - nbNoirePose; // une fois atteind on calcul piece restante à poser
                    pos2=0;
                    switch (pos2) {
                        case 0: // on part dans le sens inverse aiguille d'une montre
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king-(nbBlancheCote+k)*N)-j; // -j donc vers la gauche
                                i++;
                            }
                            pos2 = 1;
                        case 1:
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king-(nbBlancheCote+k)*N)+j; //+j donc vers la droite
                                i++;
                            }
                        default:
                            printf("erreur positionnement des pieces noires");
                            break;
                    }
                }
                pos = 1;
            case 1:
                for (k=1;k<=nbNoireCote;k++){
                    l=1;
                    while((king+nbBlancheCote+l)%N !=N-1){// tant qu'on n'a pas atteind le bord de droite
                        pieceNoire[i] = king+nbBlancheCote+l;
                        l++;
                        i++;
                    }
                    pos2=0;
                    switch (pos2) {
                        case 0: // on part dans le sens inverse aiguille d'une montre
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king+nbBlancheCote+l)-N*j; // -j donc vers la gauche
                                i++;
                            }
                            pos2 = 1;
                        case 1:
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king+nbBlancheCote+l)+N*j; //+j donc vers la droite
                                i++;
                            }
                        default:
                            printf("erreur positionnement des pieces noires");
                            break;
                    }
                }
                pos = 2;
            case 2:
                for (k=1;k<=nbNoireCote;k++){
                    l=1;
                    while((king+(nbBlancheCote+l)*N)%N !=N-1){// tant qu'on n'a pas atteind le bord du bas
                        pieceNoire[i] = king+(nbBlancheCote+l)*N;
                        l++;
                        i++;
                    }
                    pos2=0;
                    switch (pos2) {
                        case 0: // on part dans le sens inverse aiguille d'une montre
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king+(nbBlancheCote+k)*N)+j; // +j donc vers la droite
                                i++;
                            }
                            pos2 = 1;
                        case 1:
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king+(nbBlancheCote+k)*N)-j; //-j donc vers la gauche
                                i++;
                            }
                        default:
                            printf("erreur positionnement des pieces noires");
                            break;
                    }
                }
                pos = 3;
            case 3:
                for (k=1;k<=nbNoireCote;k++){
                    l=1;
                    while((king-nbBlancheCote-l)%N !=0){// tant qu'on n'a pas atteind le bord de gauche
                        pieceNoire[i] = king-nbBlancheCote-l;
                        l--;
                        i++;
                    }
                    pos2=0;
                    switch (pos2) {
                        case 0: // on part dans le sens inverse aiguille d'une montre
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king-nbBlancheCote-l)+N*j; // -j donc vers la gauche
                                i++;
                            }
                            pos2 = 1;
                        case 1:
                            for (j=1; j<=nbNoireRest/2;j++){
                                pieceNoire[i] = (king-nbBlancheCote-l)-N*j; //+j donc vers la droite
                                i++;
                            }
                        default:
                            printf("erreur positionnement des pieces noires");
                            break;
                    }
                }
            default:
                printf("erreur positionnement des pieces noires");
                break;
        }
    }
    //initialisation des forteresse
    int* forteresse = (int*) malloc(sizeof (int)*4 );
    /*if(mode = avance){
        ...
    }
    else{
        forteresse[0] = 0;
        forteresse[1] = N-1;
        forteresse[2] = (N-1)+(N-1)*N;
        forteresse[3] = (N-1)*N;
    }*/
    forteresse[0] = 0;
    forteresse[1] = N-1;
    forteresse[2] = (N-1)+(N-1)*N;
    forteresse[3] = (N-1)*N;
}
