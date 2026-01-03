#include <string.h>
#include <stdio.h>
#include "player.h"

// Globalne pole hracov
Player players[MAX_PLAYERS];
int player_count = 0;

// Funkcia na najdenie hraca podla ID
int find_player(int id) {
    for(int i = 0; i < player_count; i++) {
        if(players[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Funkcia na pridanie noveho hraca
int add_player(int id) {
    if (player_count >= MAX_PLAYERS) {
        fprintf(stderr, "Error: Max player count reached (%d)\n", MAX_PLAYERS);
        return -1;
    }
    players[player_count].id = id;
    players[player_count].kills = 0;
    players[player_count].assists = 0;
    players[player_count].deaths = 0;
    players[player_count].games_played = 0;
    players[player_count].wins = 0;
    players[player_count].losses = 0;
    players[player_count].red_team_games = 0;
    players[player_count].blue_team_games = 0;
    strcpy(players[player_count].nickname, "Unknown");
    player_count++;
    return player_count - 1;
}