/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aurelio
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <stdbool.h>
#include "../config/config.h"
#include "../config/gameConfig/gameConfig.h"
#include "srvcxnmanager.h"
#include "./src/gameArray.h"
#include "./src/game.h"
#include "./src/file.h"
#include "utils/utils.h"

Settings setting;

/**
 * @brief Function that initializes a Game_settings structure
 * @param setting
 * @return Game_settings
**/
Game_settings config_game(Settings setting){
    Game_settings game_setting;
    game_setting.rounds = atoi(settings_getOption(&setting, "rounds"));
    game_setting.twoTreason = atof(settings_getOption(&setting, "twoTreason"));
    game_setting.oneTreason = atof(settings_getOption(&setting, "oneTreason"));
    game_setting.twoCollaborat = atof(settings_getOption(&setting, "twoCollab"));
    game_setting.freeMontant = atof(settings_getOption(&setting, "freeMont"));
    return game_setting;
}

/**
 * @brief Main function of server
 * @return
**/
int main(int argc, char** argv) {
    int sockfd = -1;
    int index = 1;
    connection_t *connection;
    Game_array* game_array[MAX_GAME];

    pthread_t thread;
    /* init config file server*/
    settings_initialize(&setting, "../config/configServer.cfg");

    infoServer(settings_getOption(&setting, "ip_address"), settings_getOption(&setting, "port"));
    /* init array*/
    init_sockets_array();
    /* init game config */ 
    init_config_game(config_game(setting));
    /* create file for save games */
    create_file();
    /* create socket */
    sockfd = create_server_socket(setting);

    /* listen on port , stack size 50 for incoming connections*/
    if (listen(sockfd, 50) < 0) {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }


    //Wait for connection
    while (true) {
        /* accept incoming connections */
        connection = (connection_t *) malloc(sizeof (connection_t));
        connection->sockfd = accept(sockfd, &connection->address, &connection->addr_len);
        connection->index = index++;
        if (connection->sockfd <= 0) {
            free(connection);
        } else {
            /* start a new thread but do not wait for it */
            pthread_create(&thread, 0, threadProcess, (void *) connection);
            pthread_detach(thread);
        }
    }
    return (EXIT_SUCCESS);
}

