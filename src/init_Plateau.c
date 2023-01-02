#include "init_Plateau.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


// Fonction récursive afin de placer les forteresses aléatoirement si le mode est compliqué
int modeCompliqueForteresse(int *tableauBlancs, int *tableauNoir, int *TableauForteresse,int nbPieceBlanche, int nbPieceNoire, int N){
    int i,forteresseOK = 0;

    while (forteresseOK != 4){
        // donne des coordonnées aléatoire aux forteresses qui ne sont pas correctement placées
        srand(time(0));
        for (i = forteresseOK;i<4;i++){
            TableauForteresse[i]= rand()%81;
        }
        /* on verifie si il n'y a pas d'autre element sur la case calculé si dessus. Si c'est le cas
         * le nombre de fortersse correctement placées augment de 1
         * on fait forteresse par forteresse pour s'assurer qu'elles soient bien placées les unes par rapport aux autres*/
        bool k = true;
        // verif pas de pièce blanche sur la case
        for(i=0;i<nbPieceBlanche;i++){
            if(TableauForteresse[forteresseOK] == tableauBlancs[i]){
                k = false;
            }
            if(TableauForteresse[forteresseOK] != tableauBlancs[i] && k != false){
                k = true;
            }
        }
        // verif pas de pièce noire sur la case
        for(i=0;i<nbPieceNoire;i++){
            if(TableauForteresse[forteresseOK] == tableauNoir[i]){
                k = false;
            }
            if(TableauForteresse[forteresseOK] != tableauNoir[i] && k != false){
                k = true;
            }
        }
        // verif pas de forteresse sur la case
        if (TableauForteresse[0] == TableauForteresse[1] || TableauForteresse[0] == TableauForteresse[2] ||
        TableauForteresse[0] == TableauForteresse[3] || TableauForteresse[1] == TableauForteresse[2] ||
        TableauForteresse[1] == TableauForteresse[3] || TableauForteresse[2] == TableauForteresse[3]){
            k = false;
        }
        // verif pas sur la cas du milieu qui est reserve au roi
        if (TableauForteresse[0] == N/2+(N/2)*N || TableauForteresse[1] == N/2+(N/2)*N ||
            TableauForteresse[2] == N/2+(N/2)*N || TableauForteresse[3] == N/2+(N/2)*N){
            k = false;
        }
        if(k == true){
            forteresseOK ++;
        }
        else{
            forteresseOK = forteresseOK;
        }
    }


}


// Fonction récursive afin de placer les pieges aléatoirement si le mode est compliqué
int modeCompliquePiege(int *tableauBlancs, int *tableauNoir, int *tableauPiege,int *TableauForteresse,int nbPieceBlanche, int nbPieceNoire,int N){
   /* on procède exactement comme pour les forteresses mais en testant pour les pièges en plus*/
    int i,piegeOK = 0;

    while (piegeOK != 2){
        srand(time(0));
        for (i = piegeOK;i<2;i++){
            tableauPiege[i]= rand()%81;
        }
        bool k = true;
        for(i=0;i<nbPieceBlanche;i++){
            if(tableauPiege[piegeOK] == tableauBlancs[i]){
                k = false;
            }
            if(tableauPiege[piegeOK] != tableauBlancs[i] && k != false){
                k = true;
            }
        }
        for(i=0;i<4;i++){
            if(tableauPiege[piegeOK] == TableauForteresse[i]){
                k = false;
            }
            if(tableauPiege[piegeOK] != TableauForteresse[i] && k != false){
                k = true;
            }
        }
        for(i=0;i<nbPieceNoire;i++){
            if(tableauPiege[piegeOK] == tableauNoir[i]){
                k = false;
            }
            if(tableauPiege[piegeOK] != tableauNoir[i] && k != false){
                k = true;
            }
        }
        if(tableauPiege[0] == tableauPiege[1]){
            k = false;
        }
        if(k == true){
            piegeOK ++;
        }
        else{
            piegeOK = piegeOK;
        }
    }
}

// fonction principale afin de créer + placer les pieces
int init_Plateau(int N, int *tableauBlancs, int *tableauNoir, int *TableauForteresse, int *tableauPiege, bool mode){
    int i,k;
    int king;
    king=N/2+(N/2)*N; // calcul position du milieu

    // création des tableaux -> un pour chaques couleurs
    int nbPieceBlanche = ((N-1)/4)*4; // 4 coté donc la formule *4
    int nbPieceNoire = ((N-1)/2)*4; // 4 cote donc la formule *4
    /* Pour les pieces noirs, le placement des pieces -> nombre de pieces placées < taille du tableau
     * il faut donc vérifier et réduire la taille du tableau si nécessaie*/
    int nbNoireCote = nbPieceNoire/4; // nombre de piece noire par coté
    int nbBlancheCote = nbPieceBlanche/4; // nombre piece blanche par cote
    int nbNoireRest,nbNoireLigne,l;
    nbNoireLigne = 1; // variable -> nb piece sur la ligne pour atteindre le bord
    l=1;
    while((king+nbBlancheCote+l)%N != N-1){ /*tant qu'on a pas atteind le bord de droite ->
                                            * derniere colonne: valeur piece % taille = taille-1 */
        nbNoireLigne++; // ajoute 1 au nombre de piece noire sur une ligne
        l++;
    }
    nbNoireRest = nbNoireCote - nbNoireLigne; // calcul nb piece a poser après avoir posé celles sur la ligne
    if(nbNoireRest%2 != 0){ // si cette valeur n'est pas un multiple de 2 -> nb de piece a repartir de chauqe cote impair
        nbPieceNoire = nbPieceNoire -4; // si impair -> on enlève 4 pour les 4 coté -> pair
    }
    printf("piece noir = %d\n",nbPieceNoire);
    //création coordonné piece blanche : on part du haut puis sens aiguille d'une montre
    int pos = 0; // direction (haut,droite,bas,gauche)
    i = 0;
    while (i < nbPieceBlanche){
        if(pos==0){ // vers le haut
            for (k=1;k<=nbBlancheCote;k++){ // tant qu'on a pas placé toute les pieces par coté
                tableauBlancs[i] = king-k*N; // part du roi et -taille*k pour verticale. k augmente
                i++;
            }
            pos ++;
        }
        if(pos==1){ // vers la droite
            for (k=1;k<=nbBlancheCote;k++){ //k s'incrémente tant qu'on a pas placé le nb pieces suffisant
                tableauBlancs[i] = king+k; // part du roi et +1 pour horizontale
                i++;
            }
            pos = 2;
        }
        if(pos==2){ // vers le bas
            for (k=1;k<=nbBlancheCote;k++){
                tableauBlancs[i] = king+k*N; // part du roi et + taille pour verticale
                i++;
            }
            pos = 3;
        }
        if(pos==3) { //vers la droie
            for (k = 1; k <=nbBlancheCote; k++) {
                tableauBlancs[i] = king - k; // part du roi et -1
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
    if(mode == false){ // mode facile
        TableauForteresse[0] = 0;
        TableauForteresse[1] = N-1;
        TableauForteresse[2] = (N-1)+(N-1)*N;
        TableauForteresse[3] = (N-1)*N;

        tableauPiege[0] = -1; // piege -1 comme ça pas sur le plateau
        tableauPiege[1] = -1;
    }
    else{ //mode compliqué
        modeCompliqueForteresse(tableauBlancs, tableauNoir,TableauForteresse,nbPieceBlanche,nbPieceNoire,N);
        modeCompliquePiege(tableauBlancs, tableauNoir,tableauPiege,TableauForteresse,nbPieceBlanche,nbPieceNoire,N);
    }
    return king;
}