#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parsing_write(int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int Roi, int taille){
    int tailleBlanc;
    if(taille == 11){
        tailleBlanc = 8;
    }
    else{
        tailleBlanc = taille-1;
    }
    int tailleNoir =  (taille-1)*2;

    //Ouvre le fichier
    char *save = "save.txt";
    FILE *fp = fopen(save, "w");
    if (fp == NULL) {
        printf("Error opening the file %s", save);
        return -1;
    }

    //écrit sur le fichier
    fprintf(fp, "%d;/;", taille); // La taille de la grille

    for (int i=0; i<tailleBlanc; i++) // Le Tableau des pions blancs
        fprintf(fp, "%d;", TableauBlanc[i]);
    fprintf(fp, "/;");

    for (int i=0; i<tailleNoir; i++) // Le Tableau des pions noirs
        fprintf(fp, "%d;", TableauNoir[i]);
    fprintf(fp, "/;");

    for (int i=0; i<4; i++) // Le Tableau des forteresses
        fprintf(fp, "%d;", TableauForteresses[i]);
    fprintf(fp, "/;");

    fprintf(fp, "%d;*;", Roi); // La position du Roi

    // Ferme le fichier
    fclose(fp);
    return 0;
}

int parsing_get_size(){
    char buff[16];
    char *save = "save.txt";
    FILE *fp = fopen(save, "r");
    if (fp == NULL) {
        printf("Error opening the file %s", save);
        return -1;
    }
    fgets(buff, 3, fp);
    int size = atoi(buff);
    return size;
}

int parsing_open(int* TableauBlanc, int* TableauNoir, int* TableauForteresses) {
    //Ouvre le fichier
    int taille;
    char buffer[1024];
    int compteur = 0;
    int i = 0;
    int King;

    char *save = "save.txt";
    FILE *fp = fopen(save, "r");

    if (fp == NULL) {
        printf("Error opening the file %s for OPEN", save);
        return -1;
    }

    //Lecture du fichier
    fgets(buffer, 1024, fp);
    fclose(fp);
    char *value = strtok(buffer,";");
    while(strcmp(value, "*") != 0){
        value = strtok(NULL, ";");
        if(strcmp(value, "/") == 0){
            compteur++;
            i = 0;
        }
        else{
            switch (compteur) {
                case 0:
                    taille = atoi(value);
                    printf("%d", taille);
                    break;
                case 1:
                    TableauBlanc[i] = atoi(value);
                    i++;
                    break;
                case 2:
                    TableauNoir[i] = atoi(value);
                    i++;
                    break;
                case 3:
                    TableauForteresses[i] = atoi(value);
                    i++;
                    break;
                case 4:
                    King = atoi(value);
                    return King;
            }
        }
    }
}