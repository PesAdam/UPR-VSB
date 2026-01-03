#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
#include "output.h"

int main(int argc, char* argv[]) {
    if(argc < 4){
        printf("Pouzitie: %s <matches_file> <players_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    const char* matches_file = argv[1];
    const char* players_file = argv[2];
    const char* output_file = argv[3];
    
    // Nacitaj zapasy
    if(!load_matches(matches_file)){
        return 1;
    }
    
    // Nacitaj prezdivky
    if(!load_nicknames(players_file)){
        return 1;
    }
    
    // Validacia dat
    if(!validate_data()){
        return 1;
    }
    
    // Vygeneruj HTML
    generate_html(output_file);
    
    printf("Statistiky uspesne vygenerovane do %s\n", output_file);
    return 0;
}
