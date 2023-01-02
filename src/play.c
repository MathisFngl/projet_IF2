#include "play.h"
#include <stdbool.h>
#include <stdio.h>
#include "window.h"
#include "parsing.h"

// fonctio qui permet de vérifier qu'aucun pion n'est présent sur la case d'arrivé
bool sameCase(int king, int *pieceBlanche, int *pieceNoire, int *forteresse,int nbPieceBlanche, int nbPieceNoire,int IndexArrive, int IndexDepart,int *pieges){
    bool same=false; // booléen retourné
    int i;
    // vérifie qu'il n'y a pas de pion noir
    for(i=0;i<nbPieceNoire;i++) {
        if (pieceNoire[i] == IndexArrive) {
            same = true;
        }
    }
    // vérifie qu'il n'y a pas de pion blanc
    for(i=0;i<nbPieceBlanche;i++){
        if(pieceBlanche[i]==IndexArrive){
            same = true;
        }
    }
    // vérifie qu'il n'y a pas de forteresse sauf pour le roi
    for (i=0;i<4;i++){
        if(forteresse[i]==IndexArrive && IndexDepart != king){
            same = true;
        }
    }
    // vérifie qu'il n'y a pas le roi
    if(IndexArrive == king){
        same = true;
    }
    // verif qu'il n'y a pas de pièges
    for (i=0;i<2;i++){
        if (pieges[i]==IndexArrive){
            same = true;
        }
    }

    if(same == true){
        printf("[DEBUG] : DEPLACEMENT ILLEGAL : La case est deja prise\n");
    }

    return same;
}
/* fonction qui permet de vérifier que le mouvement est bien verticale ou horizontale + qu'il ne traverse aucun élément
 * on utilise donc un booléen*/
bool mouvement(int IndexArrive, int IndexDepart,int taille,int *pieceBlanche,int *pieceNoire,int nbPieceBlanche, int nbPieceNoire, int *forteresse,int king, int *pieges){
    bool mov = false;
    int i,k,orientation;
    //vérifie que le mouvement existe
    if(IndexDepart == IndexArrive){
        printf("bouger une piece\n");
    }
     /* verifie que le mouvement est bien horizontale ou vertical
      * on vérifie pour toute les directions de la même manière que pour placer les pièces dans init_Plateau.c */
    for(i=0;i<taille;i++) {
        if (IndexDepart - taille * i == IndexArrive) {
            mov = true;
            orientation = 1; // vers le haut
        }
        if (IndexDepart + taille * i == IndexArrive) {
            mov = true;
            orientation = 3; // vers le bas
        }
        if ((IndexDepart + i == IndexArrive && i <taille-1) || (IndexDepart +i == IndexArrive && IndexDepart%taille == 0)) {
            mov = true;
            orientation = 2; // vers la droite
        }
        if ((IndexDepart - i == IndexArrive && i<taille-1) || (IndexDepart -i == IndexArrive && IndexDepart%taille == taille-1)) {
            mov = true;
            orientation = 4; // vers la gauche
        }
    }

    if(IndexArrive == taille/2+(taille/2)*taille){ // position case du milieu
        mov = false;
    }

    // vérifie qu'il n'y a pas déléments sur le passage
    if(orientation == 1){ // vers le haut
        i=1;
        while(IndexDepart-taille*i<IndexArrive){ // tant qu'on à pas atteint l'index d'arrivé
            for(k=0;k<nbPieceBlanche;k++){
                if(IndexDepart-taille*i == pieceBlanche[k]){ // passe par une pièce blanche
                    mov = false;
                }
            }
            for(k=0;k<nbPieceNoire;k++){
                if(IndexDepart-taille*i == pieceNoire[k]){ // passe par une pièce noire
                    mov = false;
                }
            }
            if(IndexDepart-taille*i==king && IndexDepart != king){ // passe par le roi
                mov = false;
            }
            for(k=0;k<2;k++){
                if(IndexDepart-taille*i == pieges[k]){ // passe par un piège
                    mov = false;
                }
            }
            for(k=0;k<4;k++){
                if(IndexDepart-taille*i == forteresse[k]){ // passe par une forteresse
                    mov = false;
                }
            }
            i++;
        }
    }
    // on procèe de la même manière pour les autres directions
    if(orientation == 2){ // vers la droite
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
            for(k=0;k<2;k++){
                if(IndexDepart+i == pieges[k]){
                    mov = false;
                }
            }
            for(k=0;k<4;k++){
                if(IndexDepart+i == forteresse[k]){
                    mov = false;
                }
            }
            i++;
        }
    }
    if(orientation == 3){ // vers le bas
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
            for(k=0;k<2;k++){
                if(IndexDepart+taille*i == pieges[k]){
                    mov = false;
                }
            }
            for(k=0;k<4;k++){
                if(IndexDepart+taille*i == forteresse[k]){
                    mov = false;
                }
            }
            i++;
        }
    }
    if(orientation == 4){ // vers la gauche
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
            for(k=0;k<2;k++){
                if(IndexDepart-i == pieges[k]){
                    mov = false;
                }
            }
            for(k=0;k<4;k++){
                if(IndexDepart-i == forteresse[k]){
                    mov = false;
                }
            }
            i++;
        }
    }
    return mov;
}
 /* fonction qui permet de vérifier si un pion est mangé suite au mouvement
  * on test à chaque fois en regardant les pièces adjacentes à l'index d'arrivé dans la même direction
  * si un pion de la couleur opposé est adjacent à l'index d'arrivé on vérifie s'il y a un pion de même couleur que celle qui
  * vient de jouer deux cases plus loin dans la même direction
  * si un pion est mangé sa valeur devient -1 ce qui permet de ne plus l'afficher sur le plateau et on incrémente le nombre
  * de pio mangé pour les stats en appelant la fonction correspondante*/
