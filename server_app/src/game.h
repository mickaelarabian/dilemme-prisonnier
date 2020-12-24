
#ifndef GAME_H
#define GAME_H

#include "../srvcxnmanager.h"
#include "../../protocol/protocol.h"

// Structure of one game 
typedef struct
{
    int id;
    int status;
    connection_t* player_1;
    int response_player_1;
    connection_t* player_2;
    int response_player_2;
    double time_player_1;
    double time_player_2;
    double montant_player_1;
    double montant_player_2;
    int result_round;
    int maxRound;
    int round;
    int private;
} Game;

// Structure that contains the parameters of the configuration files part 
typedef struct
{
    double twoTreason;
    double oneTreason;
    double twoCollaborat;
    double freeMontant;
    int rounds;
} Game_settings;


void init_config_game(Game_settings game_setting_init);
Game* new_game(int id);
void start_game(InputProtocol inputClient, connection_t* connection, Game* game_selected);
Game* create_new_game(InputProtocol inputClient, connection_t* connection, Game* game_selected);
Game* join_game(connection_t* connection, Game* game_selected);
Game *find_result(Game* game_selected);
int find_winner(Game* game_selected);

#endif /* GAME_H */