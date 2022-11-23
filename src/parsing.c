#include <stdio.h>

int parsing_write(){

    //Ouvre le fichier
    char *save = "save.csv";
    FILE *fp = fopen(save, "w");
    if (fp == NULL) {
        printf("Error opening the file %s", save);
        return -1;
    }

    //écrit sur le fichier
    for (int i = 0; i < 10; i++)
        fprintf(fp, "This is the line #%d\n", i + 1);

    // close the file
    fclose(fp);
    return 0;
}

int parsing_open(){

}