#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fixtures.h"
#include "../../../config/gameConfig/gameConfig.h"
#include "../../src/game.h"
#include "../../utils/utils.h"
#include "../../srvcxnmanager.h"


char* get_some_protocol_char_1(){
    return "600;5;1;7;0.000000;0;0.000000";
} 
char* get_some_protocol_char_2(){
    return "600;5;2;7;0.000000;0;0.000000";
} 
char* get_some_protocol_char_3(){
    return "300;5;3;7;0.000000;0;0.000000";
} 
char* get_some_protocol_char_4(){
    return "300;5;4;7;0.000000;0;0.000000";
} 
char* get_some_protocol_first_connection(){
    return "0;5;600;0;0.000000;0;0.000000";
} 

InputProtocol get_some_protocol_struct_1(){
    InputProtocol some_protocol_struct_1;
    some_protocol_struct_1.game_id = 600;
    some_protocol_struct_1.status = 5;
    some_protocol_struct_1.player_id = 1;
    some_protocol_struct_1.action = 7;
    some_protocol_struct_1.time = 0.00;
    some_protocol_struct_1.round = 0;
    some_protocol_struct_1.montant = 0.0; 
    return some_protocol_struct_1;
}
InputProtocol get_some_protocol_struct_2(){
    InputProtocol some_protocol_struct_2;
    some_protocol_struct_2.game_id = 600;
    some_protocol_struct_2.status = 5;
    some_protocol_struct_2.player_id = 2;
    some_protocol_struct_2.action = 7;
    some_protocol_struct_2.time = 0.00;
    some_protocol_struct_2.round = 0;
    some_protocol_struct_2.montant = 0.0; 
    return some_protocol_struct_2;
}
InputProtocol get_some_protocol_struct_3(){
    InputProtocol some_protocol_struct_3;
    some_protocol_struct_3.game_id = 300;
    some_protocol_struct_3.status = 5;
    some_protocol_struct_3.player_id = 3;
    some_protocol_struct_3.action = 7;
    some_protocol_struct_3.time = 0.00;
    some_protocol_struct_3.round = 0;
    some_protocol_struct_3.montant = 0.0; 
    return some_protocol_struct_3;
}
InputProtocol get_some_protocol_struct_4(){
    InputProtocol some_protocol_struct_4;
    some_protocol_struct_4.game_id = 300;
    some_protocol_struct_4.status = 5;
    some_protocol_struct_4.player_id = 4;
    some_protocol_struct_4.action = 7;
    some_protocol_struct_4.time = 0.00;
    some_protocol_struct_4.round = 0;
    some_protocol_struct_4.montant = 0.0; 
    return some_protocol_struct_4;
}
Game* some_game(){
    Game *new_game = malloc(250);
    new_game->id = 1;
    new_game->status = 5;
    new_game->response_player_1 = 0;
    new_game->response_player_2 = 0;
    new_game->montant_player_1 = 0;
    new_game->montant_player_2 = 0;
    new_game->maxRound = 0;
    new_game->round = 0;
    new_game->time_player_1 = 0;
    new_game->time_player_2 = 0;
    new_game->result_round = 0;
    new_game->private = 0;
    return new_game;
}
Game* some_game_2(){
    Game *new_game = malloc(250);
    new_game->id = 5;
    new_game->status = GAME_STATUS_WAITING_GAME;
    new_game->response_player_1 = GAME_STATUS_JOIN;
    new_game->response_player_2 = GAME_STATUS_WAITING_PLAYER;
    new_game->montant_player_1 = 0;
    new_game->montant_player_2 = 0;
    new_game->maxRound = 3; // config file round
    new_game->round = 0;
    new_game->time_player_1 = 0;
    new_game->time_player_2 = 0;
    new_game->result_round = 0;
    new_game->private = 0;
    return new_game;
}

char* char_to_file(Game* game){
    char* someValue = malloc(100);
    sprintf(someValue, "%d;%d;%d;%s;%f;%f;%s;%f;%f;%s;\n",
        game->id,
        game->maxRound, 
        game->round, 
        getReponse(game->response_player_1), 
        game->time_player_1, 
        game->montant_player_1  
        ,getReponse(game->response_player_2), 
        game->time_player_2 ,
        game->montant_player_2,
        getReponse(game->result_round));
    return someValue;
}

connection_t* some_connection(){
    connection_t* some_connection_value = malloc(100);
    some_connection_value->addr_len = 1;
    some_connection_value->index = 1;
    some_connection_value->sockfd = 1;
    return some_connection_value;
}


