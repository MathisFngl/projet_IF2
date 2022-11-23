#include <stdio.h>

int parsing_write(int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int Roi, int taille){
    printf("%d", taille);
    int tailleBlanc = (taille-1);
    int tailleNoir =  (taille-1)*2;

    //Ouvre le fichier
    char *save = "save.csv";
    FILE *fp = fopen(save, "w");
    if (fp == NULL) {
        printf("Error opening the file %s", save);
        return -1;
    }

    //écrit sur le fichier
    fprintf(fp, "Size; %d\n", taille); // La taille de la grille
    fprintf(fp, "\n");

    fprintf(fp, "WhiteSize; %d; Values; ", tailleBlanc);
    for (int i=0; i<tailleBlanc; i++) // Le Tableau des pions blancs
        fprintf(fp, "%d;", TableauBlanc[i]);

    fprintf(fp, "\n");
    fprintf(fp, "BlackSize ; %d ; Values; ", tailleNoir);
    for (int i=0; i<tailleNoir; i++) // Le Tableau des pions noirs
        fprintf(fp, "%d ;", TableauNoir[i]);

    fprintf(fp, "\n");
    fprintf(fp, "ForteressesSize; 4 ; Values;");
    for (int i=0; i<4; i++) // Le Tableau des forteresses
        fprintf(fp, "%d ;", TableauForteresses[i]);

    fprintf(fp, "\n");
    fprintf(fp, "\n");
    fprintf(fp, "King; %d\n", Roi); // La taille de la grille

    // Ferme le fichier
    fclose(fp);
    return 0;
}

int parsing_open(){

}