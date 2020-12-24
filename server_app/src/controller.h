
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../config/gameConfig/gameConfig.h"
#include "../../protocol/protocol.h"
#include "../srvcxnmanager.h"
#include "game.h"

void controller_end_game(InputProtocol input_protocol, Game* game_selected, int status_game);
InputProtocol update_protol_montant(Game *game_select, InputProtocol input_protocol, int player);
void update_game_response_user(InputProtocol input_protocol, Game* game_selected);
void controller_choice(InputProtocol input_protocol, Game* game_selected);
void controller_main(InputProtocol input_protocol, connection_t* connection);

#endif


