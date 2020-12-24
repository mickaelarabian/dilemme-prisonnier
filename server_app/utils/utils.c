#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "utils.h"
#include "../../config/gameConfig/gameConfig.h"
#include "../../protocol/protocol.h"
#include "../src/game.h"
#include "../srvcxnmanager.h"

/**
 * @brief Transform the response of the player into a char* for write it in the file
 * @param response_player
 * @return result of the transformation
 **/ 
char *getReponse(int response_player){
    char *result = malloc(50);
    switch(response_player){
    case GAME_CHOICE_COLLABORATE:
        result = "COLLABORATE";
        break;
    case GAME_CHOICE_BETRAY:
        result = "BETRAY";
        break;
    case GAME_CHOICE_BOTH_COLLAB:
        result = "BOTH COLLAB";
        break;
    case GAME_CHOICE_BOTH_BETRAY:
        result = "BOTH BETRAY";
        break;
    case GAME_CHOICE_PLAYER1_WIN:
        result = "PLAYER 1 WIN";
        break;
    case GAME_CHOICE_PLAYER2_WIN:
        result = "PLAYER 2 WIN";
        break;
    default:
        break;
    }
    return result;
}
/**
 * @brief Printf for the protocol
 * @param input_protocol
 * @return
 **/
void console_log_protocol(InputProtocol input_protocol){
    printf("\n - Protocol => Game_id : %d ; Status : %d ; PLayer_id : %d ; Action : %d ; Time : %f ; Round : %d ; Montant : %f \n", 
    input_protocol.game_id, input_protocol.status, input_protocol.player_id,
    input_protocol.action, input_protocol.time, input_protocol.round, input_protocol.montant);
}

/**
 * @brief Sending a message to the thread 
 * @param input_protocol
 * @param connection
 * @return
 **/
void sendMessage(InputProtocol input_protocol, connection_t* connection){
    char* outputCLient = deserialize(input_protocol);
    write(connection->sockfd, outputCLient, strlen(outputCLient));
}

/**
 * @brief Viewing Server Information in the Console (ip and port)
 * @param ip
 * @param port
 * @return 
 **/
void infoServer(char* ip, char* port){
    printf("\n");
    printf("\033[1;31m");
    printf("************************************\n");
    printf("Adresse Ip : %s",ip);
    printf("Port : %s", port);
    printf("Ready and listening\n");
    printf("************************************\n");
    printf("\033[0m");
    printf("\n");
}
