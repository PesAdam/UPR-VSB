#include <stdio.h>
#include "player.h"
#include "output.h"

// Funkcia na generovanie HTML
void generate_html(const char *output_file) {
    FILE *file = fopen(output_file, "w");
    if(!file){
        printf("Nie je mozne vytvorit vystupny subor\n");
        return;
    }
    
    fprintf(file, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(file, "<meta charset=\"UTF-8\">\n");
    fprintf(file, "<title>LoL Statistiky</title>\n");
    fprintf(file, "<style>\n");
    // Modern Dark Theme CSS
    fprintf(file, "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; background-color: #1a1a1a; color: #e0e0e0; }\n");
    fprintf(file, ".container { max-width: 1000px; margin: 0 auto; padding: 40px 20px; }\n");
    fprintf(file, "table { border-collapse: collapse; margin: 25px 0; width: 100%%; background-color: #2d2d2d; box-shadow: 0 4px 6px rgba(0,0,0,0.3); border-radius: 8px; overflow: hidden; }\n");
    fprintf(file, "th, td { padding: 15px; text-align: left; border-bottom: 1px solid #404040; }\n");
    fprintf(file, "th { background-color: #007acc; color: #ffffff; font-weight: 600; text-transform: uppercase; letter-spacing: 1px; font-size: 0.9em; }\n");
    fprintf(file, "tr:last-child td { border-bottom: none; }\n");
    fprintf(file, "tr:hover { background-color: #383838; transition: background-color 0.2s; }\n");
    fprintf(file, "h1 { color: #007acc; text-align: center; font-size: 2.5em; margin-bottom: 10px; font-weight: 300; }\n");
    fprintf(file, "h2 { color: #ffffff; margin-top: 50px; border-left: 5px solid #007acc; padding-left: 15px; font-weight: 400; }\n");
    fprintf(file, ".footer { margin-top: 60px; text-align: center; color: #666; font-size: 0.85em; border-top: 1px solid #333; padding-top: 20px; }\n");
    fprintf(file, ".signature { color: #007acc; font-weight: bold; }\n");
    fprintf(file, "</style>\n</head>\n<body>\n");
    
    fprintf(file, "<div class=\"container\">\n");
    fprintf(file, "<h1>League of Legends - Prehľad</h1>\n");
    
    // Zakladna tabulka
    fprintf(file, "<h2>Celkové štatistiky hráčov</h2>\n");
    fprintf(file, "<table>\n");
    fprintf(file, "<tr><th>Prezývka</th><th>Kills</th><th>Assists</th><th>Deaths</th>");
    fprintf(file, "<th>Hry</th><th>Výhry</th><th>Prehry</th>");
    fprintf(file, "<th>Červený tím</th><th>Modrý tím</th><th>K/D Pomer</th></tr>\n");
    
    for(int i=0; i < player_count; i++){
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
    fprintf(file, "<h2>Top 3 hráči podľa Kills</h2>\n");
    fprintf(file, "<table>\n");
    fprintf(file, "<tr><th>Poradie</th><th>Prezývka</th><th>Kills</th></tr>\n");
    
    int sorted[MAX_PLAYERS];
    for(int i=0; i < player_count; i++){
        sorted[i] = i;
    }
    
    for(int i=0; i < player_count - 1; i++){
        for(int j=0; j < player_count - i - 1; j++){
            if(players[sorted[j]].kills < players[sorted[j+1]].kills){
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    
    for(int i=0; i < 3 && i < player_count; i++){
        int idx = sorted[i];
        fprintf(file, "<tr><td>%d.</td><td>%s</td><td>%d</td></tr>\n",
                i+1, players[idx].nickname, players[idx].kills);
    }
    
    fprintf(file, "</table>\n");
    
    // Top 3 hraci podla wins
    fprintf(file, "<h2>Top 3 hráči podľa Výhier</h2>\n");
    fprintf(file, "<table>\n");
    fprintf(file, "<tr><th>Poradie</th><th>Prezývka</th><th>Výhry</th><th>Úspešnosť</th></tr>\n");
    
    for(int i=0; i < player_count; i++){
        sorted[i] = i;
    }
    
    for(int i=0; i < player_count - 1; i++){
        for(int j=0; j < player_count - i - 1; j++){
            if(players[sorted[j]].wins < players[sorted[j+1]].wins){
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    
    for(int i=0; i < 3 && i < player_count; i++){
        int idx = sorted[i];
        float winrate = players[idx].games_played > 0 ?
                       (float)players[idx].wins * 100 / players[idx].games_played : 0;
        fprintf(file, "<tr><td>%d.</td><td>%s</td><td>%d</td><td>%.1f%%</td></tr>\n",
                i+1, players[idx].nickname, players[idx].wins, winrate);
    }
    
    fprintf(file, "</table>\n");
    
    fprintf(file, "<div class=\"footer\">\n");
    fprintf(file, "<span class=\"signature\">UPR Projekt - Belo</span> &bull; verzia 1.0\n");
    fprintf(file, "</div>\n");
    
    fprintf(file, "</div>\n</body>\n</html>\n");
    fclose(file);
}