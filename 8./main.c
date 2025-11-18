#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void searching(char *buffer, char *search_string, int ignoruj, FILE *out) {
    if(ignoruj == 1) {
        char *buf_lower = strdup(buffer);
        char *search_lower = strdup(search_string);
        for(int i = 0; buf_lower[i]; i++) {
            buf_lower[i] = (char)tolower((unsigned char)buf_lower[i]);
        }
        for(int i = 0; search_lower[i]; i++) {
            search_lower[i] = (char)tolower((unsigned char)search_lower[i]);
        }
        if(strstr(buf_lower, search_lower) != NULL) {
            fprintf(out, "%s", buffer);
        }
        free(buf_lower);
        free(search_lower);
    } else {
        if(strstr(buffer, search_string) != NULL) {
            fprintf(out, "%s", buffer);
        }
    }
}

int main(int argc, char *argv[]) {
    char *filename = NULL;       // OPRAVA: inicializácia
    char *search_string = NULL;  // OPRAVA: inicializácia
    char *output = NULL;         // OPRAVA: inicializácia
    int ignoruj = 0;
    int i_count = 0;  // Počítadlo pre -i
    int o_count = 0;  // Počítadlo pre -o

 
    // OPRAVA: Správny cyklus - prejdi VŠETKY parametre
    for(int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            i_count++;
            if(i_count > 1) {
                printf("Parameter -i provided multiple times\n");
                return 1;
            }
            ignoruj = 1;
        } else if (strcmp(argv[i], "-o") == 0) {
            o_count++;
            if(o_count > 1) {
                printf("Parameter -o provided multiple times\n");
                return 1;
            }
            // OPRAVA: Kontrola, či existuje parameter za -o
            if(i + 1 >= argc) {
                printf("Missing output path\n");
                return 1;
            }
            output = argv[++i];
        } else {
            // Povinný parameter (nie flag)
            if(filename == NULL) {
                filename = argv[i];
            } else if(search_string == NULL) {
                search_string = argv[i];
            } else {
                // OPRAVA: Príliš veľa parametrov
                printf("Too many parameters provided\n");
                return 1;
            }
        }
    }

    // Kontrola povinných parametrov - PORADIE JE DÔLEŽITÉ!
    // Najprv kontroluj filename, potom search_string
    if (filename == NULL) {
        printf("Input path not provided\n");
        return 1;
    }
    
    if (search_string == NULL) {
        printf("Needle not provided\n");
        return 1;
    }

    // OPRAVA: Otvorenie vstupného súboru
    FILE *file = fopen(filename, "r");
    
    // OPRAVA: Správne otvorenie výstupného súboru
    FILE *out = stdout;  // Default je stdout
    FILE *out_file = NULL;
    if(output != NULL) {
        out_file = fopen(output, "w");
        out = out_file;  // OPRAVA: Priradenie správneho FILE pointra
    }

    // OPRAVA: Čítanie zo súboru, nie zo stdin
    char buffer[101];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        searching(buffer, search_string, ignoruj, out);
    }

    // OPRAVA: Zatvorenie súborov
    fclose(file);
    if(out_file != NULL) {
        fclose(out_file);
    }
    
    return 0;
}