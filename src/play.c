/*
#include "play.h"
#include <stdbool.h>
#include <stdio.h>
#include "window.h"

bool sameCase(int king, int *pieceBlanche, int *pieceNoire, int *forteresse,int nbPieceBlanche, int nbPieceNoire,int IndexArrive){
    bool same=false;
    int i;
    for(i=0;i<nbPieceNoire;i++) {
        if (pieceNoire[i] == IndexArrive) {
            same = true;
        }
    }
    for(i=0;i<nbPieceBlanche;i++){
        if(pieceBlanche[i]==IndexArrive){
            same = true;
        }
    }
    for (i=0;i<4;i++){
        if(forteresse[i]==IndexArrive){
            same = true;
        }
    }
    if(IndexArrive == king){
        same = true;
    }
    if(same == true){
        printf("La case est deja prise\n");
    }
    /*
    for (i=0;i<2;i++){
        if (piege[i]==quadrant){
            pieceBlanche[piece]=Null}
    }

    return same;
}

bool mouvement(int IndexArrive, int IndexDepart,int taille){
    bool mov = false;
    int i;
    if(IndexDepart == IndexArrive){
        printf("bouger une piece\n");
    }
    for(i=0;i<taille;i++){
        if(IndexDepart-9*i == IndexArrive || IndexDepart+9*i == IndexArrive || IndexDepart+i == IndexArrive
           || IndexDepart-i == IndexArrive){
            mov = true;
        }
        else{
            mov = false;
        }
    }
    return mov;
}
int pionMange(int IndexArrive, int couleur, int* pieceBlanche, int* pieceNoire, int nbPieceBlanche, int nbPieceNoire,int taille){
    int i,k;
    if (couleur == 0){
        for(i=0;i<nbPieceNoire;i++){
            if(IndexArrive-taille == pieceNoire[i]){ // pion en haut
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2*taille==pieceBlanche[k]){
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive+taille == pieceNoire[i]){ // pion en bas
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2*taille==pieceBlanche[k]){
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive+1 == pieceNoire[i]){ // pion a droite
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2==pieceBlanche[k]){
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive-1 == pieceNoire[i]){ // pion a droite
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2==pieceBlanche[k]){
                        pieceNoire[i] = -1;
                    }
                }
            }
        }
    }
}

int play(int IndexArrive,int IndexDepart){
    int couleur=0,i,indexBlanc,indexNoir; //si couleur=0 alors c'est au blanc de jouer si =1 c'est au noir
    bool same,win=false,mov;
    int nbPieceBlanche = taille -1;
    int nbPieceNoire =  (taille-1)*2;

        if (couleur == 0){
            do{
                same = sameCase(king, *pieceBlanche, *pieceNoire, *forteresse,IndexArrive);
            }while(same !=false);
            do{
                mov = mouvement(IndexArrive,IndexDepart,taille);
            } while (mov != true);
            if(IndexDepart == king){
                for(i=0;i<4;i++){
                    if(forteresse[i]==king){
                        win = true;
                    }
                }
            }
            for(i=0;i<nbPieceBlanche;i++){
                if(pieceBlanche[i]==IndexDepart){
                    pieceBlanche[i] = IndexArrive;
                }
            }
            pionMange(IndexArrive, couleur, *pieceBlanche, *pieceNoire, nbPieceBlanche,nbPieceNoire,taille);
            couleur = 1;
        }
}*/