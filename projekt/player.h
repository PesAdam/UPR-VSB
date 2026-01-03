#ifndef PLAYER_H
#define PLAYER_H

#define MAX_PLAYERS 100
#define MAX_NICKNAME_LEN 50

typedef struct {
    int id;
    char nickname[MAX_NICKNAME_LEN];
    int kills;
    int assists;
    int deaths;
    int games_played;
    int wins;
    int losses;
    int red_team_games;
    int blue_team_games;
} Player;

extern Player players[MAX_PLAYERS];
extern int player_count;

int find_player(int id);
int add_player(int id);

#endif
