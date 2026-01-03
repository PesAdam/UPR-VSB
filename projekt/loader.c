#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "loader.h"

// Funkcia na nacitanie prezdivok
int load_nicknames(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file) {
        fprintf(stderr, "Cannot open players file: %s\n", filename);
        return 0;
    }
    
    char line[100];
    while(fgets(line, sizeof(line), file)) {
        int id;
        char nickname[MAX_NICKNAME_LEN];
        // Ensure nickname doesn't overflow
        if(sscanf(line, "%d,%49[^\n]", &id, nickname) == 2) {
            int idx = find_player(id);
            if(idx != -1) {
                // Ensure null termination and copy safely
                nickname[MAX_NICKNAME_LEN - 1] = '\0';
                strncpy(players[idx].nickname, nickname, MAX_NICKNAME_LEN - 1);
                players[idx].nickname[MAX_NICKNAME_LEN - 1] = '\0';
            }
        }
    }
    
    fclose(file);
    return 1;
}

// Funkcia na nacitanie zapasov
int load_matches(const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file) {
        fprintf(stderr, "Cannot open matches file: %s\n", filename);
        return 0;
    }
    
    char line[256];
    int line_num = 0;
    
    int red_ids[3], blue_ids[3];
    int red_k[3], red_a[3], red_d[3];
    int blue_k[3], blue_a[3], blue_d[3];
    char winner[10];
    
    while(fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = '\0';
        
        if(strcmp(line, "match") == 0) {
            line_num = 0;
            continue;
        }
        
        line_num++;
        
        if(line_num == 1) {
            if(sscanf(line, "%d,%d,%d", &red_ids[0], &red_ids[1], &red_ids[2]) != 3) {
                 fprintf(stderr, "Error parsing red team IDs\n");
                 fclose(file); return 0;
            }
        }
        else if(line_num == 2) {
            if(sscanf(line, "%d;%d;%d,%d;%d;%d,%d;%d;%d",
                   &red_k[0], &red_a[0], &red_d[0],
                   &red_k[1], &red_a[1], &red_d[1],
                   &red_k[2], &red_a[2], &red_d[2]) != 9) {
                 fprintf(stderr, "Error parsing red team stats\n");
                 fclose(file); return 0;
            }
        }
        else if(line_num == 3) {
            if(sscanf(line, "%d,%d,%d", &blue_ids[0], &blue_ids[1], &blue_ids[2]) != 3) {
                 fprintf(stderr, "Error parsing blue team IDs\n");
                 fclose(file); return 0;
            }
        }
        else if(line_num == 4) {
             if(sscanf(line, "%d;%d;%d,%d;%d;%d,%d;%d;%d",
                   &blue_k[0], &blue_a[0], &blue_d[0],
                   &blue_k[1], &blue_a[1], &blue_d[1],
                   &blue_k[2], &blue_a[2], &blue_d[2]) != 9) {
                 fprintf(stderr, "Error parsing blue team stats\n");
                 fclose(file); return 0;
            }
        }
        else if(line_num == 5) {
            strncpy(winner, line, sizeof(winner) - 1);
            winner[sizeof(winner) - 1] = '\0';
            
            int red_won = (strcmp(winner, "red") == 0);
            
            // Process Red Team
            for(int i = 0; i < 3; i++) {
                int idx = find_player(red_ids[i]);
                if(idx == -1) {
                    idx = add_player(red_ids[i]);
                    if (idx == -1) {
                         fclose(file); return 0;
                    }
                }
                
                players[idx].kills += red_k[i];
                players[idx].assists += red_a[i];
                players[idx].deaths += red_d[i];
                players[idx].games_played++;
                players[idx].red_team_games++;
                
                if(red_won) {
                    players[idx].wins++;
                } else {
                    players[idx].losses++;
                }
            }
            
            // Process Blue Team
            for(int i = 0; i < 3; i++) {
                int idx = find_player(blue_ids[i]);
                if(idx == -1) {
                    idx = add_player(blue_ids[i]);
                     if (idx == -1) {
                         fclose(file); return 0;
                    }
                }
                
                players[idx].kills += blue_k[i];
                players[idx].assists += blue_a[i];
                players[idx].deaths += blue_d[i];
                players[idx].games_played++;
                players[idx].blue_team_games++;
                
                if(!red_won) {
                    players[idx].wins++;
                } else {
                    players[idx].losses++;
                }
            }
            
            line_num = 0;
        }
    }
    
    fclose(file);
    return 1;
}
