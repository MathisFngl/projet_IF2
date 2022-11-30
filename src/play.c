
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
    }*/

    return same;
}

bool mouvement(int IndexArrive, int IndexDepart,int taille,int couleur,int *pieceBlanche,int *pieceNoire,int nbPieceBlanche, int nbPieceNoire, int *forteresse){
    bool mov = false;
    int i,k;
    if(IndexDepart == IndexArrive){
        printf("bouger une piece\n");
    }
    for(i=0;i<taille-1;i++){// au max 8 pour une taille de 9 par exemple
        if(IndexDepart-taille*i == IndexArrive || IndexDepart+taille*i == IndexArrive || IndexDepart+i == IndexArrive
           || IndexDepart-i == IndexArrive){
            printf("mov ok\n");
            mov = true;
        }
        else{
            printf("mov pas ok\n");
        }
    }
    if(IndexArrive == taille/2+(taille/2)*taille){ // position case du milieu
        mov = false;
        printf("mov  pas ok car pos milieu\n");
    }
    /*for(i=0;i<taille-1;i++){
        for(k=0;k<nbPieceBlanche;k++){ // plus de piece noire que blanche donc on verifie pour toute les piece nois
            if(IndexDepart-taille*i == pieceBlanche[k] || IndexDepart+taille*i == pieceBlanche[k] ||
               IndexDepart+i == pieceBlanche[k] || IndexDepart-i == pieceBlanche[k]){ // verif pas de pion sur le passage
                printf("mov pas ok car pion sur le passage 1 \n");
                mov = false;
            }
        }
    }
    for(i=0;i<taille-1;i++){
        for(k=0;k<nbPieceNoire;k++){
            if(IndexDepart-taille*i == pieceNoire[k] || IndexDepart+taille*i == pieceNoire[k] || IndexDepart+i == pieceNoire[k]
               || IndexDepart-i == pieceNoire[k]){
                printf("mov pas ok car pion sur le passage \n");
                mov = false;
            }
        }
    }*/
    return mov;
}
int pionMange(int IndexArrive,int IndexDepart, int couleur, int* pieceBlanche, int* pieceNoire, int nbPieceBlanche, int nbPieceNoire,int taille,int king){
    int i,k,index;
    if (couleur == 0){
        for (i=0;i<nbPieceBlanche;i++){
            if(pieceBlanche[i]==IndexDepart){
                index = i;
            }
        }
        for(i=0;i<nbPieceNoire;i++){
            if(IndexArrive-taille == pieceNoire[i]){ // pion en haut
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2*taille==pieceBlanche[k] || IndexArrive-2*taille == king){
                        printf("pion noir mange en haut:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive+taille == pieceNoire[i]){ // pion en bas
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2*taille==pieceBlanche[k] || IndexArrive+2*taille == king){
                        printf("pion noir mange en bas:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive+1 == pieceNoire[i] && IndexArrive%taille <= taille-3){ // pion a droite + verif assez de case sur le cote
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2==pieceBlanche[k] || IndexArrive+2 == king)
                        printf("pion noir mange a droite:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                    }
                }
            }
            if(IndexArrive-1 == pieceNoire[i] && IndexArrive%taille >= 2){ // pion a gauche + verif assez de cases sur le cote
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2==pieceBlanche[k] || IndexArrive-2 == king){
                        printf("pion noir mange à gauche:%d\n",pieceNoire[i]);
                        pieceNoire[i] = -1;
                    }
                }
            }
        }
    if (couleur == 1){
        if(IndexArrive-taille == king){ // roi mangé par le haut
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive-2*taille == pieceNoire[k]){
                    printf("roi blanc mange en haut:%d\n",king);
                    king = -1;
                }
            }
        }
        if(IndexArrive+taille == king){ // roi mangé par le bas
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive+2*taille == pieceNoire[k]){
                    printf("roi blanc mange en bas:%d\n",king);
                    king = -1;
                }
            }
        }
        if(IndexArrive-1 == king){ // roi mangé par la gauche
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive-2 == pieceNoire[k]){
                    printf("roi blanc mange a gauche:%d\n",king);
                    king = -1;
                }
            }
        }
        if(IndexArrive+1 == king){ // roi mangé par la droite
            for(k=0;k<nbPieceNoire;k++){
                if(IndexArrive+2 == pieceNoire[k]){
                    printf("roi blanc mange a droite:%d\n",king);
                    king = -1;
                }
            }
        }
        for(i=0;i<nbPieceBlanche;i++){ // parcours tout le tab blanc
            if(IndexArrive-taille == pieceBlanche[i]){ // pion en haut
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2*taille==pieceNoire[k]){
                        printf("pion blanc mange en haut:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                    }
                }
            }
            if(IndexArrive+taille == pieceBlanche[i]){ // pion en bas
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2*taille==pieceNoire[k]){
                        printf("pion blanc mange en bas:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                    }
                }
            }
            if(IndexArrive+1 == pieceBlanche[i] && IndexArrive%taille <= taille-3){ // pion a droite + verif assez de case sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive+2==pieceNoire[k]){
                        printf("pion blanc mange à droite:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                    }
                }
            }
            if(IndexArrive-1 == pieceBlanche[i] && IndexArrive%taille >= 2){ // pion a gauche + verif assez de cases sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2==pieceNoire[k]){
                        printf("pion blanc mange gauche:%d\n",pieceBlanche[i]);
                        pieceBlanche[i] = -1;
                    }
                }
            }
        }
    }
    movPieces(IndexDepart,IndexArrive,pieceNoire,pieceBlanche,king,couleur,nbPieceBlanche,nbPieceNoire);
}

