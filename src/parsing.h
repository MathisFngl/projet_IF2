int parsing_write(int*, int*, int[], int[], bool, int, int);
int parsing_open(int* TableauBlanc, int* TableauNoir, int* TableauForteresses, int* TableauPieges, bool* difficile);
int parsing_get_size();
int parsing_open_stats(int* partiesJoues, int* victoiresDesBlancs, int* victoireDesNoirs, int* pionsNoirsManges, int* pionsBlancsManges);
int parsing_write_stats(int toIncrement);
