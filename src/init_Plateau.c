#include "init_Plateau.h"
#include <stdio.h>

int init_Plateau(int N, int *tableauBlancs[], int *tableauNoir[], int *tableauForteresse[]){
    int i,k;
    int king;
    king=N/2+(N/2)*N;
    // création plateau
    int nbCase = N*N;
    int plateau[nbCase];
    for (i=0; i<nbCase; i++)
    {
        plateau[i] = i;
    }

    int nbPieceBlanche = N-1;
    int nbPieceNoire = (N-1)*2;
    //création coordonné piece blanche : on part du haut puis sens aiguille d'une montre
    int nbBlancheCote = nbPieceBlanche/4;
    int pos = 0;
    i = 0;
    while (i < nbPieceBlanche){
        if(pos==0){
            for (k=1;k<=nbBlancheCote;k++){
                tableauBlancs[i] = king-k*N;
                i++;
            }
            pos ++;}
        if(pos==1){
            for (k=1;k<=nbBlancheCote;k++){
                tableauBlancs[i] = king+k;
                i++;
            }
            pos = 2;}
        if(pos==2){
            for (k=1;k<=nbBlancheCote;k++){
                tableauBlancs[i] = king+k*N;
                i++;
            }
            pos = 3;}
        if(pos==3) {
            for (k = 1; k <=nbBlancheCote; k++) {
                tableauBlancs[i] = king - k;
                i++;
            }
        }
        else{
            printf("erreur positionnement des pieces blanches\n");
        }
    }

    //création coordonné piece noire
    int nbNoireCote = nbPieceNoire/4;
    pos = 0;
    i = 0;
    int nbNoireRest,nbNoireLigne,j,l;
    nbNoireLigne = 1;
    l=1;
    while((king+nbBlancheCote+l)%N != N-1){
        nbNoireLigne++;
        l++;
    }
    nbNoireRest = nbNoireCote - nbNoireLigne; // une fois atteind on calcul piece restante à poser
    while (i<nbPieceNoire){
        if(pos==0){ // pareil que pour les pieces blanches
            for(l=1; l<=nbNoireLigne;l++){// tant qu'on n'a pas atteind le bord du haut
                tableauNoir[i] = king-(nbBlancheCote+l)*N;
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){ // on part dans le sens inverse aiguille d'une montre
                tableauNoir[i] = (king-(nbBlancheCote+l-1)*N)-j; // -j donc vers la gauche
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king-(nbBlancheCote+l-1)*N)+j; //+j donc vers la droite
                i++;
            }
            pos  ++;
        }
        if (pos==1){
            for(l=1;l<=nbNoireLigne;l++){// tant qu'on n'a pas atteind le bord de droite
                tableauNoir[i] = king+nbBlancheCote+l;
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king+nbBlancheCote+l-1)-(N*j); // -j donc vers la gauche
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king+nbBlancheCote+l-1)+(N*j); //+j donc vers la droite
                i++;
            }
            pos ++;
        }
        if (pos==2){
            for(l=1; l<=nbNoireLigne;l++){// tant qu'on n'a pas atteind le bord du bas
                tableauNoir[i] = king+(nbBlancheCote+l)*N;
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king+(nbBlancheCote+l-1)*N)+j; // +j donc vers la droite
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king+(nbBlancheCote+l-1)*N)-j; //-j donc vers la gauche
                i++;
            }
            pos ++;
        }
        if (pos==3){
            for(l=1; l<=nbNoireLigne;l++){// tant qu'on n'a pas atteind le bord de gauche
                tableauNoir[i] = king-nbBlancheCote-l;
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king-nbBlancheCote-l-1)+(N*j); // -j donc vers la gauche
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king-nbBlancheCote-l-1)-(N*j); //+j donc vers la droite
                i++;
            }
        }
        else{
            printf("erreur positionnement des pieces noires\n");
        }
    }
    //initialisation des forteresse
    int forteresse[4];
    /*if(mode = avance){
        ...
    }
    else{
        forteresse[0] = 0;
        forteresse[1] = N-1;
        forteresse[2] = (N-1)+(N-1)*N;
        forteresse[3] = (N-1)*N;
    }*/
    tableauForteresse[0] = 0;
    tableauForteresse[1] = N-1;
    tableauForteresse[2] = (N-1)+(N-1)*N;
    tableauForteresse[3] = (N-1)*N;

    for (i=0;i<nbPieceBlanche;i++){
        //printf("%d\t",pieceBlanche[i]);
    }
    for (i=0;i<nbPieceNoire;i++){
        //printf("%d\t",pieceNoire[i]);
    }
    for (i=0;i<4;i++){
        //printf("%d\t",forteresse[i]);
    }
    printf("\n");
    return king;
}
