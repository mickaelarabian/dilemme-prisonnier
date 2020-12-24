#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "game.h"
#include "../utils/utils.h"
#include <time.h>
char path[1024];
/**
 * @brief function to create file for save games
 * @return
 **/
void create_file(){
    FILE* fichier = NULL;
    
    strcat(path,"../results/");
    char name[100];
    sprintf(name, "%d", time(NULL));
    strcat(path, name);
    strcat(path, ".csv");

    fichier = fopen(path, "w");
    // if file is not created we initialize it with the columns titles 
    if(fichier != NULL) {
        fprintf(fichier, "game_id;max_round;round;player_1_response;player_1_time;player_1_montant;player_2_response;player_2_time;player_2_montant;\n");
        fclose(fichier);
    }
}

/**
 * @brief add result of the round for a game in the file 
 * @param game_selected
 * @return
 **/
void add_result_file(Game* game_selected){
    FILE* fichier = NULL;
    // open the file and we write the round of the game in it
    fichier = fopen(path, "a");
    fprintf(fichier, "%d;%d;%d;%s;%f;%f;%s;%f;%f;%s;\n",
        game_selected->id,
        game_selected->maxRound, 
        game_selected->round, 
        getReponse(game_selected->response_player_1), 
        game_selected->time_player_1, 
        game_selected->montant_player_1  
        ,getReponse(game_selected->response_player_2), 
        game_selected->time_player_2 ,
        game_selected->montant_player_2,
        getReponse(game_selected->result_round));
    fclose(fichier);
}