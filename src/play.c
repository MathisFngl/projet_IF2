
#include "play.h"
#include <stdbool.h>
#include <stdio.h>
#include "window.h"
#include "parsing.h"

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
    }*/

    return same;
}

bool mouvement(int IndexArrive, int IndexDepart,int taille,int *pieceBlanche,int *pieceNoire,int nbPieceBlanche, int nbPieceNoire, int *forteresse,int king){
    bool mov = false;
    int i,k,orientation;
    if(IndexDepart == IndexArrive){
        printf("bouger une piece\n");
    }
    for(i=0;i<taille;i++) {
        if (IndexDepart - taille * i == IndexArrive) {
            printf("mov ok\n");
            mov = true;
            orientation = 1;
        }
        if (IndexDepart + taille * i == IndexArrive) {
            printf("mov ok\n");
            mov = true;
            orientation = 3;
        }
        if ((IndexDepart + i == IndexArrive && i <taille-1) || (IndexDepart +i == IndexArrive && IndexDepart%taille == 0)) {
            printf("mov ok\n");
            mov = true;
            orientation = 2;
        }
        if ((IndexDepart - i == IndexArrive && i<taille-1) || (IndexDepart -i == IndexArrive && IndexDepart%taille == taille-1)) {
            printf("i = %d , arrive - i = %d\n",i,IndexDepart-i);
            printf("mov ok\n");
            mov = true;
            orientation = 4;
        }
    }

    if(IndexArrive == taille/2+(taille/2)*taille){ // position case du milieu
        mov = false;
    }
    if(orientation == 1){
        i=1;
        while(IndexDepart-taille*i<IndexArrive){
            for(k=0;k<nbPieceBlanche;k++){
                if(IndexDepart-taille*i == pieceBlanche[k]){
                    mov = false;
                }
            }
            for(k=0;k<nbPieceNoire;k++){
                if(IndexDepart-taille*i == pieceNoire[k]){
                    mov = false;
                }
            }
            if(IndexDepart-taille*i==king && IndexDepart != king){
                mov = false;
            }
            i++;
        }
    }
    if(orientation == 2){
        i=1;
        while(IndexDepart+i<IndexArrive){
            for(k=0;k<nbPieceBlanche;k++){
                if(IndexDepart+i == pieceBlanche[k]){
                    mov = false;
                }
            }
            for(k=0;k<nbPieceNoire;k++){
                if(IndexDepart+i == pieceNoire[k]){
                    mov = false;
                }
            }
            if(IndexDepart+i==king && IndexDepart != king){
                mov = false;
            }
            i++;
        }
    }
    if(orientation == 3){
        i=1;
        while(IndexDepart+taille*i<IndexArrive){
            for(k=0;k<nbPieceBlanche;k++){
                if(IndexDepart+taille*i == pieceBlanche[k]){
                    mov = false;
                }
            }
            for(k=0;k<nbPieceNoire;k++){
                if(IndexDepart+taille*i == pieceNoire[k]){
                    mov = false;
                }
            }
            if(IndexDepart+taille*i==king && IndexDepart != king){
                mov = false;
            }
            i++;
        }
    }
    if(orientation == 4){
        i=1;
        while(IndexDepart-i<IndexArrive){
            for(k=0;k<nbPieceBlanche;k++){
                if(IndexDepart-i == pieceBlanche[k]){
                    mov = false;
                }
            }
            for(k=0;k<nbPieceNoire;k++){
                if(IndexDepart-i == pieceNoire[k]){
                    mov = false;
                }
            }
            if(IndexDepart-i==king && IndexDepart != king){
                mov = false;
            }
            i++;
        }
    }
    printf("orientation = %d\n",orientation);
    if (orientation > 4 ){
        printf("orientation = %d\n",orientation);
        mov = false;
    }
    return mov;
}
int pionMange(int IndexArrive,int IndexDepart, int c, int* pieceBlanche, int* pieceNoire, int nbPieceBlanche, int nbPieceNoire,int taille,int king){
    int i,k;
    if (c == 0){
        for(i=0;i<nbPieceNoire;i++){
            if(IndexArrive-taille == pieceNoire[i]){ // pion en haut
                printf("pion noir en haut:%d\n",pieceNoire[i]);
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2*taille==pieceBlanche[k] || IndexArrive-2*taille == king){
                        printf("pion noir mange en haut:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                        parsing_write_stats(3);
                    }
                }
            }
            if(IndexArrive+taille == pieceNoire[i]){ // pion en bas
                printf("pion noir en bas:%d\n",pieceNoire[i]);
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2*taille==pieceBlanche[k] || IndexArrive+2*taille == king){
                        printf("pion noir mange en bas:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                        parsing_write_stats(3);
                    }
                }
            }
            if(IndexArrive+1 == pieceNoire[i] && (IndexArrive+2)%taille!=1 && (IndexArrive+2)%taille!=0 ){ // pion a droite + verif assez de case sur le cote
                printf("pion noir a droite:%d\n",pieceNoire[i]);
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2==pieceBlanche[k] || IndexArrive+2 == king){
                        printf("pion noir mange a droite:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                        parsing_write_stats(3);
                    }
                }
            }
            if(IndexArrive-1 == pieceNoire[i] && (IndexArrive-2)%taille!=taille-1 && (IndexArrive-2)%taille!=taille-2 ){ // pion a gauche + verif assez de cases sur le cote
                printf("pion noir a gauche:%d\n",pieceNoire[i]);
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2==pieceBlanche[k] || IndexArrive-2 == king){
                        printf("pion noir mange à gauche:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                        parsing_write_stats(3);
                    }
                }
            }
        }
    }
    if (c == 1){
        if(IndexArrive-taille == king){ // roi mangé par le haut
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive-2*taille == pieceNoire[k]){
                    printf("roi blanc mange en haut:%d\n",king);
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        if(IndexArrive+taille == king){ // roi mangé par le bas
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive+2*taille == pieceNoire[k]){
                    printf("roi blanc mange en bas:%d\n",king);
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        if(IndexArrive-1 == king){ // roi mangé par la gauche
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive-2 == pieceNoire[k]){
                    printf("roi blanc mange a gauche:%d\n",king);
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        if(IndexArrive+1 == king){ // roi mangé par la droite
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive+2 == pieceNoire[k]){
                    printf("roi blanc mange a droite:%d\n",king);
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        for(i=0;i<nbPieceBlanche;i++){ // parcours tout le tab blanc
            if(IndexArrive-taille == pieceBlanche[i]){ // pion en haut
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2*taille==pieceNoire[k]){
                        printf("pion blanc mange en haut:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
            if(IndexArrive+taille == pieceBlanche[i]){ // pion en bas
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2*taille==pieceNoire[k]){
                        printf("pion blanc mange en bas:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
            if(IndexArrive+1 == pieceBlanche[i] && (IndexArrive+2)%taille!=1 && (IndexArrive+2)%taille!=0){ // pion a droite + verif assez de case sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2==pieceNoire[k]){
                        printf("pion blanc mange à droite:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
            if(IndexArrive-1 == pieceBlanche[i] && (IndexArrive+2)%taille!=1 && (IndexArrive+2)%taille!=0){ // pion a gauche + verif assez de cases sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2==pieceNoire[k]){
                        printf("pion blanc mange gauche:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
        }
    }
    movPieces(IndexDepart,IndexArrive,pieceNoire,pieceBlanche,king,c,nbPieceBlanche,nbPieceNoire);
}

int movPieces(int IndexDepart,int IndexArrive, int *pieceNoire, int *pieceBlanche, int king,int c, int nbPieceBlanche, int nbPieceNoire){
    int index,i;
    if (c == 0){
        printf("king depart = %d\n",king);
        if(IndexDepart == king){
            king = IndexArrive;
            printf("king = %d\n",king);
            return king;
        }
        for (i=0;i<nbPieceBlanche;i++){
            if(pieceBlanche[i]==IndexDepart){
                index = i;
            }
        }
        pieceBlanche[index]=IndexArrive;
    }

    if (c == 1){
        for (i=0;i<nbPieceNoire;i++){
            if(pieceNoire[i]==IndexDepart){
                index = i;
            }
        }
        pieceNoire[index]=IndexArrive;
    }
    return king;

}

int play(int IndexArrive,int IndexDepart,int taille,int *pieceNoire, int *pieceBlanche,int *forteresse, int king, int* couleur){
    //si couleur=0 alors c'est au blanc de jouer si =1 c'est au noir
    int c = *couleur;
    printf("depart = %d\n",IndexDepart);
    printf("arrive = %d\n",IndexArrive);
    printf("couleur = %d\n",c);
    int i,piece=1;
    bool same,win=false,mov;
    int nbPieceBlanche = taille -1;
    int nbPieceNoire =  (taille-1)*2;
    if(c==0){
        for(i=0;i<nbPieceBlanche;i++){
            if(pieceBlanche[i]==IndexDepart){
                piece = 0; // verif que l'on bouge bien une piece
            }
        }
        if(king==IndexDepart){
            piece = 0;
        }
    }
    if(c==1){
        for(i=0;i<nbPieceNoire;i++){
            if(pieceNoire[i]==IndexDepart){
                piece = 0; // verif que on bouge bien une piece
            }
        }
    }
    // test si'il n'y a pas déja un pion
    if(piece==0){
        same = sameCase(king, pieceBlanche, pieceNoire, forteresse,nbPieceBlanche,nbPieceNoire,IndexArrive);
    }
    else{
        return -2;
    }
    //test movement
    if(same==false){
        mov = mouvement(IndexArrive,IndexDepart,taille,pieceBlanche, pieceNoire, nbPieceBlanche, nbPieceNoire, forteresse, king);
    }else{
        return -2;
    }
    if(same ==false && mov == true && piece==0){
        king = pionMange(IndexArrive,IndexDepart, c, pieceBlanche, pieceNoire, nbPieceBlanche,nbPieceNoire,taille,king);
        return king;
    }
    else{
        return -2;
    }

}

