

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/file.h"
#include "../fixtures/fixtures.h"
#include "../../src/game.h"
#include "../../../config/gameConfig/gameConfig.h"

/**
 * @brief test_join_game
 * @return 
 **/ 
void test_join_game(){
    Game* game_to_test = malloc(100);
    Game* some_game_value = some_game();
    connection_t* connect = some_connection();

    game_to_test = join_game(connect, some_game_value);
    
    assert(game_to_test->player_2->index == some_game_value->player_2->index);
    assert(game_to_test->response_player_2 == GAME_STATUS_READY_TO_PLAY);
    assert(game_to_test->response_player_1 == GAME_STATUS_READY_TO_PLAY);
    assert(game_to_test->private == 1);
}
/**
 * @brief test_find_result
 * @return 
 **/ 
void test_find_result(){
    Game* game_to_test = malloc(100);
    Game* some_game_value = malloc(100);
    some_game_value = some_game();

    // oneTreason=10
    // twoTreason=5
    // twoCollab=0.5
    // freeMont=0

    some_game_value->response_player_1 = GAME_CHOICE_COLLABORATE;
    some_game_value->response_player_2 = GAME_CHOICE_COLLABORATE;

    game_to_test = find_result(some_game_value);
    assert(game_to_test->result_round == GAME_CHOICE_BOTH_COLLAB);

    some_game_value->response_player_1 = GAME_CHOICE_BETRAY;
    some_game_value->response_player_2 = GAME_CHOICE_BETRAY;

    game_to_test = find_result(some_game_value);
    assert(game_to_test->result_round == GAME_CHOICE_BOTH_BETRAY);

    some_game_value->response_player_1 = GAME_CHOICE_BETRAY;
    some_game_value->response_player_2 = GAME_CHOICE_COLLABORATE;

    game_to_test = find_result(some_game_value);
    assert(game_to_test->result_round == GAME_CHOICE_PLAYER1_WIN);

    some_game_value->response_player_1 = GAME_CHOICE_COLLABORATE;
    some_game_value->response_player_2 = GAME_CHOICE_BETRAY;

    game_to_test = find_result(some_game_value);
    assert(game_to_test->result_round == GAME_CHOICE_PLAYER2_WIN);

}

/**
 * @brief test_game
 * @return 
 **/ 
void test_game(){
    test_join_game();
    test_find_result();
}