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
#include "gameArray.test.h"
#include "../../src/gameArray.h"

Game_array game_array_test;

/**
 * @brief test_init_array_games
 * @return 
 **/ 
void test_init_array_games(){
    init_array_games();
    assert(game_array_test.index == 0);
}
/**
 * @brief test_game_array
 * @return 
 **/ 
void test_game_array(){
    test_init_array_games();
}