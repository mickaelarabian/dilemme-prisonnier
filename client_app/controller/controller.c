#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "controller.h"
#include "../../protocol/protocol.h"
#include "../../config/gameConfig/gameConfig.h"

/**
 * @brief Function to execute client action
 * @param choice
 * @param sockfd
 * @param cli_protocol
 * @return 
 **/
void player_action(int choice, int sockfd, InputProtocol cli_protocol){
    cli_protocol.action = choice;
    char *message = deserialize(cli_protocol);
    printf("\n ###SEND###");
    console_log_protocol(cli_protocol);
    send_message(message, sockfd);
}

/**
 * @brief Function to send messages to the server
 * @param message
 * @param sockfd
 * @return 
 **/
void send_message(char *message, int sockfd){
    write(sockfd, message, strlen(message));
}

/**
 * @brief Transform status or action into a char* for write it in the gui
 * @param label
 * @param cli_protocol
 * @return result of the transformation
 **/ 
char *get_message(int label, InputProtocol cli_protocol){
    char *message = malloc(100);
    switch (label)
    {
    case GAME_STATUS_WAITING_GAME:
        message = "En attente d'un autre joueur";
        break;
    case GAME_STATUS_WAITING_RESULT_PLAYER:
        message = "En attente du resultat";
        break;
    case GAME_STATUS_START:
        message = "A vous de jouer";
        break;
    case GAME_CLIENT_WAITING_SERVER:
        message = (label == GAME_STATUS_MESSAGE) ? "En attente du serveur" : "";
        break;
    case GAME_STATUS_END:
        message = "Partie terminée";
        break;
    case GAME_CHOICE_BOTH_COLLAB:
        message = "Vous avez tous les deux colaboré";
        break;
    case GAME_CHOICE_BOTH_BETRAY:
        message = "Vous avez tous les deux trahi";
        break;
    case GAME_CHOICE_PLAYER1_WIN:
        if(cli_protocol.status == GAME_STATUS_END){
            message = (cli_protocol.player_id % 2 == 0) ? "Vous avez perdu la partie !" : "Vous avez gagné la partie !" ;
        } else{
            message = (cli_protocol.player_id % 2 == 0) ? "Vous avez été trahi" : "Vous l'avez trahi" ;
        }
        break;
    case GAME_CHOICE_PLAYER2_WIN:
        if(cli_protocol.status == GAME_STATUS_END){
            message = (cli_protocol.player_id % 2 == 0) ? "Vous avez gagné la partie !" : "Vous avez perdu la partie !" ;
        } else {
            message = (cli_protocol.player_id % 2 == 0) ? "Vous l'avez trahi" : "Vous avez été trahi" ;
        }
        break;
    case GAME_CHOICE_EQUALITY:
        message = "Égalité !";
        break;
    default:
        break;
    }
    return message;
}

/**
 * @brief Printf for the client
 * @return
 **/
void info_client(){
    printf("\033[1;32m");
    printf("************************************\n");
    printf("Open client\n");
    printf("************************************\n");
    printf("\033[0m");
    printf("\n");
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