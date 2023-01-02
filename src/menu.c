#include <stdio.h>
#include "window.h"
#include "parsing.h"
#include "menu.h"

void GameMenu(){
    int taille = -1;
    int difficile_saisie = -1;
    printf("=====================\n");
    printf("Menu de Jeu du Tablut\n");
    printf("=====================\n\n");
    printf("Selectionnez une taille pour le plateau (Doit etre un entier positif impair)\n");
    scanf("%d",&taille);
    fflush(stdin);

    // Jusqu'à ce que le joueur saisisse une valeur supérieure à 3 et impaire.
    while(taille<3 | taille%2 == 0 ){
        printf("Le nombre doit etre un entier positif impair !\n");
        scanf("%d",&taille);
        fflush(stdin);
    }
    printf("Selectionnez une difficulte (1 = Difficile, 0 = Facile)\n");
    scanf("%d",&difficile_saisie);
    fflush(stdin);

    // Jusqu'à ce que le joueur saisisse 0 ou 1.
    while(difficile_saisie != 0 && difficile_saisie != 1){
        printf("Saisie invalide : (1 = Difficile, 0 = Facile)\n");
        scanf("%d",&difficile_saisie);
        fflush(stdin);
    }
    if(difficile_saisie == 1){
        windowCreation(taille, true, false, 0);
    }
    else{
        windowCreation(taille, false, false, 0);
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
    printf("========================\n");
    printf("Menu Principal du Tablut\n");
    printf("========================\n\n");
    printf("Regles du jeu :\n"
           "Deux joueurs s'affrontent(les blancs et les noirs).\n"
           "L'objectif des blancs est de placer le roi dans une des 4 forterresses.\n"
           "Celui des noirs est donc de manger le roi blanc.\n"
           "Afin de se deplacer, selectionnez le pion a bouger et deplacez le en restant appuyer.\n"
           "Un pion (roi compris) est mange s'il se retrouve entre deux pions adverses. Attention, un pion qui se mettrait lui meme entre deux pions adverses ne sera pas mange.\n\n");
    printf("Jouer (Appuyez sur 0) / Reprendre la partie precedente (Appuyer sur 1) / Voir les statistiques (Appuyer sur 2) / Quitter le jeu (Appuyer sur 3)\n");
    scanf("%d",&jeu);
    fflush(stdin);
    while(jeu != 0 && jeu != 1 && jeu != 2 && jeu != 3){
        printf("Vous devez appuyer sur 0 pour jouer, 1 pour reprendre, 2 pour voir les statistiques et 3 pour quitter le jeu !\n");
        scanf("%d",&jeu);
        fflush(stdin);
    }
    printf("\n");
    if(jeu == 0){
        GameMenu();
    }
    else if(jeu == 1){
        windowCreation(parsing_get_size(), true,true,0);
    }
    else if(jeu == 2){
        StatsMenu();
    }
    else{
        printf("[DEBUG] : Jeu Quitte");
        return;
    }
}