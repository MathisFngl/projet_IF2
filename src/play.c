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

bool mouvement(int IndexArrive, int IndexDepart,int taille,int couleur,int *pieceBlanche,int *pieceNoire,int nbPieceBlanche, int nbPieceNoire, int *forteresse){
    bool mov = false;
    int i,k;
    if(IndexDepart == IndexArrive){
        printf("bouger une piece\n");
    }
    for(i=0;i<taille;i++){
        if(IndexDepart-taille*i == IndexArrive || IndexDepart+taille*i == IndexArrive || IndexDepart+i == IndexArrive
           || IndexDepart-i == IndexArrive){
            mov = true;
        }
        else{
            mov = false;
        }
    }
    if(IndexArrive == taille/2+(taille/2)*taille){
        mov = false;
    }
    for(i=0;i<4;i++){
        if(IndexArrive == forteresse[i]){
            mov == false;
        }
    }
    if (couleur == 0){
        for(i=0;i<taille;i++){
            for(k=0;k<nbPieceNoire;k++){
                if(IndexDepart-taille*i == pieceNoire[k] || IndexDepart+taille*i == pieceNoire[k] || IndexDepart+i == pieceNoire[k]
                   || IndexDepart-i == pieceNoire[k]){ // verif pas de pion couleur opposé sur le passage
                    mov = false;
                }
            }
        }
    }
    if (couleur == 1){
        for(i=0;i<taille;i++){
            for(k=0;k<nbPieceBlanche;k++){
                if(IndexDepart-taille*i == pieceBlanche[k] || IndexDepart+taille*i == pieceBlanche[k] ||
                IndexDepart+i == pieceBlanche[k] || IndexDepart-i == pieceBlanche[k]){ // verif pas de pion couleur opposé sur le passage
                    mov = false;
                }
            }
        }
    }
    return mov;
}
int pionMange(int IndexArrive, int couleur, int* pieceBlanche, int* pieceNoire, int nbPieceBlanche, int nbPieceNoire,int taille,int king){
    int i,k;
    if (couleur == 0){
        for(i=0;i<nbPieceNoire;i++){
            if(IndexArrive-taille == pieceNoire[i]){ // pion en haut
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2*taille==pieceBlanche[k] || IndexArrive-2*taille == king){
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive+taille == pieceNoire[i]){ // pion en bas
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2*taille==pieceBlanche[k] || IndexArrive+2*taille == king){
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive+1 == pieceNoire[i] && IndexArrive%taille <= taille-3){ // pion a droite + verif assez de case sur le cote
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2==pieceBlanche[k] || IndexArrive+2 == king){
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive-1 == pieceNoire[i] && IndexArrive%taille >= 2){ // pion a gauche + verif assez de cases sur le cote
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2==pieceBlanche[k] || IndexArrive-2 == king){
                        pieceNoire[i] = -1;
                    }
                }
            }
        }
    }
    if (couleur == 1){
        if(IndexArrive-taille == king){ // roi mangé par le haut
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive-2*taille == pieceNoire[k]){
                    king = -1;
                }
            }
        }
        if(IndexArrive+taille == king){ // roi mangé par le bas
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive+2*taille == pieceNoire[k]){
                    king = -1;
                }
            }
        }
        if(IndexArrive-1 == king){ // roi mangé par la gauche
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive-2 == pieceNoire[k]){
                    king = -1;
                }
            }
        }
        if(IndexArrive+1 == king){ // roi mangé par la droite
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive+2 == pieceNoire[k]){
                    king = -1;
                }
            }
        }
        for(i=0;i<nbPieceBlanche;i++){ // parcours tout le tab blanc
            if(IndexArrive-taille == pieceBlanche[i]){ // pion en haut
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2*taille==pieceNoire[k]){
                        pieceBlanche[i] = -1;
                    }
                }
            }
            if(IndexArrive+taille == pieceBlanche[i]){ // pion en bas
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2*taille==pieceNoire[k]){
                        pieceBlanche[i] = -1;
                    }
                }
            }
            if(IndexArrive+1 == pieceBlanche[i] && IndexArrive%taille <= taille-3){ // pion a droite + verif assez de case sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2==pieceNoire[k]){
                        pieceBlanche[i] = -1;
                    }
                }
            }
            if(IndexArrive-1 == pieceBlanche[i] && IndexArrive%taille >= 2){ // pion a gauche + verif assez de cases sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2==pieceNoire[k]){
                        pieceBlanche[i] = -1;
                    }
                }
            }
        }
    }
    return king;
}

int play(int IndexArrive,int IndexDepart){
    int i,indexBlanc,indexNoir; //si couleur=0 alors c'est au blanc de jouer si =1 c'est au noir
    bool same,win=false,mov;
    int nbPieceBlanche = taille -1;
    int nbPieceNoire =  (taille-1)*2;
    if(IndexDepart == king){
        for(i=0;i<4;i++){
            if(forteresse[i]==king){
                win = true;
            }
        }
    }

    do{ // test si'il n'y a pas déja un pion
        same = sameCase(king, *pieceBlanche, *pieceNoire, *forteresse,IndexArrive);
    }while(same !=false);
    do{
        mov = mouvement(IndexArrive,IndexDepart,taille, couleur,*pieceBlanche, *pieceNoire, nbPieceBlanche, nbPieceNoire, *forteresse );
    } while (mov != true);

    king = pionMange(IndexArrive, couleur, *pieceBlanche, *pieceNoire, nbPieceBlanche,nbPieceNoire,taille,king);
    if (king == -1){
        win = false;
    }
}
// couleur, taille, king , tab blanc, tab noir, forteresse, indexarrive, indexdepart
*/