int movPieces(int IndexDepart,int IndexArrive, int *pieceNoire, int *pieceBlanche, int king,int couleur, int nbPieceBlanche, int nbPieceNoire){
    int index,i;
    for(i=0;i<nbPieceBlanche;i++){
        printf("%d \t",pieceBlanche[i]);
    }
    printf("\n");
    if (couleur == 0){
        if(IndexDepart == king){
            king = IndexArrive;
            return king;
        }
        for (i=0;i<nbPieceBlanche;i++){
            if(pieceBlanche[i]==IndexDepart){
                index = i;
            }
        }
        pieceBlanche[index]=IndexArrive;
        for(i=0;i<nbPieceBlanche;i++){
            printf("%d \t",pieceBlanche[i]);
        }
    }

    if (couleur == 1){
        for (i=0;i<nbPieceNoire;i++){
            if(pieceNoire[i]==IndexDepart){
                index = i;
            }
        }
        pieceNoire[index]=IndexArrive;
    }

}

int play(int IndexArrive,int IndexDepart,int taille,int *pieceNoire, int *pieceBlanche,int *forteresse, int king, int couleur){
    //si couleur=0 alors c'est au blanc de jouer si =1 c'est au noir
    printf("depart = %d\n",IndexDepart);
    printf("arrive = %d\n",IndexArrive);
    bool same,win=false,mov;
    int nbPieceBlanche = taille -1;
    int nbPieceNoire =  (taille-1)*2;
    // test si'il n'y a pas déja un pion
    same = sameCase(king, pieceBlanche, pieceNoire, forteresse,nbPieceBlanche,nbPieceNoire,IndexArrive);
    //test movement
    if(same==false){
        mov = mouvement(IndexArrive,IndexDepart,taille, couleur,pieceBlanche, pieceNoire, nbPieceBlanche, nbPieceNoire, forteresse );
    }
    if(same ==false && mov == true){
        pionMange(IndexArrive,IndexDepart, couleur, pieceBlanche, pieceNoire, nbPieceBlanche,nbPieceNoire,taille,king);
    }
    int k =couleur;
    if(k==0){
        couleur = 1;
    }
    if(k==1){
        couleur = 0;
    }
    return couleur;
}
// couleur, taille, king , tab blanc, tab noir, forteresse, indexarrive, indexdepart
