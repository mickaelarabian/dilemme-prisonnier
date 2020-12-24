#ifndef FIXTURES_H
#define FIXTURES_H

#include "../../../protocol/protocol.h"
#include "../../src/game.h"
#include "../../utils/utils.h"

char* get_some_protocol_char_1();
char* get_some_protocol_char_2();
char* get_some_protocol_char_3();
char* get_some_protocol_char_4();
char* get_some_protocol_first_connection();
InputProtocol get_some_protocol_struct_1();
InputProtocol get_some_protocol_struct_2();
InputProtocol get_some_protocol_struct_3();
InputProtocol get_some_protocol_struct_4();
Game* some_game();
Game* some_game_2();
char* char_to_file(Game* game);
connection_t* some_connection();

#endif