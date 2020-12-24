#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fixtures.h"
#include "../../../config/gameConfig/gameConfig.h"
#include "../../../protocol/protocol.h"

InputProtocol get_some_protocol_struct_1(){
    InputProtocol some_protocol_struct_1;
    some_protocol_struct_1.game_id = 600;
    some_protocol_struct_1.status = 5;
    some_protocol_struct_1.player_id = 1;
    some_protocol_struct_1.action = 35;
    some_protocol_struct_1.time = 0.00;
    some_protocol_struct_1.round = 0;
    some_protocol_struct_1.montant = 0.0; 
    return some_protocol_struct_1;
}

InputProtocol get_some_protocol_struct_2(){
    InputProtocol some_protocol_struct_2;
    some_protocol_struct_2.game_id = 600;
    some_protocol_struct_2.status = 20;
    some_protocol_struct_2.player_id = 1;
    some_protocol_struct_2.action = 7;
    some_protocol_struct_2.time = 0.00;
    some_protocol_struct_2.round = 0;
    some_protocol_struct_2.montant = 0.0; 
    return some_protocol_struct_2;
}