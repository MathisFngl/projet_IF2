#include "init_Plateau.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int modeCompliqueForteresse(int N, int *tableauBlancs, int *tableauNoir, int *TableauForteresse,int nbPieceBlanche, int nbPieceNoire){
    int i,k;

    srand(time(0));
    TableauForteresse[0] = rand()%81;
    TableauForteresse[1] = rand()%81;
    TableauForteresse[2] = rand()%81;
    TableauForteresse[3] = rand()%81;

    for(i=0;i<4;i++){
        for(k=0;k<nbPieceNoire;k++){
            if(TableauForteresse[i] == tableauNoir[k])
                modeCompliqueForteresse(N,tableauBlancs, tableauNoir,TableauForteresse,nbPieceBlanche,nbPieceNoire);

        }
        for(k=0;k<nbPieceBlanche;k++){
            if(TableauForteresse[i]==tableauBlancs[k]){
                modeCompliqueForteresse(N,tableauBlancs, tableauNoir,TableauForteresse,nbPieceBlanche,nbPieceNoire);
            }
        }
        for(k=0;k<4;k++){
            if(TableauForteresse[i]==TableauForteresse[k]){
                modeCompliqueForteresse(N,tableauBlancs, tableauNoir,TableauForteresse,nbPieceBlanche,nbPieceNoire);
            }
        }
    }
}
//fonction recursive pour les replacer aléatoirement jusqu'à ce que ça soit bon
int modeCompliquePiege(int N, int *tableauBlancs, int *tableauNoir, int *tableauPiege,int *TableauForteresse,int nbPieceBlanche, int nbPieceNoire){
    int i,k;

    srand(time(0));
    tableauPiege[0]=rand()%81;
    tableauPiege[1]=rand()%81;
    for(i=0;i<2;i++){
        for(k=0;k<nbPieceNoire;k++){
            if(tableauPiege[i] == tableauNoir[k])
                modeCompliquePiege(N,tableauBlancs,tableauNoir,tableauPiege,TableauForteresse,nbPieceBlanche,nbPieceNoire);

        }
        for(k=0;k<nbPieceBlanche;k++){
            if(tableauPiege[i]==tableauBlancs[k]){
                modeCompliquePiege(N,tableauBlancs,tableauNoir,tableauPiege,TableauForteresse,nbPieceBlanche,nbPieceNoire);
            }
        }
        for(k=0;k<2;k++){
            if(tableauPiege[i]==tableauPiege[k]){
                modeCompliquePiege(N,tableauBlancs,tableauNoir,tableauPiege,TableauForteresse, nbPieceBlanche, nbPieceNoire);
            }
        }
        for(k=0;k<4;k++){
            if(tableauPiege[i]==TableauForteresse[k]){
                modeCompliquePiege(N,tableauBlancs,tableauNoir,tableauPiege,TableauForteresse,nbPieceBlanche,nbPieceNoire);
            }
        }
    }
}

int init_Plateau(int N, int *tableauBlancs, int *tableauNoir, int *TableauForteresse, int *tableauPiege,int mode){
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

    int nbPieceBlanche = ((N-1)/4)*4;
    int nbPieceNoire = ((N-1)/2)*4;
    int nbNoireCote = nbPieceNoire/4;
    int nbBlancheCote = nbPieceBlanche/4;
    int nbNoireRest,nbNoireLigne,l;
    nbNoireLigne = 1;
    l=1;
    while((king+nbBlancheCote+l)%N != N-1){
        nbNoireLigne++;
        l++;
    }
    nbNoireRest = nbNoireCote - nbNoireLigne;
    printf("nb noire reste = %d\n",nbNoireRest);
    if(nbNoireRest%2 != 0){
        nbPieceNoire = nbPieceNoire -4;
    }

    printf("nb piece blanche = %d\n",nbPieceBlanche);
    printf("nb piece noire = %d\n",nbPieceNoire);

    //création coordonné piece blanche : on part du haut puis sens aiguille d'une montre

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

    pos = 0;
    i = 0;
    int j;
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
                tableauNoir[i] = (king-nbBlancheCote-l+1)+(N*j); // -j donc vers la gauche
                i++;
            }
            for (j=1; j<=nbNoireRest/2;j++){
                tableauNoir[i] = (king-nbBlancheCote-l+1)-(N*j); //+j donc vers la droite
                i++;
            }
        }
        else{
            printf("erreur positionnement des pieces noires\n");
        }
    }
    //initialisation des forteresse
    if(mode == 0){
        TableauForteresse[0] = 0;
        TableauForteresse[1] = N-1;
        TableauForteresse[2] = (N-1)+(N-1)*N;
        TableauForteresse[3] = (N-1)*N;
    }
    if(mode==1){
        modeCompliqueForteresse(N,tableauBlancs, tableauNoir,TableauForteresse,nbPieceBlanche,nbPieceNoire);
        modeCompliquePiege(N,tableauBlancs,tableauNoir,tableauPiege,TableauForteresse,nbPieceBlanche,nbPieceNoire);
    }

    return king;
}
