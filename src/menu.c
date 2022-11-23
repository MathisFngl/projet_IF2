#include <stdio.h>
#include "window.h"
#include "parsing.h"

void GameMenu(){
    int taille = -1;
    printf("============\n");
    printf("Menu de Jeu du Tablut\n");
    printf("============\n\n");
    printf("Selectionnez une taille pour le tableau (Doit etre un entier positif impair)\n");
    scanf("%d",&taille);
    fflush(stdin);
    while(taille<3 | taille%2 == 0 | taille>17){
        printf("Le nombre doit etre un entier positif impair !\n");
        scanf("%d",&taille);
        fflush(stdin);
    }
    windowCreation(taille);
};

void MainMenu(){
    int jeu = -1;
    printf("============\n");
    printf("Menu Principal du Tablut\n");
    printf("============\n\n");
    printf("Jouer (Appuyez sur 0)\n");
    scanf("%d",&jeu);
    fflush(stdin);
    while(jeu != 0){
        printf("Vous devez appuyer sur 0 pour jouer !\n");
        scanf("%d",&jeu);
        fflush(stdin);
    }
    printf("\n");
    GameMenu();
};