#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "utils.test.h"

/**
 * @brief get_reponse_test
 * @return 
 **/ 
void get_reponse_test(){
    
    int some_response_player = GAME_CHOICE_COLLABORATE;
    char *result = malloc(50);
    result = getReponse(some_response_player);
    assert(strcmp(result, "COLLABORATE") == 0);
    result = "";

    int some_response_player_1 = GAME_CHOICE_BETRAY;
    result = getReponse(some_response_player_1);
    assert(strcmp(result, "BETRAY") == 0);
    result = "";

    some_response_player = GAME_CHOICE_BOTH_BETRAY;
    result = getReponse(some_response_player);
    assert(strcmp(result, "BOTH BETRAY") == 0);
    result = "";

    some_response_player = GAME_CHOICE_BOTH_COLLAB;
    result = getReponse(some_response_player);
    assert(strcmp(result, "BOTH COLLAB") == 0);
    result = "";

    some_response_player = GAME_CHOICE_PLAYER1_WIN;
    result = getReponse(some_response_player);
    assert(strcmp(result, "PLAYER 1 WIN") == 0);
    result = "";

    some_response_player = GAME_CHOICE_PLAYER2_WIN;
    result = getReponse(some_response_player);
    assert(strcmp(result, "PLAYER 2 WIN") == 0);

}
/**
 * @brief test_utils
 * @return 
 **/ 
void test_utils(){
    get_reponse_test();
}