#include <stdio.h>
#include "player.h"
#include "output.h"

// Funkcia na generovanie HTML
void generate_html(const char *output_file) {
    FILE *file = fopen(output_file, "w");
    if(!file) {
        printf("Cannot create output file\n");
        return;
    }
    
    fprintf(file, "<html>\n<head>\n<title>LoL Statistics</title>\n");
    fprintf(file, "<style>\n");
    fprintf(file, "body { font-family: Arial, sans-serif; margin: 20px; background: #f5f5f5; }\n");
    fprintf(file, "table { border-collapse: collapse; margin: 20px 0; width: 100%%; background: white; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }\n");
    fprintf(file, "th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }\n");
    fprintf(file, "th { background-color: #4CAF50; color: white; font-weight: bold; }\n");
    fprintf(file, "tr:hover { background-color: #f5f5f5; }\n");
    fprintf(file, "h1 { color: #333; text-align: center; }\n");
    fprintf(file, "h2 { color: #4CAF50; margin-top: 40px; border-bottom: 2px solid #4CAF50; padding-bottom: 10px; }\n");
    fprintf(file, "</style>\n</head>\n<body>\n");
    
    fprintf(file, "<h1>League of Legends Statistics</h1>\n");
    
    // Zakladna tabulka
    fprintf(file, "<h2>Player Statistics</h2>\n");
    fprintf(file, "<table>\n");
    fprintf(file, "<tr><th>Nickname</th><th>Kills</th><th>Assists</th><th>Deaths</th>");
    fprintf(file, "<th>Games</th><th>Wins</th><th>Losses</th>");
    fprintf(file, "<th>Red Team</th><th>Blue Team</th><th>K/D Ratio</th></tr>\n");
    
    for(int i = 0; i < player_count; i++) {
        float kd = players[i].deaths > 0 ? 
                   (float)players[i].kills / players[i].deaths : 
                   (float)players[i].kills;
        
        fprintf(file, "<tr><td>%s</td><td>%d</td><td>%d</td><td>%d</td>",
                players[i].nickname, players[i].kills, 
                players[i].assists, players[i].deaths);
        fprintf(file, "<td>%d</td><td>%d</td><td>%d</td>",
                players[i].games_played, players[i].wins, players[i].losses);
        fprintf(file, "<td>%d</td><td>%d</td><td>%.2f</td></tr>\n",
                players[i].red_team_games, players[i].blue_team_games, kd);
    }
    
    fprintf(file, "</table>\n");
    
    // Top 3 hraci podla kills
    fprintf(file, "<h2>Top 3 Players by Kills</h2>\n");
    fprintf(file, "<table>\n");
    fprintf(file, "<tr><th>Rank</th><th>Nickname</th><th>Kills</th></tr>\n");
    
    int sorted[MAX_PLAYERS];
    for(int i = 0; i < player_count; i++) {
        sorted[i] = i;
    }
    
    for(int i = 0; i < player_count - 1; i++) {
        for(int j = 0; j < player_count - i - 1; j++) {
            if(players[sorted[j]].kills < players[sorted[j+1]].kills) {
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    
    for(int i = 0; i < 3 && i < player_count; i++) {
        int idx = sorted[i];
        fprintf(file, "<tr><td>%d</td><td>%s</td><td>%d</td></tr>\n",
                i+1, players[idx].nickname, players[idx].kills);
    }
    
    fprintf(file, "</table>\n");
    
    // Top 3 hraci podla wins
    fprintf(file, "<h2>Top 3 Players by Wins</h2>\n");
    fprintf(file, "<table>\n");
    fprintf(file, "<tr><th>Rank</th><th>Nickname</th><th>Wins</th><th>Win Rate</th></tr>\n");
    
    for(int i = 0; i < player_count; i++) {
        sorted[i] = i;
    }
    
    for(int i = 0; i < player_count - 1; i++) {
        for(int j = 0; j < player_count - i - 1; j++) {
            if(players[sorted[j]].wins < players[sorted[j+1]].wins) {
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    
    for(int i = 0; i < 3 && i < player_count; i++) {
        int idx = sorted[i];
        float winrate = players[idx].games_played > 0 ?
                       (float)players[idx].wins * 100 / players[idx].games_played : 0;
        fprintf(file, "<tr><td>%d</td><td>%s</td><td>%d</td><td>%.1f%%</td></tr>\n",
                i+1, players[idx].nickname, players[idx].wins, winrate);
    }
    
    fprintf(file, "</table>\n");
    
    fprintf(file, "</body>\n</html>\n");
    fclose(file);
}