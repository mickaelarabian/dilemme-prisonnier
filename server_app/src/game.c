#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "game.h"
#include "gameArray.h"
#include "../../config/gameConfig/gameConfig.h"
#include "../../protocol/protocol.h"
#include "../utils/utils.h"


Game_settings game_setting;

// Max round of games defined in the configuration file
int roundParty;

/**
 * @brief init game setting from config file
 * @param Settings
 * @return 
 **/
void init_config_game(Game_settings game_setting_init){
    game_setting = game_setting_init;
}

/**
 * @brief Create a game by initializing it's parameters and return it
 * @param id // id game
 * @return new game
 **/
Game* new_game(int id){
    Game *new_game = malloc(sizeof(Game));
    new_game->id = id;
    new_game->status = GAME_STATUS_WAITING_GAME;
    new_game->response_player_1 = GAME_STATUS_JOIN;
    new_game->response_player_2 = GAME_STATUS_WAITING_PLAYER;
    new_game->montant_player_1 = 0;
    new_game->montant_player_2 = 0;
    new_game->maxRound = game_setting.rounds;
    new_game->round = 0;
    new_game->time_player_1 = 0;
    new_game->time_player_2 = 0;
    new_game->result_round = 0;
    new_game->private = 0;
    return new_game;
}
/**
 * @brief Created new game, add it in the game array and return it
 * @param input_protocol
 * @param connection
 * @param game_selected
 * @return game_selected who is initializing
 **/
Game* create_new_game(InputProtocol input_protocol, connection_t* connection, Game* game_selected){
    srand(time(0));
    game_selected = new_game(rand() % 1000);
    game_selected->player_1 = connection;
    games_add(*game_selected);
    return game_selected;
}

/**
 * @brief Start game by sending message to both player
 * @param input_protocol
 * @param connection
 * @param game_selected
 * @return
 **/
void start_game(InputProtocol input_protocol, connection_t* connection, Game* game_selected){
    // Start game for the players
    // Player who has joined the game
    sendMessage(input_protocol, connection);
    // Player who has created the game
    input_protocol.player_id = game_selected->player_1->index;
    sendMessage(input_protocol, game_selected->player_1);
}

/**
 * @brief joinning game when game is waiting player
 * @param connection
 * @param game_selected
 * @return game_selected after update value and 
 **/
Game* join_game(connection_t* connection, Game* game_selected){
    game_selected->player_2 = connection;
    game_selected->response_player_2 = GAME_STATUS_READY_TO_PLAY;
    game_selected->response_player_1 = GAME_STATUS_READY_TO_PLAY;
    game_selected->private = 1;
    return game_selected;
}

/**
 * @brief Find result of the game with choice of both player
 * @param game_selected
 * @return game_selected with the result of the round and points of differences player 
 **/
Game *find_result(Game* game_selected){
    if(game_selected->response_player_1 == game_selected->response_player_2 && 
    game_selected->response_player_1 == GAME_CHOICE_COLLABORATE){
        game_selected->result_round = GAME_CHOICE_BOTH_COLLAB;
        game_selected->montant_player_1 += game_setting.twoCollaborat;
        game_selected->montant_player_2 += game_setting.twoCollaborat;
    }else if(game_selected->response_player_1 == game_selected->response_player_2 && 
        game_selected->response_player_1 == GAME_CHOICE_BETRAY){
        game_selected->result_round = GAME_CHOICE_BOTH_BETRAY;
        game_selected->montant_player_1 += game_setting.twoTreason;
        game_selected->montant_player_2 += game_setting.twoTreason;
    }else if(game_selected->response_player_1 == GAME_CHOICE_BETRAY && 
        game_selected->response_player_2 == GAME_CHOICE_COLLABORATE){
        game_selected->result_round = GAME_CHOICE_PLAYER1_WIN;
        game_selected->montant_player_1 += game_setting.freeMontant;
        game_selected->montant_player_2 += game_setting.oneTreason;
    }else{
        game_selected->result_round = GAME_CHOICE_PLAYER2_WIN;
        game_selected->montant_player_1 += game_setting.oneTreason;
        game_selected->montant_player_2 += game_setting.freeMontant;
    }
    return game_selected;
}
/**
 * @brief Find result of the game
 * @param game_selected
 * @return return who win the party
 **/ 
int find_winner(Game* game_selected){
    if(game_selected->montant_player_1 < game_selected->montant_player_2){
        return GAME_CHOICE_PLAYER1_WIN;
    }else if(game_selected->montant_player_1 > game_selected->montant_player_2) {
        return GAME_CHOICE_PLAYER2_WIN;
    }else{
        return GAME_CHOICE_EQUALITY;
    }
}
    

