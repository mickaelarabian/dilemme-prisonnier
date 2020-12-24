

#ifndef GAME_ARRAY_H
#define GAME_ARRAY_H

#include <stdbool.h>
#include "game.h"
#include "../../config/gameConfig/gameConfig.h"

typedef struct
{
    Game data[MAX_GAME];
    int index;
} Game_array;

void init_array_games();
void games_add(Game game_to_add);
bool game_remove(int index);
Game* search_game_valid();
Game* search_game_by_id(int id);
bool remove_game_array(int id);

#endif