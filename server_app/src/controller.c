
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "controller.h"
#include "game.h"
#include "gameArray.h"
#include "file.h"
#include "../../config/gameConfig/gameConfig.h"
#include "../../protocol/protocol.h"
#include "../utils/utils.h"
#include "../srvcxnmanager.h"


/**
 * @brief Finished the game when the game is complet or one of the player disconnect
 * @param input_protocol
 * @param game_selected
 * @param statusGame
 * @return
 **/
void controller_end_game(InputProtocol input_protocol, Game* game_selected, int statusGame){
    if(statusGame == GAME_STATUS_DISCONNECT){
        if(input_protocol.player_id == game_selected->player_1->index){
            input_protocol = relaod_protocol(input_protocol);
            input_protocol.status = GAME_STATUS_END;
            if(game_selected->player_2 != NULL){
                input_protocol.player_id = game_selected->player_2->index;
                input_protocol.montant = game_selected->montant_player_2;
                sendMessage(input_protocol, game_selected->player_2);
            }
        }else{
            input_protocol = relaod_protocol(input_protocol);
            input_protocol.status = GAME_STATUS_END;
            input_protocol.montant = game_selected->montant_player_1;
            input_protocol.player_id = game_selected->player_1->index;
            sendMessage(input_protocol, game_selected->player_1);
        }
        remove_game_array(game_selected->id);
    }
}

/**
 * @brief update protocol to the right montant and send to the right user 
 * @param game_selcted
 * @param input_protocol
 * @return input_protocol
 **/
InputProtocol update_protol_montant(Game *game_selected, InputProtocol input_protocol, int player){
    if(player == GAME_PLAYER_1){
        input_protocol.player_id = game_selected->player_1->index;
        input_protocol.montant = game_selected->montant_player_1;
    }else {
        input_protocol.player_id = game_selected->player_2->index;
        input_protocol.montant = game_selected->montant_player_2;
    }
    if(game_selected->round == game_selected->maxRound){
        input_protocol.action = find_winner(game_selected);
        input_protocol.status = GAME_STATUS_END;
    }else {
        input_protocol.action = game_selected->result_round;
        input_protocol.status = GAME_STATUS_START;
    }
    return input_protocol;
}

/**
 * @brief Update the game status and sending response or en game
 * @param input_protocol
 * @param game_selected
 * @return 
 **/
void update_game_response_user(InputProtocol input_protocol, Game* game_selected){
    if(game_selected->status != GAME_STATUS_WAITING_RESULT_PLAYER){
        game_selected->status = GAME_STATUS_WAITING_RESULT_PLAYER;
    }else{
        game_selected->round += 1;
        input_protocol.round = game_selected->round;
        game_selected = find_result(game_selected);
        game_selected->status = GAME_STATUS_RESULT;
        InputProtocol input_protocol1 = update_protol_montant(game_selected, input_protocol ,GAME_PLAYER_1);
        InputProtocol input_protocol2 = update_protol_montant(game_selected, input_protocol, GAME_PLAYER_2);
        console_log_protocol(input_protocol1);
        console_log_protocol(input_protocol2);
        add_result_file(game_selected);
        sendMessage(input_protocol1, game_selected->player_1);
        sendMessage(input_protocol2, game_selected->player_2);
    }
}

/**
 * @brief find the right player and put the result in the game_selected
 * @param input_protocol
 * @param game_selected
 * @return
 **/
void controller_choice(InputProtocol input_protocol, Game* game_selected){
    // choice player and check if the other already have make his choice
    // select player 1
    if(game_selected->player_1->index == input_protocol.player_id){
        game_selected->response_player_1 = input_protocol.action;
        game_selected->time_player_1 = input_protocol.time;
        input_protocol.player_id = game_selected->player_1->index;
        printf("\n *** Reponse joueur 1 : %d", game_selected->response_player_1);
        update_game_response_user(input_protocol, game_selected);
    }else{ // select player 2
        game_selected->response_player_2 = input_protocol.action;
        game_selected->time_player_2 = input_protocol.time;
        input_protocol.player_id = game_selected->player_2->index;
        printf("\n *** Reponse joueur 2 : %d", game_selected->response_player_2);
        update_game_response_user(input_protocol, game_selected);
    }
}

/**
 * @brief Main function of the controller usef for dispatch the actions
 * @param input_protocol
 * @param connection
 * @return 
 **/
void controller_main(InputProtocol input_protocol, connection_t* connection){
    
    Game *game_selected;
   
    switch (input_protocol.status) {
        // Protocol disconnect
        case GAME_STATUS_DISCONNECT:
            if(input_protocol.game_id != 0){
                game_selected = search_game_by_id(input_protocol.game_id);
                if(game_selected != NULL){
                    controller_end_game(input_protocol, game_selected, GAME_STATUS_DISCONNECT);
                }         
            }
            break;
        // Protocol when first connection by the player
        case GAME_STATUS_FIRST_CONNECTION:
            // Search game for played 
            game_selected = search_game_valid();
            // If no game is available
            if(game_selected == NULL){
                    printf("\n%s", "Create new game\n");
                    // Function for created new game
                    game_selected = create_new_game(input_protocol, connection, game_selected);

                    input_protocol.game_id = game_selected->id;
                    input_protocol.status = GAME_STATUS_WAITING_GAME;
                    input_protocol.round = game_selected->round;
                    // Sending protocol to the player 1
                    sendMessage(input_protocol, connection);
            // If we found a game available
            }else if(game_selected->response_player_2 == GAME_STATUS_WAITING_PLAYER) {
                    printf("\n%s", "Join game\n");
                    // Function for joinning a game
                    game_selected = join_game(connection, game_selected);
                    input_protocol.game_id = game_selected->id;
                    input_protocol.status = GAME_STATUS_START;
                    input_protocol.action = GAME_STATUS_WAITING_RESULT;
                    input_protocol.round = game_selected->round;
                    // Function for start game by warning both player
                    start_game(input_protocol, connection, game_selected);
            // Error during search game
            }else{
                printf("\n %d", game_selected->id);
                printf("\n Error during search game");
            }
            break;
        // Protocol waiting the result of differents game 
        case GAME_STATUS_WAITING_RESULT_PLAYER:
            // Search game of the player
            game_selected = search_game_by_id(input_protocol.game_id);
            if(game_selected != NULL) {
                printf(" - Player result :\n");
                console_log_protocol(input_protocol);
                // Function for compare the different choice of players and save it in the file
                controller_choice(input_protocol, game_selected);
            }

            break;
        // protocol error
        case GAME_STATUS_ERROR: 
            printf("\n - Game error : GAME_STATUS_ERROR");
            break;
        default:
            // Error when the protocol received is not compliant
            printf("\n - Error during sending protocol to server : Protocol not found");
            break;
    }
}
