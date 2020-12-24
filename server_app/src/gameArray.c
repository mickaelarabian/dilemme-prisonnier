#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "gameArray.h"


Game_array game_array;

/**
 * @brief init array game when the server start
 * @return
 **/
void init_array_games() {
    game_array.index = 0;
}

/**
 * @brief Add game to game_array
 * @param game_to_add
 * @return 
 **/
void games_add(Game game_to_add) {
    if (game_array.index < MAX_GAME) {
        game_array.data[game_array.index + 1] = game_to_add;
        game_array.index ++;      
    }
}

/**
 * @brief Remove game from game_array
 * @param index
 * @return boolean true if removed and false if not
 **/
bool game_remove(int index){
    if(index <= game_array.index){
        for(int i = index; i <= (game_array.index -1); i++){
           game_array.data[i] = game_array.data[i + 1];
        }
        game_array.index--;
        return true;
    }
    return false;
}

/**
 * @brief search game valid in the game_array
 * @return Game if found a game valid
 **/
Game* search_game_valid(){
    // Searching game where player 2 is waiting
    for(int i = 0; i<= game_array.index; i++){
        if(game_array.data[i].response_player_2 == GAME_STATUS_WAITING_PLAYER){
            return &game_array.data[i];
        }
    }
    return NULL;
}

/**
 * @brief Search game by id
 * @param id
 * @return Game if found game by searching by id
 **/
Game* search_game_by_id(int id){
    // Searching game
    for(int i = 0; i<= game_array.index; i++){
        if(game_array.data[i].id == id){
            return &game_array.data[i];
        }
    }
    return NULL;
}

/**
 * @brief Finding game to removed from the game_array
 * @param id
 * @return Game to removed
 **/
bool remove_game_array(int id){
    // Searching game
    for(int i = 0; i<= game_array.index; i++){
        if(game_array.data[i].id == id){
            game_remove(i);
            return true;
        }
    }
    return false;
}