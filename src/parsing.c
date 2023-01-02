#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parsing_write(int* TableauNoir, int* TableauBlanc, int TableauForteresses[], int TableauPieges[], int Roi, int taille, int couleur){
    int tailleBlanc = ((taille-1)/4)*4;
    int tailleNoir =  ((taille-1)*2);

    //Ouvre le fichier
    char *save = "save.txt";
    FILE *fp = fopen(save, "w");

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

    for (int i=0; i<2; i++) // Le Tableau des pièges
        fprintf(fp, "%d;", TableauPieges[i]);
    fprintf(fp, "/;");

    fprintf(fp,"%d;/;", couleur); // Couleur

    fprintf(fp, "%d;/;*;", Roi); // La position du Roi

    // Ferme le fichier
    fclose(fp);
}

// Prend uniquement la première valeur du fichier (la taille)
int parsing_get_size(){
    char buff[16];
    int taille;
    char *save = "save.txt";
    FILE *fp = fopen(save, "r");

    fgets(buff, 16, fp);
    fclose(fp);
    taille = atoi(strtok(&buff[0], ";"));
    return taille;
}

// Lit le fichier pour en tirer les informations données en paramètres
int parsing_open(int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int* TableauPieges, int* couleur) {
    //Ouvre le fichier
    int taille;
    char buffer[1024];
    int compteur = 0;
    int i = 0;
    int King;

    char *save = "save.txt";
    FILE *fp = fopen(save, "r"); // Ouvre en mode lecture

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
                    TableauPieges[i] = atoi(value);
                    i++;
                    break;
                case 5:
                    *couleur = atoi(value);
                    break;
                case 6:
                    King = atoi(value);
                    return King;
            }
        }
    }
}

//Permet d'ouvrir le fichier statistiques et renvoie les informations données en paramètre
void parsing_open_stats(int* partiesJoues, int* victoiresDesBlancs, int* victoireDesNoirs, int* pionsNoirsManges, int* pionsBlancsManges){

    char *save = "stats.txt";
    FILE *fp = fopen(save, "r");

    char buffer[1024];
    int compteur = 0;
    fgets(buffer, 1024, fp);
    fclose(fp);
    char* value;
    value = strtok(buffer,";");
    while(strcmp(value, "*") != 0){
        value = strtok(NULL, ";");
        if(strcmp(value, "/") == 0){
            compteur++;
        }
        else{
            switch (compteur) {
                case 1:
                    *partiesJoues = atoi(value);
                    break;
                case 2:
                    *victoiresDesBlancs = atoi(value);
                    break;
                case 3:
                    *victoireDesNoirs = atoi(value);
                    break;
                case 4:
                    *pionsNoirsManges = atoi(value);
                    break;
                case 5:
                    *pionsBlancsManges = atoi(value);
                    break;
                default:
                    break;
            }
        }
    }
    fclose(fp);
}

// Ecrit les statistiques dans un fichier
void parsing_write_stats(int toIncrement) {

    int partiesJoues, victoiresDesBlancs, victoireDesNoirs, pionsNoirsManges, pionsBlancsManges;
    int *P_partiesJoues = &partiesJoues;
    int *P_victoiresDesBlancs = &victoiresDesBlancs;
    int *P_victoireDesNoirs = &victoireDesNoirs;
    int *P_pionsNoirsManges = &pionsNoirsManges;
    int *P_pionsBlancsManges = &pionsBlancsManges;

    //Modifie les valeurs depuis les pointeurs.
    parsing_open_stats(P_partiesJoues, P_victoiresDesBlancs, P_victoireDesNoirs, P_pionsNoirsManges,
                       P_pionsBlancsManges);

    // Ouverture du Fichier
    char *save = "stats.txt";
    FILE *fp = fopen(save, "w");

    // Ecriture des stats
    switch (toIncrement) {

        // +1 victoire des blancs
        case 1:
            fprintf(fp, "0;/;%d;/;%d;/;%d;/;%d;/;%d;/;*;", partiesJoues+1, victoiresDesBlancs+1, victoireDesNoirs, pionsNoirsManges, pionsBlancsManges);
            break;

        // +1 victoire des Noirs
        case 2:
            fprintf(fp, "0;/;%d;/;%d;/;%d;/;%d;/;%d;/;*;", partiesJoues+1, victoiresDesBlancs, victoireDesNoirs+1, pionsNoirsManges, pionsBlancsManges);
            break;

        // +1 pion noir mangé
        case 3:
            fprintf(fp, "0;/;%d;/;%d;/;%d;/;%d;/;%d;/;*;", partiesJoues, victoiresDesBlancs, victoireDesNoirs, pionsNoirsManges+1, pionsBlancsManges);
            break;

        // +1 pion blanc mangé
        case 4:
            fprintf(fp, "0;/;%d;/;%d;/;%d;/;%d;/;%d;/;*;", partiesJoues, victoiresDesBlancs, victoireDesNoirs, pionsNoirsManges, pionsBlancsManges+1);
            break;

        // Ne change rien (Si la valeur de toIncrement n'est pas reconnue
        default:
            fprintf(fp, "0;/;%d;/;%d;/;%d;/;%d;/;%d;/;*;", partiesJoues, victoiresDesBlancs, victoireDesNoirs, pionsNoirsManges, pionsBlancsManges);
            break;
    }
    fclose(fp);
}