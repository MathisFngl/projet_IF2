#include <stdio.h>
#include "window.h"
#include "parsing.h"
#include "menu.h"

void GameMenu(){
    int taille = -1;
    bool difficile;
    int difficile_saisie = -1;
    printf("============\n");
    printf("Menu de Jeu du Tablut\n");
    printf("============\n\n");
    printf("Selectionnez une taille pour le tableau (Doit etre un entier positif impair)\n");
    scanf("%d",&taille);
    fflush(stdin);
    while(taille<3 | taille%2 == 0 ){
        printf("Le nombre doit etre un entier positif impair !\n");
        scanf("%d",&taille);
        fflush(stdin);
    }
    printf("Selectionnez une difficulté (1 = Difficile, 0 = Facile)\n");
    scanf("%d",&difficile_saisie);
    fflush(stdin);
    while(difficile_saisie != 0 && difficile_saisie != 1){
        printf("Saisie invalide : (1 = Difficile, 0 = Facile)\n");
        scanf("%d",&difficile_saisie);
        fflush(stdin);
    }
    if(difficile_saisie == 1){
        windowCreation(taille, true, false);
    }
    else{
        windowCreation(taille, false, false);
    }
};

void StatsMenu(){
    int partiesJoues, victoiresDesBlancs, victoireDesNoirs, pionsNoirsManges, pionsBlancsManges;
    int *P_partiesJoues = &partiesJoues;
    int *P_victoiresDesBlancs = &victoiresDesBlancs;
    int *P_victoireDesNoirs = &victoireDesNoirs;
    int *P_pionsNoirsManges = &pionsNoirsManges;
    int *P_pionsBlancsManges = &pionsBlancsManges;

    parsing_open_stats(P_partiesJoues, P_victoiresDesBlancs, P_victoireDesNoirs, P_pionsNoirsManges,
                       P_pionsBlancsManges);

    printf("Statistiques : \n\n");

    printf("Nombre de parties Jouees : %d\n", partiesJoues);
    printf("Nombre de victoires des Blancs : %d\n", victoiresDesBlancs);
    printf("Nombre de victoires des Noirs : %d\n", victoireDesNoirs);
    printf("Nombre de pions Noirs Manges : %d\n", pionsNoirsManges);
    printf("Nombre de pions Blancs Manges : %d\n\n", pionsBlancsManges);

    MainMenu();
}

void MainMenu(){
    int jeu = -1;
    printf("============\n");
    printf("Menu Principal du Tablut\n");
    printf("============\n\n");
    printf("Jouer (Appuyez sur 0) / Reprendre la partie precedente (Appuyer sur 1) / Voir les statistiques (Appuyer sur 2)\n");
    scanf("%d",&jeu);
    fflush(stdin);
    while(jeu != 0 && jeu != 1 && jeu != 2){
        printf("Vous devez appuyer sur 0 pour jouer, 1 pour reprendre et 2 pour voir les statistiques !\n");
        scanf("%d",&jeu);
        printf("%d", jeu);
        fflush(stdin);
    }
    printf("\n");
    if(jeu == 0){
        GameMenu();
    }
    else if(jeu == 1){
        windowCreation(parsing_get_size(), true,false);
    }
    else{
        StatsMenu();
    }
};