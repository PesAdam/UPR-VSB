#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "loader.h"

// funkcia na nacitanie prezdivok
// format: ID,prezdivka
int load_nicknames(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file){
        fprintf(stderr, "Nie je mozne otvorit subor s hracmi: %s\n", filename);
        return 0;
    }
    
    char line[100];
    while(fgets(line, sizeof(line), file)){
        int id;
        char nickname[MAX_NICKNAME_LEN];
        
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;

        if(sscanf(line, "%d,%49[^\n]", &id, nickname) == 2){
            int idx = find_player(id);
            if(idx == -1){
                idx = add_player(id);
                if(idx == -1) {
                    fclose(file);
                    return 0;
                }
            }
            
            nickname[MAX_NICKNAME_LEN - 1] = '\0';
            strncpy(players[idx].nickname, nickname, MAX_NICKNAME_LEN - 1);
            players[idx].nickname[MAX_NICKNAME_LEN - 1] = '\0';
            players[idx].has_nickname = 1;
        } else {
             fprintf(stderr, "Chyba formatu v subore hracov: %s\n", line);
             fclose(file);
             return 0;
        }
    }
    
    fclose(file);
    return 1;
}

// Funkcia na nacitanie zapasov
int load_matches(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file){
        fprintf(stderr, "Nie je mozne otvorit subor so zapasmi: %s\n", filename);
        return 0;
    }
    
    char line[256];
    
    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\r\n")] = '\0';
        if(strlen(line) == 0) continue; 
        
        if(strcmp(line, "match") != 0){
            fprintf(stderr, "Ocakavany zaciatok zapasu 'match', ale prislo: %s\n", line);
            fclose(file); return 0;
        }
        
        // nacitame dalsich 5 riadkov (IDs, Stats, IDs, Stats, Winner)
        char l1[256], l2[256], l3[256], l4[256], l5[256];
        
        if(!fgets(l1, sizeof(l1), file) || 
           !fgets(l2, sizeof(l2), file) || 
           !fgets(l3, sizeof(l3), file) || 
           !fgets(l4, sizeof(l4), file) ||
           !fgets(l5, sizeof(l5), file)) {
            fprintf(stderr, "Neuplny zaznam zapasu (chybaju riadky)\n");
            fclose(file); return 0;
        }
        
        l1[strcspn(l1, "\r\n")] = '\0';
        l2[strcspn(l2, "\r\n")] = '\0';
        l3[strcspn(l3, "\r\n")] = '\0';
        l4[strcspn(l4, "\r\n")] = '\0';
        l5[strcspn(l5, "\r\n")] = '\0';
        
        int red_ids[3], blue_ids[3];
        int red_k[3], red_a[3], red_d[3];
        int blue_k[3], blue_a[3], blue_d[3];
        
        // parsovanie
        if(sscanf(l1, "%d,%d,%d", &red_ids[0], &red_ids[1], &red_ids[2]) != 3){
            fprintf(stderr, "Chyba formatu ID cerveneho timu\n"); fclose(file); return 0;
        }
        if(sscanf(l2, "%d;%d;%d,%d;%d;%d,%d;%d;%d",
               &red_k[0], &red_a[0], &red_d[0], &red_k[1], &red_a[1], &red_d[1], &red_k[2], &red_a[2], &red_d[2]) != 9){
             fprintf(stderr, "Chyba formatu statistik cerveneho timu\n"); fclose(file); return 0;
        }
        if(sscanf(l3, "%d,%d,%d", &blue_ids[0], &blue_ids[1], &blue_ids[2]) != 3){
             fprintf(stderr, "Chyba formatu ID modreho timu\n"); fclose(file); return 0;
        }
        if(sscanf(l4, "%d;%d;%d,%d;%d;%d,%d;%d;%d",
               &blue_k[0], &blue_a[0], &blue_d[0], &blue_k[1], &blue_a[1], &blue_d[1], &blue_k[2], &blue_a[2], &blue_d[2]) != 9){
             fprintf(stderr, "Chyba formatu statistik modreho timu\n"); fclose(file); return 0;
        }
        
        // validacia vitaza
        int red_won = 0;
        if(strcmp(l5, "red") == 0){
            red_won = 1;
        } else if(strcmp(l5, "blue") == 0){
            red_won = 0;
        } else {
            fprintf(stderr, "Neplatny vitaz: %s (ocakavane 'red' alebo 'blue')\n", l5);
            fclose(file); return 0;
        }
        
        // validacia ID v ramci zapasu
        int all_ids[6];
        for(int i=0; i<3; i++) all_ids[i] = red_ids[i];
        for(int i=0; i<3; i++) all_ids[i+3] = blue_ids[i];
        
        for(int i=0; i<6; i++){
            for(int j=i+1; j<6; j++){
                if(all_ids[i] == all_ids[j]){
                    fprintf(stderr, "Hrac s ID %d sa v zapase vyskytuje viackrat\n", all_ids[i]);
                    fclose(file); return 0;
                }
            }
        }
        
        // ulozenie statistik (a vytvorenie hracov ak neexistuju)
        // RED tim
        for(int i=0; i<3; i++){
            int idx = find_player(red_ids[i]);
            if(idx == -1) {
                idx = add_player(red_ids[i]);
                if(idx == -1) { fclose(file); return 0; }
            }
            
            players[idx].kills += red_k[i];
            players[idx].assists += red_a[i];
            players[idx].deaths += red_d[i];
            players[idx].games_played++;
            players[idx].red_team_games++;
            if(red_won) players[idx].wins++; else players[idx].losses++;
        }
        
        // BLUE tim
        for(int i=0; i<3; i++){
            int idx = find_player(blue_ids[i]);
            if(idx == -1) {
                idx = add_player(blue_ids[i]);
                if(idx == -1) { fclose(file); return 0; }
            }
            
            players[idx].kills += blue_k[i];
            players[idx].assists += blue_a[i];
            players[idx].deaths += blue_d[i];
            players[idx].games_played++;
            players[idx].blue_team_games++;
            if(!red_won) players[idx].wins++; else players[idx].losses++;
        }
    }
    
    fclose(file);
    return 1;
}

// validacia dat po nacitani vsetkych suborov
int validate_data(void) {
    for(int i=0; i < player_count; i++){
        // akk hrac hral v nejakom zapase, ale nema priradenu prezdivku (nebol v subore hracov)
        if(players[i].games_played > 0 && players[i].has_nickname == 0){
            fprintf(stderr, "Hrac s ID %d v zazname hry chyba v zozname prezdivok\n", players[i].id);
            return 0;
        }
    }
    return 1;
}
