#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// funkcia na prevod textu na male pismena
void to_lower(char *text) {
    for(int i = 0; text[i]; i++) {
        text[i] = (char)tolower((unsigned char)text[i]);
    }
}

// vyhladavanie textu v riadku
void search_in_row(char *line, char *text, int ignore_case, FILE *vystup) {
    if(ignore_case == 0) {
        // priame porovnanie
        if(strstr(line, text)) {
            fprintf(vystup, "%s", line);
        }
        return;
    }
    
    // ignorovanie velkosti pismen - potrebujeme kopie
    char *small_line = strdup(line);
    char *small_text = strdup(text);
    
    to_lower(small_line);
    to_lower(small_text);
    
    if(strstr(small_line, small_text)) {
        fprintf(vystup, "%s", line);
    }
    
    free(small_line);
    free(small_text);
}

int main(int argc, char *argv[]) {
    char *file_path = NULL;       
    char *wanted_text = NULL;  
    char *o_file = NULL;        
    int ignore_case = 0;
    int num_i = 0;  
    int num_o = 0;

    // spracovanie parametrov
    for(int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            num_i++;
            if(num_i > 1) {
                printf("Parameter -i provided multiple times\n");
                return 1;
            }
            ignore_case = 1;
            continue;
        }
        
        if (strcmp(argv[i], "-o") == 0) {
            num_o++;
            if(num_o > 1) {
                printf("Parameter -o provided multiple times\n");
                return 1;
            }
            if(i + 1 >= argc) {
                printf("Missing output path\n");
                return 1;
            }
            o_file = argv[++i];
            continue;
        }
        
        // povinne parametre
        if(file_path == NULL) {
            file_path = argv[i];
        } else if(wanted_text == NULL) {
            wanted_text = argv[i];
        } else {
            printf("Too many parameters provided\n");
            return 1;
        }
    }

    // kontrola povinnych parametrov - poradi je dolezite
    if (file_path == NULL) {
        printf("Input path not provided\n");
        return 1;
    }
    
    if (wanted_text == NULL) {
        printf("Needle not provided\n");
        return 1;
    }
    
    // otvorenie suborov
    FILE *vstup = fopen(file_path, "r");
    FILE *vystup = stdout;
    FILE *subor_vystup = NULL;
    
    if(o_file) {
        subor_vystup = fopen(o_file, "w");
        vystup = subor_vystup;  
    }

    // citanie a vyhladavanie po riadkoch
    char buffer[101] = {0};
    while(fgets(buffer, sizeof(buffer), vstup)) {
        search_in_row(buffer, wanted_text, ignore_case, vystup);
    }

    // zatvorenie suborov
    fclose(vstup);
    if(subor_vystup) {
        fclose(subor_vystup);
    }
    
    return 0;
}