int pionMange(int IndexArrive,int IndexDepart, int c, int* pieceBlanche, int* pieceNoire, int nbPieceBlanche, int nbPieceNoire,int *pieges, int taille,int king){
    int i,k;
    if (c == 0){ // couleur = blanc -> on vérifie a chaque fois s'il y a un pion ou le roi
        for(i=0;i<nbPieceNoire;i++){
            if(IndexArrive-taille == pieceNoire[i]){ // pion en haut
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2*taille==pieceBlanche[k] || IndexArrive-2*taille == king){ // -2*taille car le pion deux fois au dessus
                        pieceNoire[i] = -1;
                        parsing_write_stats(3); // appel la fonction pour les stats
                    }
                }
            }
            if(IndexArrive+taille == pieceNoire[i]){ // pion en bas
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2*taille==pieceBlanche[k] || IndexArrive+2*taille == king){
                        pieceNoire[i] = -1;
                        parsing_write_stats(3);
                    }
                }
            }
            if(IndexArrive+1 == pieceNoire[i] && (IndexArrive+2)%taille!=1 && (IndexArrive+2)%taille!=0 ){ /* pion a droite + verif assez de case sur le cote
                 * Exemple un pion noir pourrait se trouver sur une extrémiter et un pio blanc sur l'extrémité opposé
                 * un ligne en dessous. il serait alors encerclé*/
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive+2==pieceBlanche[k] || IndexArrive+2 == king){
                        pieceNoire[i] = -1;
                        parsing_write_stats(3);
                    }
                }
            }
            if(IndexArrive-1 == pieceNoire[i] && (IndexArrive-2)%taille!=taille-1 && (IndexArrive-2)%taille!=taille-2 ){ // pion a gauche + verif assez de cases sur le cote
                for(k=0;k<nbPieceBlanche;k++){
                    if(IndexArrive-2==pieceBlanche[k] || IndexArrive-2 == king){
                        pieceNoire[i] = -1;
                        parsing_write_stats(3);
                    }
                }
            }
        }
    }
    if (c == 1){ // couleur = noire -> vérifie pour les pions plus pour les pièges
        // le roi peut aussi etre mangé donc il a des test particulier
        if(IndexArrive-taille == king){ // roi mangé par le haut
            for(k=0;k<nbPieceNoire;k++){
                if((IndexArrive-2*taille == pieceNoire[k]) || (IndexArrive-2*taille == pieges[0]) || (IndexArrive-2*taille == pieges[1])){ // test pour les pièges + pions
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        if(IndexArrive+taille == king){ // roi mangé par le bas
            for(k=0;k<nbPieceNoire;k++){
                if((IndexArrive+2*taille == pieceNoire[k]) || (IndexArrive+2*taille == pieges[0]) || (IndexArrive+2*taille == pieges[1])){
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        if(IndexArrive-1 == king){ // roi mangé par la gauche
            for(k=0;k<nbPieceNoire;k++){
                if((IndexArrive-2 == pieceNoire[k]) || (IndexArrive-2 == pieges[0]) || (IndexArrive-2 == pieges[1])){
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        if(IndexArrive+1 == king){ // roi mangé par la droite
            for(k=0;k<nbPieceNoire;k++){
                if((IndexArrive+2 == pieceNoire[k]) || (IndexArrive+2 == pieges[0]) || (IndexArrive+2 == pieges[1])){
                    king = -1;
                    parsing_write_stats(4);
                }
            }
        }
        for(i=0;i<nbPieceBlanche;i++){ // parcours tout le tab blanc
            if(IndexArrive-taille == pieceBlanche[i]){ // pion en haut
                for(k=0;k<nbPieceNoire;k++){
                    if(IndexArrive-2*taille==pieceNoire[k] || (IndexArrive-2*taille == pieges[0]) || (IndexArrive-2*taille == pieges[1])){
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
            if(IndexArrive+taille == pieceBlanche[i]){ // pion en bas
                for(k=0;k<nbPieceNoire;k++){
                    if((IndexArrive+2*taille==pieceNoire[k]) || (IndexArrive+2*taille==pieges[0]) || (IndexArrive+2*taille==pieges[1])){
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
            if(IndexArrive+1 == pieceBlanche[i] && (IndexArrive+2)%taille!=1 && (IndexArrive+2)%taille!=0){ // pion a droite + verif assez de case sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if((IndexArrive+2==pieceNoire[k]) || (IndexArrive+2==pieges[0]) || (IndexArrive+2==pieges[1])){
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
            if(IndexArrive-1 == pieceBlanche[i] && (IndexArrive+2)%taille!=1 && (IndexArrive+2)%taille!=0){ // pion a gauche + verif assez de cases sur le cote
                for(k=0;k<nbPieceNoire;k++){
                    if((IndexArrive-2==pieceNoire[k]) || (IndexArrive-2==pieges[0]) || (IndexArrive-2==pieges[1])){
                        pieceBlanche[i] = -1;
                        parsing_write_stats(4);
                    }
                }
            }
        }
    }
    /* après avoir testé si un pion est mangé, on appelle directment la fonction qui permet de modifier et donc de mettre
     * a jour les tableaux des pièces */
    movPieces(IndexDepart,IndexArrive,pieceNoire,pieceBlanche,king,c,nbPieceBlanche,nbPieceNoire);
}

/* fonction qui permet de mettre a jour tout les tableaux du au mouvement */
int movPieces(int IndexDepart,int IndexArrive, int *pieceNoire, int *pieceBlanche, int king,int c, int nbPieceBlanche, int nbPieceNoire){
    int index,i;
    if (c == 0){ // couleur = blanche
        if(IndexDepart == king){ // si on a bougé le roi
            king = IndexArrive;
            return king;
        }
        for (i=0;i<nbPieceBlanche;i++){ // permet de récupérer l'index de la pièce qui a été bougé afin de la retrouver dans le tableau
            if(pieceBlanche[i]==IndexDepart){
                index = i;
            }
        }
        // modification de la valeur de la pièce
        pieceBlanche[index]=IndexArrive;
    }

    if (c == 1){ // couleur = blanche
        for (i=0;i<nbPieceNoire;i++){
            if(pieceNoire[i]==IndexDepart){
                index = i;
            }
        }
        // modification de la valeur de la pièce
        pieceNoire[index]=IndexArrive;
    }
    return king;

}
/* fonction principale. Elle permet de faire tout les test par rapport au mouvement en appelant des fonctions
 * chaques fonctions ne peuvent pas être appellée tant que les tests de celle précédente n'est pas poisitf
 * on utilise donc des booléens pour les tests */
int play(int IndexArrive,int IndexDepart,int taille,int *pieceNoire, int *pieceBlanche,int *forteresse, int *pieges, int king, int* couleur){
    //si couleur=0 alors c'est au blanc de jouer si =1 c'est au noir
    int c = *couleur;
    int i,piece=1;
    bool same,mov;
    int nbPieceBlanche = taille -1;
    int nbPieceNoire =  (taille-1)*2;
    if(c==0){ // couleur = blanc
        for(i=0;i<nbPieceBlanche;i++){
            if(pieceBlanche[i]==IndexDepart){
                piece = 0; // verif que l'on bouge bien une piece
            }
        }
        if(king==IndexDepart){
            piece = 0;
        }
    }
    if(c==1){ // couleur = noire
        for(i=0;i<nbPieceNoire;i++){
            if(pieceNoire[i]==IndexDepart){
                piece = 0; // verif que on bouge bien une piece
            }
        }
    }
    // test si'il n'y a pas déja un pion sur l'index d'arrivé
    if(piece==0){ // seulement s'il y a bien un mouvement
        same = sameCase(king, pieceBlanche, pieceNoire, forteresse,nbPieceBlanche,nbPieceNoire,IndexArrive,IndexDepart,pieges);
    }
    else{ // retourne -2 pour indiquer que le mouvement n'est pas correct
        return -2;
    }

    //test movement
    if(same==false){
        mov = mouvement(IndexArrive,IndexDepart,taille,pieceBlanche, pieceNoire, nbPieceBlanche, nbPieceNoire, forteresse, king,pieges);
    }
    else{ // retourne -2 pour indiquer que le mouvement n'est pas correct
        return -2;
    }

    // si tous les tests de mouvement sont positif on vérifie alors si le mouvement implique qu'un pion soit mangé
    if(same == false && mov == true && piece == 0){
        king = pionMange(IndexArrive,IndexDepart, c, pieceBlanche, pieceNoire, nbPieceBlanche,nbPieceNoire,pieges, taille,king);
        return king;
    }
    else{
        return -2;
    }

}